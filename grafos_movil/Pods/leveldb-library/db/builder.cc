// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#include "db/builder.h"

<<<<<<< HEAD
#include "db/dbformat.h"
#include "db/filename.h"
=======
#include "db/filename.h"
#include "db/dbformat.h"
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#include "db/table_cache.h"
#include "db/version_edit.h"
#include "leveldb/db.h"
#include "leveldb/env.h"
#include "leveldb/iterator.h"

namespace leveldb {

<<<<<<< HEAD
Status BuildTable(const std::string& dbname, Env* env, const Options& options,
                  TableCache* table_cache, Iterator* iter, FileMetaData* meta) {
=======
Status BuildTable(const std::string& dbname,
                  Env* env,
                  const Options& options,
                  TableCache* table_cache,
                  Iterator* iter,
                  FileMetaData* meta) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  Status s;
  meta->file_size = 0;
  iter->SeekToFirst();

  std::string fname = TableFileName(dbname, meta->number);
  if (iter->Valid()) {
    WritableFile* file;
    s = env->NewWritableFile(fname, &file);
    if (!s.ok()) {
      return s;
    }

    TableBuilder* builder = new TableBuilder(options, file);
    meta->smallest.DecodeFrom(iter->key());
    for (; iter->Valid(); iter->Next()) {
      Slice key = iter->key();
      meta->largest.DecodeFrom(key);
      builder->Add(key, iter->value());
    }

    // Finish and check for builder errors
<<<<<<< HEAD
    s = builder->Finish();
    if (s.ok()) {
      meta->file_size = builder->FileSize();
      assert(meta->file_size > 0);
=======
    if (s.ok()) {
      s = builder->Finish();
      if (s.ok()) {
        meta->file_size = builder->FileSize();
        assert(meta->file_size > 0);
      }
    } else {
      builder->Abandon();
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    }
    delete builder;

    // Finish and check for file errors
    if (s.ok()) {
      s = file->Sync();
    }
    if (s.ok()) {
      s = file->Close();
    }
    delete file;
<<<<<<< HEAD
    file = nullptr;

    if (s.ok()) {
      // Verify that the table is usable
      Iterator* it = table_cache->NewIterator(ReadOptions(), meta->number,
=======
    file = NULL;

    if (s.ok()) {
      // Verify that the table is usable
      Iterator* it = table_cache->NewIterator(ReadOptions(),
                                              meta->number,
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
                                              meta->file_size);
      s = it->status();
      delete it;
    }
  }

  // Check for input iterator errors
  if (!iter->status().ok()) {
    s = iter->status();
  }

  if (s.ok() && meta->file_size > 0) {
    // Keep it
  } else {
    env->DeleteFile(fname);
  }
  return s;
}

}  // namespace leveldb
