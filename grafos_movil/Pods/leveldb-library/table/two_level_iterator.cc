// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#include "table/two_level_iterator.h"

#include "leveldb/table.h"
#include "table/block.h"
#include "table/format.h"
#include "table/iterator_wrapper.h"

namespace leveldb {

namespace {

typedef Iterator* (*BlockFunction)(void*, const ReadOptions&, const Slice&);

<<<<<<< HEAD
<<<<<<< HEAD
class TwoLevelIterator : public Iterator {
 public:
  TwoLevelIterator(Iterator* index_iter, BlockFunction block_function,
                   void* arg, const ReadOptions& options);
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
class TwoLevelIterator: public Iterator {
 public:
  TwoLevelIterator(
    Iterator* index_iter,
    BlockFunction block_function,
    void* arg,
    const ReadOptions& options);
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

  virtual ~TwoLevelIterator();

  virtual void Seek(const Slice& target);
  virtual void SeekToFirst();
  virtual void SeekToLast();
  virtual void Next();
  virtual void Prev();

<<<<<<< HEAD
<<<<<<< HEAD
  virtual bool Valid() const { return data_iter_.Valid(); }
=======
  virtual bool Valid() const {
    return data_iter_.Valid();
  }
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  virtual bool Valid() const {
    return data_iter_.Valid();
  }
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  virtual Slice key() const {
    assert(Valid());
    return data_iter_.key();
  }
  virtual Slice value() const {
    assert(Valid());
    return data_iter_.value();
  }
  virtual Status status() const {
    // It'd be nice if status() returned a const Status& instead of a Status
    if (!index_iter_.status().ok()) {
      return index_iter_.status();
<<<<<<< HEAD
<<<<<<< HEAD
    } else if (data_iter_.iter() != nullptr && !data_iter_.status().ok()) {
=======
    } else if (data_iter_.iter() != NULL && !data_iter_.status().ok()) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
    } else if (data_iter_.iter() != NULL && !data_iter_.status().ok()) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
      return data_iter_.status();
    } else {
      return status_;
    }
  }

 private:
  void SaveError(const Status& s) {
    if (status_.ok() && !s.ok()) status_ = s;
  }
  void SkipEmptyDataBlocksForward();
  void SkipEmptyDataBlocksBackward();
  void SetDataIterator(Iterator* data_iter);
  void InitDataBlock();

