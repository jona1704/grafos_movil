// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.
//
// Simple hash function used for internal data structures

#ifndef STORAGE_LEVELDB_UTIL_HASH_H_
#define STORAGE_LEVELDB_UTIL_HASH_H_

#include <stddef.h>
#include <stdint.h>

namespace leveldb {

<<<<<<< HEAD
<<<<<<< HEAD
uint32_t Hash(const char* data, size_t n, uint32_t seed);

}  // namespace leveldb
=======
extern uint32_t Hash(const char* data, size_t n, uint32_t seed);

}
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
extern uint32_t Hash(const char* data, size_t n, uint32_t seed);

}
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

#endif  // STORAGE_LEVELDB_UTIL_HASH_H_
