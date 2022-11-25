#pragma once

#include "rdma_ctrl.hpp"

using namespace rdmaio;

// Two RDMA requests are sent to the QP in a doorbelled (or batched) way.
// These requests are executed within one round trip
// Target: improve performance

class DoorbellBatch {
 public:
  DoorbellBatch() {
    // The key of doorbell: set the pointer to link two requests
    sr[0].num_sge = 1;
    sr[0].sg_list = &sge[0];
    sr[0].send_flags = 0;
    sr[0].next = &sr[1];
    sr[1].num_sge = 1;
    sr[1].sg_list = &sge[1];
    sr[1].send_flags = IBV_SEND_SIGNALED;
    sr[1].next = NULL;
  }

  struct ibv_send_wr sr[2];

  struct ibv_sge sge[2];

  struct ibv_send_wr* bad_sr;
};

class DoubleCASBatch : public DoorbellBatch {
  public:
    DoubleCASBatch() : DoorbellBatch() {}

    void Set1stCAS(char* local_addr, uint64_t remote_off, uint64_t compare, uint64_t swap);

    void Set2ndCAS(char* local_addr, uint64_t remote_off, uint64_t compare, uint64_t swap);

    // Send doorbelled requests to the queue pair
    bool SendReqs(RCQP* qp);
};

class LockReadBatch : public DoorbellBatch {
 public:
  LockReadBatch() : DoorbellBatch() {}

  // SetLockReq and SetReadReq are a doorbelled group
  // First lock, then read
  void SetLockReq(char* local_addr, uint64_t remote_off, uint64_t compare, uint64_t swap);

  void SetReadReq(char* local_addr, uint64_t remote_off, size_t size);

  // Send doorbelled requests to the queue pair
  bool SendReqs(RCQP* qp);
};

class WriteUnlockBatch : public DoorbellBatch {
 public:
  WriteUnlockBatch() : DoorbellBatch() {}

  // SetWritePrimaryReq and SetUnLockReq are a doorbelled group
  // First write, then unlock
  void SetWriteReq(char* local_addr, uint64_t remote_off, size_t size);

  void SetUnLockReq(char* local_addr, uint64_t remote_off, uint64_t compare, uint64_t swap);

  // Send doorbelled requests to the queue pair
  bool SendReqs(RCQP* qp);
};

class InvisibleWriteBatch : public DoorbellBatch {
 public:
  InvisibleWriteBatch() : DoorbellBatch() {}

  // SetInvisibleReq and SetWriteRemoteReq are a doorbelled group
  // First lock, then write
  void SetInvisibleReq(char* local_addr, uint64_t remote_off, uint64_t compare, uint64_t swap);

  void SetWriteRemoteReq(char* local_addr, uint64_t remote_off, size_t size);

  // Send doorbelled requests to the queue pair
  bool SendReqsSync(RCQP* qp);
};
