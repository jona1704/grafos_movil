// Copyright (c) 2012 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.
//
// A filter block is stored near the end of a Table file.  It contains
// filters (e.g., bloom filters) for all data blocks in the table combined
// into a single filter block.

#ifndef STORAGE_LEVELDB_TABLE_FILTER_BLOCK_H_
#define STORAGE_LEVELDB_TABLE_FILTER_BLOCK_H_

#include <stddef.h>
#include <stdint.h>
<<<<<<< HEAD
<<<<<<< HEAD

#include <string>
#include <vector>

=======
#include <string>
#include <vector>
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
#include <string>
#include <vector>
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#include "leveldb/slice.h"
#include "util/hash.h"

namespace leveldb {

class FilterPolicy;

// A FilterBlockBuilder is used to construct all of the filters for a
// particular Table.  It generates a single string which is stored as
// a special block in the Table.
//
// The sequence of calls to FilterBlockBuilder must match the regexp:
//      (StartBlock AddKey*)* Finish
class FilterBlockBuilder {
 public:
  explicit FilterBlockBuilder(const FilterPolicy*);

<<<<<<< HEAD
<<<<<<< HEAD
  FilterBlockBuilder(const FilterBlockBuilder&) = delete;
  FilterBlockBuilder& operator=(const FilterBlockBuilder&) = delete;

=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  void StartBlock(uint64_t block_offset);
  void AddKey(const Slice& key);
  Slice Finish();

 private:
  void GenerateFilter();

  const FilterPolicy* policy_;
<<<<<<< HEAD
<<<<<<< HEAD
  std::string keys_;             // Flattened key contents
  std::vector<size_t> start_;    // Starting index in keys_ of each key
  std::string result_;           // Filter data computed so far
  std::vector<Slice> tmp_keys_;  // policy_->CreateFilter() argument
  std::vector<uint32_t> filter_offsets_;
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  std::string keys_;              // Flattened key contents
  std::vector<size_t> start_;     // Starting index in keys_ of each key
  std::string result_;            // Filter data computed so far
  std::vector<Slice> tmp_keys_;   // policy_->CreateFilter() argument
  std::vector<uint32_t> filter_offsets_;

  // No copying allowed
  FilterBlockBuilder(const FilterBlockBuilder&);
  void operator=(const FilterBlockBuilder&);
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
};

class FilterBlockReader {
 public:
<<<<<<< HEAD
<<<<<<< HEAD
  // REQUIRES: "contents" and *policy must stay live while *this is live.
=======
 // REQUIRES: "contents" and *policy must stay live while *this is live.
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
 // REQUIRES: "contents" and *policy must stay live while *this is live.
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  FilterBlockReader(const FilterPolicy* policy, const Slice& contents);
  bool KeyMayMatch(uint64_t block_offset, const Slice& key);

 private:
  const FilterPolicy* policy_;
  const char* data_;    // Pointer to filter data (at block-start)
  const char* offset_;  // Pointer to beginning of offset array (at block-end)
  size_t num_;          // Number of entries in offset array
  size_t base_lg_;      // Encoding parameter (see kFilterBaseLg in .cc file)
};

<<<<<<< HEAD
<<<<<<< HEAD
}  // namespace leveldb
=======
}
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
}
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

#endif  // STORAGE_LEVELDB_TABLE_FILTER_BLOCK_H_
