/*
 * Copyright 2019 Google
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

#ifndef FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_NANOPB_NANOPB_UTIL_H_
#define FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_NANOPB_NANOPB_UTIL_H_

#include <pb.h>

#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

#include "Firestore/core/src/firebase/firestore/nanopb/byte_string.h"
#include "Firestore/core/src/firebase/firestore/util/hard_assert.h"
<<<<<<< HEAD
#include "Firestore/core/src/firebase/firestore/util/nullability.h"
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

namespace firebase {
namespace firestore {
namespace nanopb {

/**
 * Static casts the given size_t value down to a nanopb compatible size, after
 * asserting that the value isn't out of range.
 */
inline pb_size_t CheckedSize(size_t size) {
  HARD_ASSERT(size <= PB_SIZE_MAX,
              "Size exceeds nanopb limits. Too many entries.");
  return static_cast<pb_size_t>(size);
}

/**
 * Creates a new, null-terminated byte array that's a copy of the bytes in the
 * given buffer. Returns a null instance if the given buffer is null or empty.
 */
<<<<<<< HEAD
pb_bytes_array_t* _Nullable CopyBytesArray(
    const pb_bytes_array_t* _Nullable buffer);
=======
pb_bytes_array_t* CopyBytesArray(const pb_bytes_array_t* buffer);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

/**
 * Creates a new, null-terminated byte array that's a copy of the given bytes.
 * Returns a null instance if the given size is zero.
 */
<<<<<<< HEAD
pb_bytes_array_t* _Nullable MakeBytesArray(const void* _Nullable data,
                                           size_t size);
=======
pb_bytes_array_t* MakeBytesArray(const void* data, size_t size);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

/**
 * Creates a new, null-terminated byte array that's a copy of the given bytes.
 * Returns a null instance if the size of the given vector is zero.
 */
<<<<<<< HEAD
inline pb_bytes_array_t* _Nullable MakeBytesArray(
    const std::vector<uint8_t>& bytes) {
=======
inline pb_bytes_array_t* MakeBytesArray(const std::vector<uint8_t>& bytes) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  return MakeBytesArray(bytes.data(), bytes.size());
}

/**
 * Creates a string_view of the given nanopb bytes.
 */
<<<<<<< HEAD
absl::string_view MakeStringView(const pb_bytes_array_t* _Nullable str);

/**
 * Creates a string_view of the given nanopb bytes.
 */
absl::string_view MakeStringView(const ByteString& bytes);

inline pb_bytes_array_t* _Nullable MakeBytesArray(const std::string& str) {
  return MakeBytesArray(str.data(), str.size());
}

std::string MakeString(const pb_bytes_array_t* _Nullable str);
=======
absl::string_view MakeStringView(const ByteString& bytes);

inline pb_bytes_array_t* MakeBytesArray(const std::string& str) {
  return MakeBytesArray(str.data(), str.size());
}

std::string MakeString(const pb_bytes_array_t* str);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

/**
 * Copies the backing byte array into a new vector of bytes.
 */
inline std::vector<uint8_t> MakeVector(const ByteString& str) {
  return {str.begin(), str.end()};
}

#if __OBJC__
<<<<<<< HEAD
inline ByteString MakeByteString(NSData* _Nullable value) {
  if (value == nil) return ByteString();

=======
inline ByteString MakeByteString(NSData* value) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  auto size = static_cast<size_t>(value.length);
  return ByteString::Take(MakeBytesArray(value.bytes, size));
}

<<<<<<< HEAD
inline NSData* _Nonnull MakeNSData(const ByteString& str) {
  return [[NSData alloc] initWithBytes:str.data() length:str.size()];
}

inline NSData* _Nullable MakeNullableNSData(const ByteString& str) {
  if (str.empty()) return nil;
  return MakeNSData(str);
}
=======
inline NSData* MakeNSData(const ByteString& str) {
  return [[NSData alloc] initWithBytes:str.data() length:str.size()];
}
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#endif

}  // namespace nanopb
}  // namespace firestore
}  // namespace firebase

#endif  // FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_NANOPB_NANOPB_UTIL_H_
