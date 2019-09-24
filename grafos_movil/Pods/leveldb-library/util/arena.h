// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#ifndef STORAGE_LEVELDB_UTIL_ARENA_H_
#define STORAGE_LEVELDB_UTIL_ARENA_H_

<<<<<<< HEAD
<<<<<<< HEAD
#include <atomic>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <vector>
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#include <vector>
#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include "port/port.h"
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

namespace leveldb {

class Arena {
 public:
  Arena();
<<<<<<< HEAD
<<<<<<< HEAD

  Arena(const Arena&) = delete;
  Arena& operator=(const Arena&) = delete;

=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  ~Arena();

  // Return a pointer to a newly allocated memory block of "bytes" bytes.
  char* Allocate(size_t bytes);

<<<<<<< HEAD
<<<<<<< HEAD
  // Allocate memory with the normal alignment guarantees provided by malloc.
=======
  // Allocate memory with the normal alignment guarantees provided by malloc
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  // Allocate memory with the normal alignment guarantees provided by malloc
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  char* AllocateAligned(size_t bytes);

  // Returns an estimate of the total memory usage of data allocated
  // by the arena.
  size_t MemoryUsage() const {
<<<<<<< HEAD
<<<<<<< HEAD
    return memory_usage_.load(std::memory_order_relaxed);
=======
    return reinterpret_cast<uintptr_t>(memory_usage_.NoBarrier_Load());
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
    return reinterpret_cast<uintptr_t>(memory_usage_.NoBarrier_Load());
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  }

 private:
  char* AllocateFallback(size_t bytes);
  char* AllocateNewBlock(size_t block_bytes);

  // Allocation state
  char* alloc_ptr_;
  size_t alloc_bytes_remaining_;

  // Array of new[] allocated memory blocks
  std::vector<char*> blocks_;

  // Total memory usage of the arena.
<<<<<<< HEAD
<<<<<<< HEAD
  //
  // TODO(costan): This member is accessed via atomics, but the others are
  //               accessed without any locking. Is this OK?
  std::atomic<size_t> memory_usage_;
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  port::AtomicPointer memory_usage_;

  // No copying allowed
  Arena(const Arena&);
  void operator=(const Arena&);
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
};

inline char* Arena::Allocate(size_t bytes) {
  // The semantics of what to return are a bit messy if we allow
  // 0-byte allocations, so we disallow them here (we don't need
  // them for our internal use).
  assert(bytes > 0);
  if (bytes <= alloc_bytes_remaining_) {
    char* result = alloc_ptr_;
    alloc_ptr_ += bytes;
    alloc_bytes_remaining_ -= bytes;
    return result;
  }
  return AllocateFallback(bytes);
}

}  // namespace leveldb

#endif  // STORAGE_LEVELDB_UTIL_ARENA_H_
