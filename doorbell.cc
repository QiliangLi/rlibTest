#include "doorbell.h"
#define ALWAYS_INLINE inline __attribute__((always_inline))

ALWAYS_INLINE
bool RDMABatchSync(RCQP *qp, ibv_send_wr *send_sr, ibv_send_wr **bad_sr_addr, int doorbell_num)
{
    send_sr[doorbell_num].wr_id = 0;
    auto rc = qp->post_batch(send_sr, bad_sr_addr);
    if (rc != SUCC)
    {
        RDMA_LOG(ERROR) << "client: post batch fail. rc=" << rc;
        return false;
    }
    ibv_wc wc{};
    rc = qp->poll_till_completion(wc, no_timeout);
    if (rc != SUCC)
    {
        RDMA_LOG(ERROR) << "client: poll batch fail. rc=" << rc;
        return false;
    }
    return true;
}

void LockReadBatch::SetLockReq(char *local_addr, uint64_t remote_off, uint64_t compare, uint64_t swap)
{
    sr[0].opcode = IBV_WR_ATOMIC_CMP_AND_SWP;
    sr[0].wr.atomic.remote_addr = remote_off;
    sr[0].wr.atomic.compare_add = compare;
    sr[0].wr.atomic.swap = swap;
    sge[0].length = sizeof(uint64_t);
    sge[0].addr = (uint64_t)local_addr;
}

void LockReadBatch::SetReadReq(char *local_addr, uint64_t remote_off, size_t size)
{
    sr[1].opcode = IBV_WR_RDMA_READ;
    sr[1].wr.rdma.remote_addr = remote_off;
    sge[1].addr = (uint64_t)local_addr;
    sge[1].length = size;
}

bool LockReadBatch::SendReqs(RCQP *qp)
{
    // sr[0] must be an atomic operation
    sr[0].wr.atomic.remote_addr += qp->remote_mr_.buf;
    sr[0].wr.atomic.rkey = qp->remote_mr_.key;
    sge[0].lkey = qp->local_mr_.key;

    sr[1].wr.rdma.remote_addr += qp->remote_mr_.buf;
    sr[1].wr.rdma.rkey = qp->remote_mr_.key;
    sge[1].lkey = qp->local_mr_.key;

    if (!RDMABatchSync(qp, &(sr[0]), &bad_sr, 1))
        return false;
    return true;
}

void WriteUnlockBatch::SetWriteReq(char *local_addr, uint64_t remote_off, size_t size)
{
    sr[0].opcode = IBV_WR_RDMA_WRITE;
    sr[0].wr.rdma.remote_addr = remote_off;
    sge[0].addr = (uint64_t)local_addr;
    sge[0].length = size;
    if (size < 64)
    {
        sr[0].send_flags |= IBV_SEND_INLINE;
    }
}

void WriteUnlockBatch::SetUnLockReq(char *local_addr, uint64_t remote_off, uint64_t compare, uint64_t swap)
{
    sr[1].opcode = IBV_WR_ATOMIC_CMP_AND_SWP;
    sr[1].wr.atomic.remote_addr = remote_off;
    sr[1].wr.atomic.compare_add = compare;
    sr[1].wr.atomic.swap = swap;
    sge[1].length = sizeof(uint64_t);
    sge[1].addr = (uint64_t)local_addr;
}

bool WriteUnlockBatch::SendReqs(RCQP *qp)
{
    sr[0].wr.rdma.remote_addr += qp->remote_mr_.buf;
    sr[0].wr.rdma.rkey = qp->remote_mr_.key;
    sge[0].lkey = qp->local_mr_.key;

    sr[1].wr.atomic.remote_addr += qp->remote_mr_.buf;
    sr[1].wr.atomic.rkey = qp->remote_mr_.key;

    sge[1].lkey = qp->local_mr_.key;

    if (!RDMABatchSync(qp, &(sr[0]), &bad_sr, 1))
        return false;
    return true;
}

void InvisibleWriteBatch::SetInvisibleReq(char *local_addr, uint64_t remote_off, uint64_t compare, uint64_t swap)
{
    sr[0].opcode = IBV_WR_ATOMIC_CMP_AND_SWP;
    sr[0].wr.atomic.remote_addr = remote_off;
    sr[0].wr.atomic.compare_add = compare;
    sr[0].wr.atomic.swap = swap;
    sge[0].length = sizeof(uint64_t);
    sge[0].addr = (uint64_t)local_addr;
}

void InvisibleWriteBatch::SetWriteRemoteReq(char *local_addr, uint64_t remote_off, size_t size)
{
    sr[1].opcode = IBV_WR_RDMA_WRITE;
    sr[1].wr.rdma.remote_addr = remote_off;
    sge[1].addr = (uint64_t)local_addr;
    sge[1].length = size;
    if (size < 64)
    {
        sr[1].send_flags |= IBV_SEND_INLINE;
    }
}

bool InvisibleWriteBatch::SendReqsSync(RCQP *qp)
{
    // sr[0] must be an atomic operation
    sr[0].wr.atomic.remote_addr += qp->remote_mr_.buf;
    sr[0].wr.atomic.rkey = qp->remote_mr_.key;
    sge[0].lkey = qp->local_mr_.key;

    sr[1].wr.rdma.remote_addr += qp->remote_mr_.buf;
    sr[1].wr.rdma.rkey = qp->remote_mr_.key;
    sge[1].lkey = qp->local_mr_.key;

    if (!RDMABatchSync(qp, &(sr[0]), &bad_sr, 1))
        return false;
    return true;
}