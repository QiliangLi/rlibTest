#include "rdma_ctrl.hpp"
#include <stdio.h>
#include <assert.h>

int client_node_id = 0;
int tcp_port = 8000;
int server_port = 23333;

using namespace rdmaio;

int main(int argc, char *argv[])
{
    RdmaCtrl *c = new RdmaCtrl(client_node_id, tcp_port);
    RdmaCtrl::DevIdx idx{.dev_id = 0, .port_id = 1}; // using the first RNIC's first port
    c->open_thread_local_device(idx);

    // client's local memory region
    // register a buffer to the previous opened device, using id = 73
    char *buffer = (char *)malloc(4096);
    memset(buffer, 0, 4096);
    // parameters in register_memory: ids for client's local_mr, buffer, size, previously opened device of this thread (if it is already opened)
    RDMA_ASSERT(c->register_memory(73, buffer, 4096, c->get_device()) == true);

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
    char *local_buf = buffer;
    uint64_t address = 0;
    int msg_len = 11; // length of "hello world"

    ConnStatus rc;

    for (int i = 0; i < 10; i++)
    {
        rc = qp->post_send(IBV_WR_RDMA_READ, local_buf, msg_len, address, IBV_SEND_SIGNALED);
        if (rc == SUCC)
        {
            printf("client: post ok\n");
        }
        else
        {
            printf("client: post fail. rc=%d\n", rc);
        }
        
        rc = qp->poll_till_completion(wc, no_timeout);
        // then get the results, stored in the local_buffer
        if (rc == SUCC)
        {
            printf("client: poll ok\n");
            printf("msg read: %s\n", local_buf);
        }
        else
        {
            printf("client: poll fail. rc=%d\n", rc);
        }
    }

    return 0;
}
