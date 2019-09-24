// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.
//
// Must not be included from any .h files to avoid polluting the namespace
// with macros.

#ifndef STORAGE_LEVELDB_UTIL_LOGGING_H_
#define STORAGE_LEVELDB_UTIL_LOGGING_H_

<<<<<<< HEAD
#include <stdint.h>
#include <stdio.h>

#include <string>

=======
#include <stdio.h>
#include <stdint.h>
#include <string>
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#include "port/port.h"

namespace leveldb {

class Slice;
class WritableFile;

// Append a human-readable printout of "num" to *str
<<<<<<< HEAD
void AppendNumberTo(std::string* str, uint64_t num);

// Append a human-readable printout of "value" to *str.
// Escapes any non-printable characters found in "value".
void AppendEscapedStringTo(std::string* str, const Slice& value);

// Return a human-readable printout of "num"
std::string NumberToString(uint64_t num);

// Return a human-readable version of "value".
// Escapes any non-printable characters found in "value".
std::string EscapeString(const Slice& value);
=======
extern void AppendNumberTo(std::string* str, uint64_t num);

// Append a human-readable printout of "value" to *str.
// Escapes any non-printable characters found in "value".
extern void AppendEscapedStringTo(std::string* str, const Slice& value);

// Return a human-readable printout of "num"
extern std::string NumberToString(uint64_t num);

// Return a human-readable version of "value".
// Escapes any non-printable characters found in "value".
extern std::string EscapeString(const Slice& value);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

// Parse a human-readable number from "*in" into *value.  On success,
// advances "*in" past the consumed number and sets "*val" to the
// numeric value.  Otherwise, returns false and leaves *in in an
// unspecified state.
<<<<<<< HEAD
bool ConsumeDecimalNumber(Slice* in, uint64_t* val);
=======
extern bool ConsumeDecimalNumber(Slice* in, uint64_t* val);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

}  // namespace leveldb

#endif  // STORAGE_LEVELDB_UTIL_LOGGING_H_
