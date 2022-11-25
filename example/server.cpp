
#include "rdma_ctrl.hpp"
#include <stdio.h>
#include <string.h>
#include <assert.h>

/**
 * Note, RDMA usually uses some other communication method (e.g. TCP/IP) to exchange QP informations.
 * RLib uses TCP for the pre-communication.
 */
int server_node_id = 1;
int tcp_port = 23333;
int client_port = 8000;

using namespace rdmaio;

int main(int argc, char *argv[])
{
    RdmaCtrl *c = new RdmaCtrl(server_node_id, tcp_port);
    RdmaCtrl::DevIdx idx{.dev_id = 0, .port_id = 1}; // using the first RNIC's first port
    c->open_thread_local_device(idx);

    // register a buffer to the previous opened device, using id = 73
    char *buffer = (char *)malloc(40960);
    memset(buffer, 0, 40960);
    RDMA_ASSERT(c->register_memory(73, buffer, 40960, c->get_device()) == true);
    printf("[server] buffer registered\n");

    char *b0 = (char*) malloc(4096);
    char *b1 = (char*) malloc(4096);
    memset(b0, 0, 4096);
    memset(b1, 0, 4096);
    RDMA_ASSERT(c->register_memory(74, b0, 4096, c->get_device()) == true);
    RDMA_ASSERT(c->register_memory(75, b1, 4096, c->get_device()) == true);
    printf("[server] b0 b1 registered\n");

    // fill a string to the register memory region
    char s[] = "ABCDEFGZhello world";
    memcpy(buffer, s, strlen(s));

    // MemoryAttr local_mr = c->get_local_mr(73);
    // RCQP *qp = c->create_rc_qp(create_rc_idx(1, 0), c->get_device(), &local_mr);

    // // server also needs to "connect" clinet.
    // while (qp->connect("node2", client_port, create_rc_idx(1, 0)) != SUCC)
    // {
    //     usleep(2000);
    // }

    // printf("server: QP connected!\n");
    printf("start looping...\n");
    while (true)
    {
        memcpy(s, buffer, strlen(s));
        printf("memory region: %s\n", s);
        // This is RDMA, server does not need to do anything :)
        sleep(1);
    }

    return 0;
}
