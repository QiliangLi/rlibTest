#include "rdma_ctrl.hpp"
#include "doorbell.h"
#include <stdio.h>
#include <assert.h>

#define STATE_LOCKED 1 // Data cannot be written. Used for serializing transactions
#define STATE_CLEAN 0

int client_node_id = 0;
int tcp_port = 8000;
int server_port = 23333;

using namespace rdmaio;

// the input buffer has stored the data in a little endian representation
// If the buffer is stored in big endian mode then reverse the loop
uint64_t char2uint64(char *input){
    int i;
    uint64_t paquet = 0;
    for( i = 7; i >= 0; --i )
    {
        paquet <<= 8;
        paquet |= (uint64_t)input[i];
    }

    return paquet;
}

int main(int argc, char *argv[])
{
    RdmaCtrl *c = new RdmaCtrl(client_node_id, tcp_port);
    RdmaCtrl::DevIdx idx{.dev_id = 0, .port_id = 1}; // using the first RNIC's first port
    c->open_thread_local_device(idx);

    // client's local memory region
    // register a buffer to the previous opened device, using id = 73
    char *buffer = (char *)malloc(40960);
    memset(buffer, 0, 40960);
    // parameters in register_memory: ids for client's local_mr, buffer, size, previously opened device of this thread (if it is already opened)
    RDMA_ASSERT(c->register_memory(73, buffer, 40960, c->get_device()) == true);

    // get remote server's memory region information via TCP
    // parameters in get_remote_mr: remote server ip, remote server port, Memory region ids for remote servers, returned MemoryAttr
    MemoryAttr remote_mr;
    while (QP::get_remote_mr("node13", server_port, 73, &remote_mr) != SUCC)
    {
        usleep(2000);
    }

    // create the RC qp to access remote server's memory, using the previous registered memory
    MemoryAttr local_mr = c->get_local_mr(73);
    RCQP *qp = c->create_rc_qp(create_rc_idx(1, 0), c->get_device(), &local_mr);
    qp->bind_remote_mr(remote_mr); // bind to the previous allocated mr

    while (qp->connect("node13", server_port) != SUCC)
    {
        usleep(2000);
    }

    printf("client: QP connected!\n");
    // wc: work completion structure
    ibv_wc wc;
    char *cas_buf = buffer;
    char *data_buf = buffer + 9;
    uint64_t address = 0;
    int msg_len = 11; // length of "hello world"
    ConnStatus rc;

    std::shared_ptr<DoubleCASBatch> doorbell = std::make_shared<DoubleCASBatch>();

    // int loop = 1000;
    // struct timespec start = {0, 0};
    // struct timespec end = {0, 0};
    // for (msg_len = 128; msg_len <= 4096; msg_len *= 2)
    // {
    //     // RDMA_LOG(INFO) << "Testing RDMA Batch(CAS+READ), msg_len " << msg_len << "\n";
    //     clock_gettime(CLOCK_REALTIME, &start);
    //     for (int i = 0; i < loop; i++)
    //     {
    //         doorbell->SetLockReq(cas_buf, 0, STATE_CLEAN, STATE_LOCKED);
    //         doorbell->SetReadReq(data_buf, 8, msg_len); // Read "hello world"
    //         if (!doorbell->SendReqs(qp))
    //         {
    //             RDMA_LOG(ERROR) << "Send doorbell requests fail!";
    //         }
    //     }
    //     clock_gettime(CLOCK_REALTIME, &end);
    //     long total = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);
    //     printf("RDMA Batch(CAS+READ), msg_len %d B, avgLatency %f us\n", msg_len, total / (loop * 1000.0));
    // }

    doorbell->Set1stCAS(cas_buf, 0, char2uint64("SSSSSSSS"), char2uint64("LLLLLLLL"));
    doorbell->Set2ndCAS(data_buf, 8, char2uint64("hello wo"), char2uint64("MMMMMMMM"));

    if (!doorbell->SendReqs(qp))
    {
        RDMA_LOG(ERROR) << "Send doorbell requests fail!";
    }
    printf("cas_buf: %s\n", cas_buf);
    printf("data_buf: %s\n", data_buf);
    rc = qp->poll_till_completion(wc, no_timeout);
    rc == SUCC ? printf("client: poll ok\nmsg read: %s\n", cas_buf) : printf("client: poll fail. rc=%d\n", rc);
    rc = qp->poll_till_completion(wc, no_timeout);
    rc == SUCC ? printf("client: poll ok\nmsg read: %s\n", data_buf) : printf("client: poll fail. rc=%d\n", rc);


    return 0;
}
