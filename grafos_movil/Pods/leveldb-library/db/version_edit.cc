// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#include "db/version_edit.h"

#include "db/version_set.h"
#include "util/coding.h"

namespace leveldb {

// Tag numbers for serialized VersionEdit.  These numbers are written to
// disk and should not be changed.
enum Tag {
<<<<<<< HEAD
<<<<<<< HEAD
  kComparator = 1,
  kLogNumber = 2,
  kNextFileNumber = 3,
  kLastSequence = 4,
  kCompactPointer = 5,
  kDeletedFile = 6,
  kNewFile = 7,
  // 8 was used for large value refs
  kPrevLogNumber = 9
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  kComparator           = 1,
  kLogNumber            = 2,
  kNextFileNumber       = 3,
  kLastSequence         = 4,
  kCompactPointer       = 5,
  kDeletedFile          = 6,
  kNewFile              = 7,
  // 8 was used for large value refs
  kPrevLogNumber        = 9
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
};

void VersionEdit::Clear() {
  comparator_.clear();
  log_number_ = 0;
  prev_log_number_ = 0;
  last_sequence_ = 0;
  next_file_number_ = 0;
  has_comparator_ = false;
  has_log_number_ = false;
  has_prev_log_number_ = false;
  has_next_file_number_ = false;
  has_last_sequence_ = false;
  deleted_files_.clear();
  new_files_.clear();
}

void VersionEdit::EncodeTo(std::string* dst) const {
  if (has_comparator_) {
    PutVarint32(dst, kComparator);
    PutLengthPrefixedSlice(dst, comparator_);
  }
  if (has_log_number_) {
    PutVarint32(dst, kLogNumber);
    PutVarint64(dst, log_number_);
  }
  if (has_prev_log_number_) {
    PutVarint32(dst, kPrevLogNumber);
    PutVarint64(dst, prev_log_number_);
  }
  if (has_next_file_number_) {
    PutVarint32(dst, kNextFileNumber);
    PutVarint64(dst, next_file_number_);
  }
  if (has_last_sequence_) {
    PutVarint32(dst, kLastSequence);
    PutVarint64(dst, last_sequence_);
  }

  for (size_t i = 0; i < compact_pointers_.size(); i++) {
    PutVarint32(dst, kCompactPointer);
    PutVarint32(dst, compact_pointers_[i].first);  // level
    PutLengthPrefixedSlice(dst, compact_pointers_[i].second.Encode());
  }

  for (DeletedFileSet::const_iterator iter = deleted_files_.begin();
<<<<<<< HEAD
<<<<<<< HEAD
       iter != deleted_files_.end(); ++iter) {
=======
       iter != deleted_files_.end();
       ++iter) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
       iter != deleted_files_.end();
       ++iter) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    PutVarint32(dst, kDeletedFile);
    PutVarint32(dst, iter->first);   // level
    PutVarint64(dst, iter->second);  // file number
  }

  for (size_t i = 0; i < new_files_.size(); i++) {
    const FileMetaData& f = new_files_[i].second;
    PutVarint32(dst, kNewFile);
    PutVarint32(dst, new_files_[i].first);  // level
    PutVarint64(dst, f.number);
    PutVarint64(dst, f.file_size);
    PutLengthPrefixedSlice(dst, f.smallest.Encode());
    PutLengthPrefixedSlice(dst, f.largest.Encode());
  }
}

static bool GetInternalKey(Slice* input, InternalKey* dst) {
  Slice str;
  if (GetLengthPrefixedSlice(input, &str)) {
    dst->DecodeFrom(str);
    return true;
  } else {
    return false;
  }
}

static bool GetLevel(Slice* input, int* level) {
  uint32_t v;
<<<<<<< HEAD
<<<<<<< HEAD
  if (GetVarint32(input, &v) && v < config::kNumLevels) {
=======
  if (GetVarint32(input, &v) &&
      v < config::kNumLevels) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  if (GetVarint32(input, &v) &&
      v < config::kNumLevels) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    *level = v;
    return true;
  } else {
    return false;
  }
}

