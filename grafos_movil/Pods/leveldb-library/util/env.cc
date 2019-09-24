// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#include "leveldb/env.h"

namespace leveldb {

<<<<<<< HEAD
<<<<<<< HEAD
Env::~Env() {}
=======
Env::~Env() {
}
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
Env::~Env() {
}
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

Status Env::NewAppendableFile(const std::string& fname, WritableFile** result) {
  return Status::NotSupported("NewAppendableFile", fname);
}

<<<<<<< HEAD
<<<<<<< HEAD
SequentialFile::~SequentialFile() {}

RandomAccessFile::~RandomAccessFile() {}

WritableFile::~WritableFile() {}

Logger::~Logger() {}

FileLock::~FileLock() {}

void Log(Logger* info_log, const char* format, ...) {
  if (info_log != nullptr) {
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
SequentialFile::~SequentialFile() {
}

RandomAccessFile::~RandomAccessFile() {
}

WritableFile::~WritableFile() {
}

Logger::~Logger() {
}

FileLock::~FileLock() {
}

void Log(Logger* info_log, const char* format, ...) {
  if (info_log != NULL) {
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    va_list ap;
    va_start(ap, format);
    info_log->Logv(format, ap);
    va_end(ap);
  }
}

static Status DoWriteStringToFile(Env* env, const Slice& data,
<<<<<<< HEAD
<<<<<<< HEAD
                                  const std::string& fname, bool should_sync) {
=======
                                  const std::string& fname,
                                  bool should_sync) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
                                  const std::string& fname,
                                  bool should_sync) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  WritableFile* file;
  Status s = env->NewWritableFile(fname, &file);
  if (!s.ok()) {
    return s;
  }
  s = file->Append(data);
  if (s.ok() && should_sync) {
    s = file->Sync();
  }
  if (s.ok()) {
    s = file->Close();
  }
  delete file;  // Will auto-close if we did not close above
  if (!s.ok()) {
    env->DeleteFile(fname);
  }
  return s;
}

Status WriteStringToFile(Env* env, const Slice& data,
                         const std::string& fname) {
  return DoWriteStringToFile(env, data, fname, false);
}

Status WriteStringToFileSync(Env* env, const Slice& data,
                             const std::string& fname) {
  return DoWriteStringToFile(env, data, fname, true);
}

Status ReadFileToString(Env* env, const std::string& fname, std::string* data) {
  data->clear();
  SequentialFile* file;
  Status s = env->NewSequentialFile(fname, &file);
  if (!s.ok()) {
    return s;
  }
  static const int kBufferSize = 8192;
  char* space = new char[kBufferSize];
  while (true) {
    Slice fragment;
    s = file->Read(kBufferSize, &fragment, space);
    if (!s.ok()) {
      break;
    }
    data->append(fragment.data(), fragment.size());
    if (fragment.empty()) {
      break;
    }
  }
  delete[] space;
  delete file;
  return s;
}

<<<<<<< HEAD
<<<<<<< HEAD
EnvWrapper::~EnvWrapper() {}
=======
EnvWrapper::~EnvWrapper() {
}
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
EnvWrapper::~EnvWrapper() {
}
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

}  // namespace leveldb
