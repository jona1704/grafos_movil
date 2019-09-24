// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.
//
// File names used by DB code

#ifndef STORAGE_LEVELDB_DB_FILENAME_H_
#define STORAGE_LEVELDB_DB_FILENAME_H_

#include <stdint.h>
<<<<<<< HEAD
<<<<<<< HEAD

#include <string>

=======
#include <string>
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
#include <string>
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#include "leveldb/slice.h"
#include "leveldb/status.h"
#include "port/port.h"

namespace leveldb {

class Env;

enum FileType {
  kLogFile,
  kDBLockFile,
  kTableFile,
  kDescriptorFile,
  kCurrentFile,
  kTempFile,
  kInfoLogFile  // Either the current one, or an old one
};

// Return the name of the log file with the specified number
// in the db named by "dbname".  The result will be prefixed with
// "dbname".
<<<<<<< HEAD
<<<<<<< HEAD
std::string LogFileName(const std::string& dbname, uint64_t number);
=======
extern std::string LogFileName(const std::string& dbname, uint64_t number);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
extern std::string LogFileName(const std::string& dbname, uint64_t number);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

// Return the name of the sstable with the specified number
// in the db named by "dbname".  The result will be prefixed with
// "dbname".
<<<<<<< HEAD
<<<<<<< HEAD
std::string TableFileName(const std::string& dbname, uint64_t number);
=======
extern std::string TableFileName(const std::string& dbname, uint64_t number);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
extern std::string TableFileName(const std::string& dbname, uint64_t number);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

// Return the legacy file name for an sstable with the specified number
// in the db named by "dbname". The result will be prefixed with
// "dbname".
<<<<<<< HEAD
<<<<<<< HEAD
std::string SSTTableFileName(const std::string& dbname, uint64_t number);
=======
extern std::string SSTTableFileName(const std::string& dbname, uint64_t number);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
extern std::string SSTTableFileName(const std::string& dbname, uint64_t number);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

// Return the name of the descriptor file for the db named by
// "dbname" and the specified incarnation number.  The result will be
// prefixed with "dbname".
<<<<<<< HEAD
<<<<<<< HEAD
std::string DescriptorFileName(const std::string& dbname, uint64_t number);
=======
extern std::string DescriptorFileName(const std::string& dbname,
                                      uint64_t number);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
extern std::string DescriptorFileName(const std::string& dbname,
                                      uint64_t number);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

// Return the name of the current file.  This file contains the name
// of the current manifest file.  The result will be prefixed with
// "dbname".
<<<<<<< HEAD
<<<<<<< HEAD
std::string CurrentFileName(const std::string& dbname);

// Return the name of the lock file for the db named by
// "dbname".  The result will be prefixed with "dbname".
std::string LockFileName(const std::string& dbname);

// Return the name of a temporary file owned by the db named "dbname".
// The result will be prefixed with "dbname".
std::string TempFileName(const std::string& dbname, uint64_t number);

// Return the name of the info log file for "dbname".
std::string InfoLogFileName(const std::string& dbname);

// Return the name of the old info log file for "dbname".
std::string OldInfoLogFileName(const std::string& dbname);
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
extern std::string CurrentFileName(const std::string& dbname);

// Return the name of the lock file for the db named by
// "dbname".  The result will be prefixed with "dbname".
extern std::string LockFileName(const std::string& dbname);

// Return the name of a temporary file owned by the db named "dbname".
// The result will be prefixed with "dbname".
extern std::string TempFileName(const std::string& dbname, uint64_t number);

// Return the name of the info log file for "dbname".
extern std::string InfoLogFileName(const std::string& dbname);

// Return the name of the old info log file for "dbname".
extern std::string OldInfoLogFileName(const std::string& dbname);
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

// If filename is a leveldb file, store the type of the file in *type.
// The number encoded in the filename is stored in *number.  If the
// filename was successfully parsed, returns true.  Else return false.
<<<<<<< HEAD
<<<<<<< HEAD
bool ParseFileName(const std::string& filename, uint64_t* number,
                   FileType* type);

// Make the CURRENT file point to the descriptor file with the
// specified number.
Status SetCurrentFile(Env* env, const std::string& dbname,
                      uint64_t descriptor_number);
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
extern bool ParseFileName(const std::string& filename,
                          uint64_t* number,
                          FileType* type);

// Make the CURRENT file point to the descriptor file with the
// specified number.
extern Status SetCurrentFile(Env* env, const std::string& dbname,
                             uint64_t descriptor_number);

<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

}  // namespace leveldb

#endif  // STORAGE_LEVELDB_DB_FILENAME_H_