Status VersionEdit::DecodeFrom(const Slice& src) {
  Clear();
  Slice input = src;
<<<<<<< HEAD
<<<<<<< HEAD
  const char* msg = nullptr;
=======
  const char* msg = NULL;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  const char* msg = NULL;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  uint32_t tag;

  // Temporary storage for parsing
  int level;
  uint64_t number;
  FileMetaData f;
  Slice str;
  InternalKey key;

<<<<<<< HEAD
<<<<<<< HEAD
  while (msg == nullptr && GetVarint32(&input, &tag)) {
=======
  while (msg == NULL && GetVarint32(&input, &tag)) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  while (msg == NULL && GetVarint32(&input, &tag)) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    switch (tag) {
      case kComparator:
        if (GetLengthPrefixedSlice(&input, &str)) {
          comparator_ = str.ToString();
          has_comparator_ = true;
        } else {
          msg = "comparator name";
        }
        break;

      case kLogNumber:
        if (GetVarint64(&input, &log_number_)) {
          has_log_number_ = true;
        } else {
          msg = "log number";
        }
        break;

      case kPrevLogNumber:
        if (GetVarint64(&input, &prev_log_number_)) {
          has_prev_log_number_ = true;
        } else {
          msg = "previous log number";
        }
        break;

      case kNextFileNumber:
        if (GetVarint64(&input, &next_file_number_)) {
          has_next_file_number_ = true;
        } else {
          msg = "next file number";
        }
        break;

      case kLastSequence:
        if (GetVarint64(&input, &last_sequence_)) {
          has_last_sequence_ = true;
        } else {
          msg = "last sequence number";
        }
        break;

      case kCompactPointer:
<<<<<<< HEAD
<<<<<<< HEAD
        if (GetLevel(&input, &level) && GetInternalKey(&input, &key)) {
=======
        if (GetLevel(&input, &level) &&
            GetInternalKey(&input, &key)) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
        if (GetLevel(&input, &level) &&
            GetInternalKey(&input, &key)) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
          compact_pointers_.push_back(std::make_pair(level, key));
        } else {
          msg = "compaction pointer";
        }
        break;

      case kDeletedFile:
<<<<<<< HEAD
<<<<<<< HEAD
        if (GetLevel(&input, &level) && GetVarint64(&input, &number)) {
=======
        if (GetLevel(&input, &level) &&
            GetVarint64(&input, &number)) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
        if (GetLevel(&input, &level) &&
            GetVarint64(&input, &number)) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
          deleted_files_.insert(std::make_pair(level, number));
        } else {
          msg = "deleted file";
        }
        break;

      case kNewFile:
<<<<<<< HEAD
<<<<<<< HEAD
        if (GetLevel(&input, &level) && GetVarint64(&input, &f.number) &&
=======
        if (GetLevel(&input, &level) &&
            GetVarint64(&input, &f.number) &&
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
        if (GetLevel(&input, &level) &&
            GetVarint64(&input, &f.number) &&
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
            GetVarint64(&input, &f.file_size) &&
            GetInternalKey(&input, &f.smallest) &&
            GetInternalKey(&input, &f.largest)) {
          new_files_.push_back(std::make_pair(level, f));
        } else {
          msg = "new-file entry";
        }
        break;

      default:
        msg = "unknown tag";
        break;
    }
  }

<<<<<<< HEAD
<<<<<<< HEAD
  if (msg == nullptr && !input.empty()) {
=======
  if (msg == NULL && !input.empty()) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  if (msg == NULL && !input.empty()) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    msg = "invalid tag";
  }

  Status result;
<<<<<<< HEAD
<<<<<<< HEAD
  if (msg != nullptr) {
=======
  if (msg != NULL) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  if (msg != NULL) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    result = Status::Corruption("VersionEdit", msg);
  }
  return result;
}

std::string VersionEdit::DebugString() const {
  std::string r;
  r.append("VersionEdit {");
  if (has_comparator_) {
    r.append("\n  Comparator: ");
    r.append(comparator_);
  }
  if (has_log_number_) {
    r.append("\n  LogNumber: ");
    AppendNumberTo(&r, log_number_);
  }
  if (has_prev_log_number_) {
    r.append("\n  PrevLogNumber: ");
    AppendNumberTo(&r, prev_log_number_);
  }
  if (has_next_file_number_) {
    r.append("\n  NextFile: ");
    AppendNumberTo(&r, next_file_number_);
  }
  if (has_last_sequence_) {
    r.append("\n  LastSeq: ");
    AppendNumberTo(&r, last_sequence_);
  }
  for (size_t i = 0; i < compact_pointers_.size(); i++) {
    r.append("\n  CompactPointer: ");
    AppendNumberTo(&r, compact_pointers_[i].first);
    r.append(" ");
    r.append(compact_pointers_[i].second.DebugString());
  }
  for (DeletedFileSet::const_iterator iter = deleted_files_.begin();
<<<<<<< HEAD
<<<<<<< HEAD
       iter != deleted_files_.end(); ++iter) {
=======
       iter != deleted_files_.end();
       ++iter) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
       iter != deleted_files_.end();
       ++iter) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    r.append("\n  DeleteFile: ");
    AppendNumberTo(&r, iter->first);
    r.append(" ");
    AppendNumberTo(&r, iter->second);
  }
  for (size_t i = 0; i < new_files_.size(); i++) {
    const FileMetaData& f = new_files_[i].second;
    r.append("\n  AddFile: ");
    AppendNumberTo(&r, new_files_[i].first);
    r.append(" ");
    AppendNumberTo(&r, f.number);
    r.append(" ");
    AppendNumberTo(&r, f.file_size);
    r.append(" ");
    r.append(f.smallest.DebugString());
    r.append(" .. ");
    r.append(f.largest.DebugString());
  }
  r.append("\n}\n");
  return r;
}

}  // namespace leveldb
