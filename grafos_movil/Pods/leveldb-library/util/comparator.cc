// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#include <algorithm>
<<<<<<< HEAD
#include <cstdint>
#include <string>

#include "leveldb/comparator.h"
#include "leveldb/slice.h"
#include "util/logging.h"
#include "util/no_destructor.h"

namespace leveldb {

Comparator::~Comparator() {}
=======
#include <stdint.h>
#include "leveldb/comparator.h"
#include "leveldb/slice.h"
#include "port/port.h"
#include "util/logging.h"

namespace leveldb {

Comparator::~Comparator() { }
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

namespace {
class BytewiseComparatorImpl : public Comparator {
 public:
<<<<<<< HEAD
  BytewiseComparatorImpl() {}

  virtual const char* Name() const { return "leveldb.BytewiseComparator"; }
=======
  BytewiseComparatorImpl() { }

  virtual const char* Name() const {
    return "leveldb.BytewiseComparator";
  }
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

  virtual int Compare(const Slice& a, const Slice& b) const {
    return a.compare(b);
  }

<<<<<<< HEAD
  virtual void FindShortestSeparator(std::string* start,
                                     const Slice& limit) const {
=======
  virtual void FindShortestSeparator(
      std::string* start,
      const Slice& limit) const {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    // Find length of common prefix
    size_t min_length = std::min(start->size(), limit.size());
    size_t diff_index = 0;
    while ((diff_index < min_length) &&
           ((*start)[diff_index] == limit[diff_index])) {
      diff_index++;
    }

    if (diff_index >= min_length) {
      // Do not shorten if one string is a prefix of the other
    } else {
      uint8_t diff_byte = static_cast<uint8_t>((*start)[diff_index]);
      if (diff_byte < static_cast<uint8_t>(0xff) &&
          diff_byte + 1 < static_cast<uint8_t>(limit[diff_index])) {
        (*start)[diff_index]++;
        start->resize(diff_index + 1);
        assert(Compare(*start, limit) < 0);
      }
    }
  }

  virtual void FindShortSuccessor(std::string* key) const {
    // Find first character that can be incremented
    size_t n = key->size();
    for (size_t i = 0; i < n; i++) {
      const uint8_t byte = (*key)[i];
      if (byte != static_cast<uint8_t>(0xff)) {
        (*key)[i] = byte + 1;
<<<<<<< HEAD
        key->resize(i + 1);
=======
        key->resize(i+1);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
        return;
      }
    }
    // *key is a run of 0xffs.  Leave it alone.
  }
};
}  // namespace

<<<<<<< HEAD
const Comparator* BytewiseComparator() {
  static NoDestructor<BytewiseComparatorImpl> singleton;
  return singleton.get();
=======
static port::OnceType once = LEVELDB_ONCE_INIT;
static const Comparator* bytewise;

static void InitModule() {
  bytewise = new BytewiseComparatorImpl;
}

const Comparator* BytewiseComparator() {
  port::InitOnce(&once, InitModule);
  return bytewise;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
}

}  // namespace leveldb
