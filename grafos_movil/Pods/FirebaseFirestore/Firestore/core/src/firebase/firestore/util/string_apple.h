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

#ifndef FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_UTIL_STRING_APPLE_H_
#define FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_UTIL_STRING_APPLE_H_

#if defined(__APPLE__)
#import <CoreFoundation/CoreFoundation.h>

#if defined(__OBJC__)
#import <Foundation/Foundation.h>
#endif

#include <memory>
#include <string>

#include "absl/strings/string_view.h"

CF_ASSUME_NONNULL_BEGIN

namespace firebase {
namespace firestore {
namespace util {

/**
 * Returns a copy of the given CFString (or NSString) encoded in UTF-8.
 */
std::string MakeString(CFStringRef str);

inline CFStringRef MakeCFString(absl::string_view contents) {
  auto bytes = reinterpret_cast<const UInt8*>(contents.data());
  return CFStringCreateWithBytes(kCFAllocatorDefault, bytes, contents.size(),
                                 kCFStringEncodingUTF8, false);
}

#if defined(__OBJC__)

// Translates a C string to the equivalent NSString without making a copy.
inline NSString* MakeNSStringNoCopy(const char* c_str, size_t size) {
  return [[NSString alloc]
      initWithBytesNoCopy:const_cast<void*>(static_cast<const void*>(c_str))
                   length:size
                 encoding:NSUTF8StringEncoding
             freeWhenDone:false];
}

// Translates a string_view to the equivalent NSString without making a copy.
<<<<<<< HEAD
<<<<<<< HEAD
inline NSString* MakeNSStringNoCopy(absl::string_view str) {
=======
inline NSString* MakeNSStringNoCopy(const absl::string_view str) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
inline NSString* MakeNSStringNoCopy(const absl::string_view str) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  return MakeNSStringNoCopy(str.data(), str.size());
}

// Translates a string_view string to the equivalent NSString by making a copy.
<<<<<<< HEAD
<<<<<<< HEAD
inline NSString* MakeNSString(absl::string_view str) {
=======
inline NSString* MakeNSString(const absl::string_view str) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
inline NSString* MakeNSString(const absl::string_view str) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  return [[NSString alloc]
      initWithBytes:const_cast<void*>(static_cast<const void*>(str.data()))
             length:str.length()
           encoding:NSUTF8StringEncoding];
}

// Translates a nullable pointer to string to the equivalent NSString by making
// a copy.
inline NSString* _Nullable MakeNSString(
    const std::shared_ptr<const std::string>& str) {
  return str ? MakeNSString(*str) : nil;
}

// Creates an absl::string_view wrapper for the contents of the given
// NSString.
inline absl::string_view MakeStringView(NSString* str) {
  return absl::string_view(
      [str UTF8String], [str lengthOfBytesUsingEncoding:NSUTF8StringEncoding]);
}

// Creates a std::string wrapper for the contents of the given NSString.
inline std::string MakeString(NSString* str) {
  CFStringRef cf_str = (__bridge CFStringRef)str;
  return MakeString(cf_str);
}

// Creates a nullable shared_ptr pointing to a string for the contents of the
// given NSString, or nullptr if it's nil.
inline std::shared_ptr<const std::string> MakeStringPtr(
    NSString* _Nullable str) {
  if (!str) return nullptr;
  return std::make_shared<const std::string>(MakeString(str));
}

#endif  // defined(__OBJC__)

}  // namespace util
}  // namespace firestore
}  // namespace firebase

CF_ASSUME_NONNULL_END

#endif  // defined(__APPLE__)
#endif  // FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_UTIL_STRING_APPLE_H_
