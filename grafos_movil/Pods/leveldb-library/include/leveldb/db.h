// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#ifndef STORAGE_LEVELDB_INCLUDE_DB_H_
#define STORAGE_LEVELDB_INCLUDE_DB_H_

#include <stdint.h>
#include <stdio.h>
<<<<<<< HEAD

#include "leveldb/export.h"
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#include "leveldb/iterator.h"
#include "leveldb/options.h"

namespace leveldb {

<<<<<<< HEAD
// Update CMakeLists.txt if you change these
static const int kMajorVersion = 1;
static const int kMinorVersion = 22;
=======
// Update Makefile if you change these
static const int kMajorVersion = 1;
static const int kMinorVersion = 20;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

struct Options;
struct ReadOptions;
struct WriteOptions;
class WriteBatch;

// Abstract handle to particular state of a DB.
// A Snapshot is an immutable object and can therefore be safely
// accessed from multiple threads without any external synchronization.
<<<<<<< HEAD
class LEVELDB_EXPORT Snapshot {
=======
class Snapshot {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
 protected:
  virtual ~Snapshot();
};

// A range of keys
<<<<<<< HEAD
struct LEVELDB_EXPORT Range {
  Range() {}
  Range(const Slice& s, const Slice& l) : start(s), limit(l) {}

  Slice start;  // Included in the range
  Slice limit;  // Not included in the range
=======
struct Range {
  Slice start;          // Included in the range
  Slice limit;          // Not included in the range

  Range() { }
  Range(const Slice& s, const Slice& l) : start(s), limit(l) { }
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
};

// A DB is a persistent ordered map from keys to values.
// A DB is safe for concurrent access from multiple threads without
// any external synchronization.
<<<<<<< HEAD
class LEVELDB_EXPORT DB {
=======
class DB {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
 public:
  // Open the database with the specified "name".
  // Stores a pointer to a heap-allocated database in *dbptr and returns
  // OK on success.
<<<<<<< HEAD
  // Stores nullptr in *dbptr and returns a non-OK status on error.
  // Caller should delete *dbptr when it is no longer needed.
  static Status Open(const Options& options, const std::string& name,
                     DB** dbptr);

  DB() = default;

  DB(const DB&) = delete;
  DB& operator=(const DB&) = delete;

=======
  // Stores NULL in *dbptr and returns a non-OK status on error.
  // Caller should delete *dbptr when it is no longer needed.
  static Status Open(const Options& options,
                     const std::string& name,
                     DB** dbptr);

  DB() { }
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  virtual ~DB();

