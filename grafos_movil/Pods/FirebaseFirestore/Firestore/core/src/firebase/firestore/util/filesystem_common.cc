/*
 * Copyright 2018 Google
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Firestore/core/src/firebase/firestore/util/filesystem_detail.h"

#include <fstream>
#include <sstream>

#include "Firestore/core/src/firebase/firestore/util/filesystem.h"
#include "Firestore/core/src/firebase/firestore/util/string_format.h"

using firebase::firestore::util::Path;

namespace firebase {
namespace firestore {
namespace util {
namespace detail {

Status RecursivelyDeleteDir(const Path& parent) {
  std::unique_ptr<DirectoryIterator> iter = DirectoryIterator::Create(parent);
  for (; iter->Valid(); iter->Next()) {
    Status status = RecursivelyDelete(iter->file());
    if (!status.ok()) {
      return status;
    }
  }
  if (!iter->status().ok()) {
<<<<<<< HEAD
    if (iter->status().code() == Error::NotFound) {
=======
    if (iter->status().code() == FirestoreErrorCode::NotFound) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
      return Status::OK();
    }
    return iter->status();
  }
  return detail::DeleteDir(parent);
}

}  // namespace detail

Status RecursivelyCreateDir(const Path& path) {
  Status result = detail::CreateDir(path);
<<<<<<< HEAD
  if (result.ok() || result.code() != Error::NotFound) {
=======
  if (result.ok() || result.code() != FirestoreErrorCode::NotFound) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    // Successfully created the directory, it already existed, or some other
    // unrecoverable error.
    return result;
  }

  // Missing parent
  Path parent = path.Dirname();
  result = RecursivelyCreateDir(parent);
  if (!result.ok()) {
    return result;
  }

  // Successfully created the parent so try again.
  return detail::CreateDir(path);
}

Status RecursivelyDelete(const Path& path) {
  Status status = IsDirectory(path);
  switch (status.code()) {
<<<<<<< HEAD
    case Error::Ok:
      return detail::RecursivelyDeleteDir(path);

    case Error::FailedPrecondition:
=======
    case FirestoreErrorCode::Ok:
      return detail::RecursivelyDeleteDir(path);

    case FirestoreErrorCode::FailedPrecondition:
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
      // Could be a file or something else. Attempt to delete it as a file
      // but otherwise allow that to fail if it's not a file.
      return detail::DeleteFile(path);

<<<<<<< HEAD
    case Error::NotFound:
=======
    case FirestoreErrorCode::NotFound:
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
      return Status::OK();

    default:
      return status;
  }
}

StatusOr<std::string> ReadFile(const Path& path) {
  std::ifstream file{path.native_value()};
  if (!file) {
    // TODO(varconst): more error details. This will require platform-specific
    // code, because `<iostream>` may not update `errno`.
<<<<<<< HEAD
    return Status{Error::Unknown,
=======
    return Status{FirestoreErrorCode::Unknown,
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
                  StringFormat("File at path '%s' cannot be opened",
                               path.ToUtf8String())};
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

}  // namespace util
}  // namespace firestore
}  // namespace firebase
