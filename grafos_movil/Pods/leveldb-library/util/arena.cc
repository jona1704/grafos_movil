// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#include "util/arena.h"
<<<<<<< HEAD
=======
#include <assert.h>
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

namespace leveldb {

static const int kBlockSize = 4096;

<<<<<<< HEAD
Arena::Arena()
    : alloc_ptr_(nullptr), alloc_bytes_remaining_(0), memory_usage_(0) {}
=======
Arena::Arena() : memory_usage_(0) {
  alloc_ptr_ = NULL;  // First allocation will allocate a block
  alloc_bytes_remaining_ = 0;
}
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

Arena::~Arena() {
  for (size_t i = 0; i < blocks_.size(); i++) {
    delete[] blocks_[i];
  }
}

char* Arena::AllocateFallback(size_t bytes) {
  if (bytes > kBlockSize / 4) {
    // Object is more than a quarter of our block size.  Allocate it separately
    // to avoid wasting too much space in leftover bytes.
    char* result = AllocateNewBlock(bytes);
    return result;
  }

  // We waste the remaining space in the current block.
  alloc_ptr_ = AllocateNewBlock(kBlockSize);
  alloc_bytes_remaining_ = kBlockSize;

  char* result = alloc_ptr_;
  alloc_ptr_ += bytes;
  alloc_bytes_remaining_ -= bytes;
  return result;
}

char* Arena::AllocateAligned(size_t bytes) {
  const int align = (sizeof(void*) > 8) ? sizeof(void*) : 8;
<<<<<<< HEAD
  static_assert((align & (align - 1)) == 0,
                "Pointer size should be a power of 2");
  size_t current_mod = reinterpret_cast<uintptr_t>(alloc_ptr_) & (align - 1);
=======
  assert((align & (align-1)) == 0);   // Pointer size should be a power of 2
  size_t current_mod = reinterpret_cast<uintptr_t>(alloc_ptr_) & (align-1);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  size_t slop = (current_mod == 0 ? 0 : align - current_mod);
  size_t needed = bytes + slop;
  char* result;
  if (needed <= alloc_bytes_remaining_) {
    result = alloc_ptr_ + slop;
    alloc_ptr_ += needed;
    alloc_bytes_remaining_ -= needed;
  } else {
    // AllocateFallback always returned aligned memory
    result = AllocateFallback(bytes);
  }
<<<<<<< HEAD
  assert((reinterpret_cast<uintptr_t>(result) & (align - 1)) == 0);
=======
  assert((reinterpret_cast<uintptr_t>(result) & (align-1)) == 0);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  return result;
}

char* Arena::AllocateNewBlock(size_t block_bytes) {
  char* result = new char[block_bytes];
  blocks_.push_back(result);
<<<<<<< HEAD
  memory_usage_.fetch_add(block_bytes + sizeof(char*),
                          std::memory_order_relaxed);
=======
  memory_usage_.NoBarrier_Store(
      reinterpret_cast<void*>(MemoryUsage() + block_bytes + sizeof(char*)));
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  return result;
}

}  // namespace leveldb