  // Set the database entry for "key" to "value".  Returns OK on success,
  // and a non-OK status on error.
  // Note: consider setting options.sync = true.
<<<<<<< HEAD
  virtual Status Put(const WriteOptions& options, const Slice& key,
=======
  virtual Status Put(const WriteOptions& options,
                     const Slice& key,
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
                     const Slice& value) = 0;

  // Remove the database entry (if any) for "key".  Returns OK on
  // success, and a non-OK status on error.  It is not an error if "key"
  // did not exist in the database.
  // Note: consider setting options.sync = true.
  virtual Status Delete(const WriteOptions& options, const Slice& key) = 0;

  // Apply the specified updates to the database.
  // Returns OK on success, non-OK on failure.
  // Note: consider setting options.sync = true.
  virtual Status Write(const WriteOptions& options, WriteBatch* updates) = 0;

  // If the database contains an entry for "key" store the
  // corresponding value in *value and return OK.
  //
  // If there is no entry for "key" leave *value unchanged and return
  // a status for which Status::IsNotFound() returns true.
  //
  // May return some other Status on an error.
<<<<<<< HEAD
  virtual Status Get(const ReadOptions& options, const Slice& key,
                     std::string* value) = 0;
=======
  virtual Status Get(const ReadOptions& options,
                     const Slice& key, std::string* value) = 0;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

  // Return a heap-allocated iterator over the contents of the database.
  // The result of NewIterator() is initially invalid (caller must
  // call one of the Seek methods on the iterator before using it).
  //
  // Caller should delete the iterator when it is no longer needed.
  // The returned iterator should be deleted before this db is deleted.
  virtual Iterator* NewIterator(const ReadOptions& options) = 0;

  // Return a handle to the current DB state.  Iterators created with
  // this handle will all observe a stable snapshot of the current DB
  // state.  The caller must call ReleaseSnapshot(result) when the
  // snapshot is no longer needed.
  virtual const Snapshot* GetSnapshot() = 0;

  // Release a previously acquired snapshot.  The caller must not
  // use "snapshot" after this call.
  virtual void ReleaseSnapshot(const Snapshot* snapshot) = 0;

  // DB implementations can export properties about their state
  // via this method.  If "property" is a valid property understood by this
  // DB implementation, fills "*value" with its current value and returns
  // true.  Otherwise returns false.
  //
  //
  // Valid property names include:
  //
  //  "leveldb.num-files-at-level<N>" - return the number of files at level <N>,
  //     where <N> is an ASCII representation of a level number (e.g. "0").
  //  "leveldb.stats" - returns a multi-line string that describes statistics
  //     about the internal operation of the DB.
  //  "leveldb.sstables" - returns a multi-line string that describes all
  //     of the sstables that make up the db contents.
  //  "leveldb.approximate-memory-usage" - returns the approximate number of
  //     bytes of memory in use by the DB.
  virtual bool GetProperty(const Slice& property, std::string* value) = 0;

  // For each i in [0,n-1], store in "sizes[i]", the approximate
  // file system space used by keys in "[range[i].start .. range[i].limit)".
  //
  // Note that the returned sizes measure file system space usage, so
  // if the user data compresses by a factor of ten, the returned
  // sizes will be one-tenth the size of the corresponding user data size.
  //
  // The results may not include the sizes of recently written data.
  virtual void GetApproximateSizes(const Range* range, int n,
                                   uint64_t* sizes) = 0;

  // Compact the underlying storage for the key range [*begin,*end].
  // In particular, deleted and overwritten versions are discarded,
  // and the data is rearranged to reduce the cost of operations
  // needed to access the data.  This operation should typically only
  // be invoked by users who understand the underlying implementation.
  //
<<<<<<< HEAD
  // begin==nullptr is treated as a key before all keys in the database.
  // end==nullptr is treated as a key after all keys in the database.
  // Therefore the following call will compact the entire database:
  //    db->CompactRange(nullptr, nullptr);
  virtual void CompactRange(const Slice* begin, const Slice* end) = 0;
=======
  // begin==NULL is treated as a key before all keys in the database.
  // end==NULL is treated as a key after all keys in the database.
  // Therefore the following call will compact the entire database:
  //    db->CompactRange(NULL, NULL);
  virtual void CompactRange(const Slice* begin, const Slice* end) = 0;

 private:
  // No copying allowed
  DB(const DB&);
  void operator=(const DB&);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
};

// Destroy the contents of the specified database.
// Be very careful using this method.
<<<<<<< HEAD
//
// Note: For backwards compatibility, if DestroyDB is unable to list the
// database files, Status::OK() will still be returned masking this failure.
LEVELDB_EXPORT Status DestroyDB(const std::string& name,
                                const Options& options);
=======
Status DestroyDB(const std::string& name, const Options& options);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

// If a DB cannot be opened, you may attempt to call this method to
// resurrect as much of the contents of the database as possible.
// Some data may be lost, so be careful when calling this function
// on a database that contains important information.
<<<<<<< HEAD
LEVELDB_EXPORT Status RepairDB(const std::string& dbname,
                               const Options& options);
=======
Status RepairDB(const std::string& dbname, const Options& options);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

}  // namespace leveldb

#endif  // STORAGE_LEVELDB_INCLUDE_DB_H_