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

#include "Firestore/core/src/firebase/firestore/util/status.h"

#include <cerrno>

#include "Firestore/core/src/firebase/firestore/util/strerror.h"
#include "Firestore/core/src/firebase/firestore/util/string_format.h"

namespace firebase {
namespace firestore {
namespace util {

/// Returns the Canonical error code for the given errno value.
<<<<<<< HEAD
<<<<<<< HEAD
static Error CodeForErrno(int errno_code) {
  switch (errno_code) {
    case 0:
      return Error::Ok;
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
static FirestoreErrorCode CodeForErrno(int errno_code) {
  switch (errno_code) {
    case 0:
      return FirestoreErrorCode::Ok;
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

      // Internal canonical mappings call these failed preconditions, but for
      // our purposes these must indicate an internal error in file handling.
    case EBADF:  // Invalid file descriptor
#if defined(EBADFD)
    case EBADFD:  // File descriptor in bad state
#endif
<<<<<<< HEAD
<<<<<<< HEAD
      return Error::Internal;
=======
      return FirestoreErrorCode::Internal;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
      return FirestoreErrorCode::Internal;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

    case EINVAL:        // Invalid argument
    case ENAMETOOLONG:  // Filename too long
    case E2BIG:         // Argument list too long
    case EDESTADDRREQ:  // Destination address required
    case EDOM:          // Mathematics argument out of domain of function
    case EFAULT:        // Bad address
    case EILSEQ:        // Illegal byte sequence
    case ENOPROTOOPT:   // Protocol not available
    case ENOSTR:        // Not a STREAM
    case ENOTSOCK:      // Not a socket
    case ENOTTY:        // Inappropriate I/O control operation
    case EPROTOTYPE:    // Protocol wrong type for socket
    case ESPIPE:        // Invalid seek
<<<<<<< HEAD
<<<<<<< HEAD
      return Error::InvalidArgument;

    case ETIMEDOUT:  // Connection timed out
    case ETIME:      // Timer expired
      return Error::DeadlineExceeded;
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
      return FirestoreErrorCode::InvalidArgument;

    case ETIMEDOUT:  // Connection timed out
    case ETIME:      // Timer expired
      return FirestoreErrorCode::DeadlineExceeded;
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

    case ENODEV:  // No such device
    case ENOENT:  // No such file or directory
#if defined(ENOMEDIUM)
    case ENOMEDIUM:  // No medium found
#endif
    case ENXIO:  // No such device or address
    case ESRCH:  // No such process
<<<<<<< HEAD
<<<<<<< HEAD
      return Error::NotFound;
=======
      return FirestoreErrorCode::NotFound;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
      return FirestoreErrorCode::NotFound;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

    case EEXIST:         // File exists
    case EADDRNOTAVAIL:  // Address not available
    case EALREADY:       // Connection already in progress
#if defined(ENOTUNIQ)
    case ENOTUNIQ:  // Name not unique on network
#endif
<<<<<<< HEAD
<<<<<<< HEAD
      return Error::AlreadyExists;
=======
      return FirestoreErrorCode::AlreadyExists;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
      return FirestoreErrorCode::AlreadyExists;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

    case EPERM:   // Operation not permitted
    case EACCES:  // Permission denied
#if defined(ENOKEY)
    case ENOKEY:  // Required key not available
#endif
    case EROFS:  // Read only file system
<<<<<<< HEAD
<<<<<<< HEAD
      return Error::PermissionDenied;
=======
      return FirestoreErrorCode::PermissionDenied;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
      return FirestoreErrorCode::PermissionDenied;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

    case ENOTEMPTY:   // Directory not empty
    case EISDIR:      // Is a directory
    case ENOTDIR:     // Not a directory
    case EADDRINUSE:  // Address already in use
    case EBUSY:       // Device or resource busy
    case ECHILD:      // No child processes
    case EISCONN:     // Socket is connected
#if defined(EISNAM)
    case EISNAM:  // Is a named type file
#endif
#if defined(ENOTBLK)
    case ENOTBLK:  // Block device required
#endif
    case ENOTCONN:  // The socket is not connected
    case EPIPE:     // Broken pipe
#if defined(ESHUTDOWN)
    case ESHUTDOWN:  // Cannot send after transport endpoint shutdown
#endif
    case ETXTBSY:  // Text file busy
#if defined(EUNATCH)
    case EUNATCH:  // Protocol driver not attached
#endif
<<<<<<< HEAD
<<<<<<< HEAD
      return Error::FailedPrecondition;
=======
      return FirestoreErrorCode::FailedPrecondition;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
      return FirestoreErrorCode::FailedPrecondition;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

    case ENOSPC:  // No space left on device
#if defined(EDQUOT)
    case EDQUOT:  // Disk quota exceeded
#endif
    case EMFILE:   // Too many open files
    case EMLINK:   // Too many links
    case ENFILE:   // Too many open files in system
    case ENOBUFS:  // No buffer space available
    case ENODATA:  // No message is available on the STREAM read queue
    case ENOMEM:   // Not enough space
    case ENOSR:    // No STREAM resources
#if defined(EUSERS)
    case EUSERS:  // Too many users
#endif
<<<<<<< HEAD
<<<<<<< HEAD
      return Error::ResourceExhausted;
=======
      return FirestoreErrorCode::ResourceExhausted;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
      return FirestoreErrorCode::ResourceExhausted;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

#if defined(ECHRNG)
    case ECHRNG:  // Channel number out of range
#endif
    case EFBIG:      // File too large
    case EOVERFLOW:  // Value too large to be stored in data type
    case ERANGE:     // Result too large
<<<<<<< HEAD
<<<<<<< HEAD
      return Error::OutOfRange;
=======
      return FirestoreErrorCode::OutOfRange;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
      return FirestoreErrorCode::OutOfRange;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

#if defined(ENOPKG)
    case ENOPKG:  // Package not installed
#endif
    case ENOSYS:        // Function not implemented
    case ENOTSUP:       // Operation not supported
    case EAFNOSUPPORT:  // Address family not supported
#if defined(EPFNOSUPPORT)
    case EPFNOSUPPORT:  // Protocol family not supported
#endif
    case EPROTONOSUPPORT:  // Protocol not supported
#if defined(ESOCKTNOSUPPORT)
    case ESOCKTNOSUPPORT:  // Socket type not supported
#endif
    case EXDEV:  // Improper link
<<<<<<< HEAD
<<<<<<< HEAD
      return Error::Unimplemented;
=======
      return FirestoreErrorCode::Unimplemented;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
      return FirestoreErrorCode::Unimplemented;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

    case EAGAIN:  // Resource temporarily unavailable
#if defined(ECOMM)
    case ECOMM:  // Communication error on send
#endif
    case ECONNREFUSED:  // Connection refused
    case ECONNABORTED:  // Connection aborted
    case ECONNRESET:    // Connection reset
    case EINTR:         // Interrupted function call
#if defined(EHOSTDOWN)
    case EHOSTDOWN:  // Host is down
#endif
    case EHOSTUNREACH:  // Host is unreachable
    case ENETDOWN:      // Network is down
    case ENETRESET:     // Connection aborted by network
    case ENETUNREACH:   // Network unreachable
    case ENOLCK:        // No locks available
    case ENOLINK:       // Link has been severed
#if defined(ENONET)
    case ENONET:  // Machine is not on the network
#endif
<<<<<<< HEAD
<<<<<<< HEAD
      return Error::Unavailable;
=======
      return FirestoreErrorCode::Unavailable;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
      return FirestoreErrorCode::Unavailable;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

    case EDEADLK:  // Resource deadlock avoided
#if defined(ESTALE)
    case ESTALE:  // Stale file handle
#endif
<<<<<<< HEAD
<<<<<<< HEAD
      return Error::Aborted;

    case ECANCELED:  // Operation cancelled
      return Error::Cancelled;

    default:
      return Error::Unknown;
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
      return FirestoreErrorCode::Aborted;

    case ECANCELED:  // Operation cancelled
      return FirestoreErrorCode::Cancelled;

    default:
      return FirestoreErrorCode::Unknown;
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  }
}

Status Status::FromErrno(int errno_code, absl::string_view msg) {
  if (errno_code == 0) {
    return Status::OK();
  }

<<<<<<< HEAD
<<<<<<< HEAD
  Error canonical_code = CodeForErrno(errno_code);
=======
  FirestoreErrorCode canonical_code = CodeForErrno(errno_code);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  FirestoreErrorCode canonical_code = CodeForErrno(errno_code);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  return Status{canonical_code,
                util::StringFormat("%s (errno %s: %s)", msg, errno_code,
                                   StrError(errno_code))};
}

}  // namespace util
}  // namespace firestore
}  // namespace firebase