  BlockFunction block_function_;
  void* arg_;
  const ReadOptions options_;
  Status status_;
  IteratorWrapper index_iter_;
<<<<<<< HEAD
<<<<<<< HEAD
  IteratorWrapper data_iter_;  // May be nullptr
  // If data_iter_ is non-null, then "data_block_handle_" holds the
=======
  IteratorWrapper data_iter_; // May be NULL
  // If data_iter_ is non-NULL, then "data_block_handle_" holds the
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  IteratorWrapper data_iter_; // May be NULL
  // If data_iter_ is non-NULL, then "data_block_handle_" holds the
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  // "index_value" passed to block_function_ to create the data_iter_.
  std::string data_block_handle_;
};

<<<<<<< HEAD
<<<<<<< HEAD
TwoLevelIterator::TwoLevelIterator(Iterator* index_iter,
                                   BlockFunction block_function, void* arg,
                                   const ReadOptions& options)
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
TwoLevelIterator::TwoLevelIterator(
    Iterator* index_iter,
    BlockFunction block_function,
    void* arg,
    const ReadOptions& options)
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    : block_function_(block_function),
      arg_(arg),
      options_(options),
      index_iter_(index_iter),
<<<<<<< HEAD
<<<<<<< HEAD
      data_iter_(nullptr) {}

TwoLevelIterator::~TwoLevelIterator() {}
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
      data_iter_(NULL) {
}

TwoLevelIterator::~TwoLevelIterator() {
}
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

void TwoLevelIterator::Seek(const Slice& target) {
  index_iter_.Seek(target);
  InitDataBlock();
<<<<<<< HEAD
<<<<<<< HEAD
  if (data_iter_.iter() != nullptr) data_iter_.Seek(target);
=======
  if (data_iter_.iter() != NULL) data_iter_.Seek(target);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  if (data_iter_.iter() != NULL) data_iter_.Seek(target);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  SkipEmptyDataBlocksForward();
}

void TwoLevelIterator::SeekToFirst() {
  index_iter_.SeekToFirst();
  InitDataBlock();
<<<<<<< HEAD
<<<<<<< HEAD
  if (data_iter_.iter() != nullptr) data_iter_.SeekToFirst();
=======
  if (data_iter_.iter() != NULL) data_iter_.SeekToFirst();
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  if (data_iter_.iter() != NULL) data_iter_.SeekToFirst();
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  SkipEmptyDataBlocksForward();
}

void TwoLevelIterator::SeekToLast() {
  index_iter_.SeekToLast();
  InitDataBlock();
<<<<<<< HEAD
<<<<<<< HEAD
  if (data_iter_.iter() != nullptr) data_iter_.SeekToLast();
=======
  if (data_iter_.iter() != NULL) data_iter_.SeekToLast();
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  if (data_iter_.iter() != NULL) data_iter_.SeekToLast();
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  SkipEmptyDataBlocksBackward();
}

void TwoLevelIterator::Next() {
  assert(Valid());
  data_iter_.Next();
  SkipEmptyDataBlocksForward();
}

void TwoLevelIterator::Prev() {
  assert(Valid());
  data_iter_.Prev();
  SkipEmptyDataBlocksBackward();
}

<<<<<<< HEAD
<<<<<<< HEAD
void TwoLevelIterator::SkipEmptyDataBlocksForward() {
  while (data_iter_.iter() == nullptr || !data_iter_.Valid()) {
    // Move to next block
    if (!index_iter_.Valid()) {
      SetDataIterator(nullptr);
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

void TwoLevelIterator::SkipEmptyDataBlocksForward() {
  while (data_iter_.iter() == NULL || !data_iter_.Valid()) {
    // Move to next block
    if (!index_iter_.Valid()) {
      SetDataIterator(NULL);
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
      return;
    }
    index_iter_.Next();
    InitDataBlock();
<<<<<<< HEAD
<<<<<<< HEAD
    if (data_iter_.iter() != nullptr) data_iter_.SeekToFirst();
=======
    if (data_iter_.iter() != NULL) data_iter_.SeekToFirst();
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
    if (data_iter_.iter() != NULL) data_iter_.SeekToFirst();
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  }
}

void TwoLevelIterator::SkipEmptyDataBlocksBackward() {
<<<<<<< HEAD
<<<<<<< HEAD
  while (data_iter_.iter() == nullptr || !data_iter_.Valid()) {
    // Move to next block
    if (!index_iter_.Valid()) {
      SetDataIterator(nullptr);
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  while (data_iter_.iter() == NULL || !data_iter_.Valid()) {
    // Move to next block
    if (!index_iter_.Valid()) {
      SetDataIterator(NULL);
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
      return;
    }
    index_iter_.Prev();
    InitDataBlock();
<<<<<<< HEAD
<<<<<<< HEAD
    if (data_iter_.iter() != nullptr) data_iter_.SeekToLast();
=======
    if (data_iter_.iter() != NULL) data_iter_.SeekToLast();
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
    if (data_iter_.iter() != NULL) data_iter_.SeekToLast();
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  }
}

void TwoLevelIterator::SetDataIterator(Iterator* data_iter) {
<<<<<<< HEAD
<<<<<<< HEAD
  if (data_iter_.iter() != nullptr) SaveError(data_iter_.status());
=======
  if (data_iter_.iter() != NULL) SaveError(data_iter_.status());
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  if (data_iter_.iter() != NULL) SaveError(data_iter_.status());
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  data_iter_.Set(data_iter);
}

void TwoLevelIterator::InitDataBlock() {
  if (!index_iter_.Valid()) {
<<<<<<< HEAD
<<<<<<< HEAD
    SetDataIterator(nullptr);
  } else {
    Slice handle = index_iter_.value();
    if (data_iter_.iter() != nullptr &&
        handle.compare(data_block_handle_) == 0) {
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    SetDataIterator(NULL);
  } else {
    Slice handle = index_iter_.value();
    if (data_iter_.iter() != NULL && handle.compare(data_block_handle_) == 0) {
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
      // data_iter_ is already constructed with this iterator, so
      // no need to change anything
    } else {
      Iterator* iter = (*block_function_)(arg_, options_, handle);
      data_block_handle_.assign(handle.data(), handle.size());
      SetDataIterator(iter);
    }
  }
}

}  // namespace

<<<<<<< HEAD
<<<<<<< HEAD
Iterator* NewTwoLevelIterator(Iterator* index_iter,
                              BlockFunction block_function, void* arg,
                              const ReadOptions& options) {
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
Iterator* NewTwoLevelIterator(
    Iterator* index_iter,
    BlockFunction block_function,
    void* arg,
    const ReadOptions& options) {
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  return new TwoLevelIterator(index_iter, block_function, arg, options);
}

}  // namespace leveldb
