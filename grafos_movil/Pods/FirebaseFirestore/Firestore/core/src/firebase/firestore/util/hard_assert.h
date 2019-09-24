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

#ifndef FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_UTIL_HARD_ASSERT_H_
#define FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_UTIL_HARD_ASSERT_H_

#include <string>
#include <utility>

#include "Firestore/core/src/firebase/firestore/util/string_format.h"
<<<<<<< HEAD
<<<<<<< HEAD
#include "absl/base/optimization.h"
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

#if defined(_MSC_VER)
#define FIRESTORE_FUNCTION_NAME __FUNCSIG__
#else
#define FIRESTORE_FUNCTION_NAME __PRETTY_FUNCTION__
#endif

/**
<<<<<<< HEAD
<<<<<<< HEAD
 * Invokes the internal Fail function below with all the required contextual
 * information and passes additional arguments.
 *
 * @param message The failure message.
 * @param condition The string form of the expression that failed (optional)
 */
#define INVOKE_INTERNAL_FAIL(...)                                              \
  firebase::firestore::util::internal::Fail(__FILE__, FIRESTORE_FUNCTION_NAME, \
                                            __LINE__, __VA_ARGS__)

/**
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
 * Fails the current function if the given condition is false.
 *
 * Unlike assert(3) or NSAssert, this macro is never compiled out.
 *
 * @param condition The condition to test.
 * @param format (optional) A format string suitable for util::StringFormat.
 * @param ... format arguments to pass to util::StringFormat.
 */
<<<<<<< HEAD
<<<<<<< HEAD
#define HARD_ASSERT(condition, ...)                             \
  do {                                                          \
    if (!ABSL_PREDICT_TRUE(condition)) {                        \
      std::string _message =                                    \
          firebase::firestore::util::StringFormat(__VA_ARGS__); \
      INVOKE_INTERNAL_FAIL(_message, #condition);               \
    }                                                           \
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#define HARD_ASSERT(condition, ...)                                           \
  do {                                                                        \
    if (!(condition)) {                                                       \
      std::string _message =                                                  \
          firebase::firestore::util::StringFormat(__VA_ARGS__);               \
      firebase::firestore::util::internal::Fail(                              \
          __FILE__, FIRESTORE_FUNCTION_NAME, __LINE__, _message, #condition); \
    }                                                                         \
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  } while (0)

/**
 * Unconditionally fails the current function.
 *
 * Unlike assert(3) or NSAssert, this macro is never compiled out.
 *
 * @param format A format string suitable for util::StringFormat.
 * @param ... format arguments to pass to util::StringFormat.
 */
<<<<<<< HEAD
<<<<<<< HEAD
#define HARD_FAIL(...)                                        \
  do {                                                        \
    std::string _failure =                                    \
        firebase::firestore::util::StringFormat(__VA_ARGS__); \
    INVOKE_INTERNAL_FAIL(_failure);                           \
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#define HARD_FAIL(...)                                          \
  do {                                                          \
    std::string _failure =                                      \
        firebase::firestore::util::StringFormat(__VA_ARGS__);   \
    firebase::firestore::util::internal::Fail(                  \
        __FILE__, FIRESTORE_FUNCTION_NAME, __LINE__, _failure); \
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  } while (0)

/**
 * Indicates an area of the code that cannot be reached (except possibly due to
 * undefined behaviour or other similar badness). The only reasonable thing to
 * do in these cases is to immediately abort.
 */
#define UNREACHABLE() abort()

/**
 * Returns the given `ptr` if it is non-null; otherwise, results in a failed
 * assertion, similar to `HARD_ASSERT`. This macro deliberately expands to an
 * expression, so that it can be used in initialization and assignment:
 *
 *   my_ptr_ = NOT_NULL(suspicious_ptr);
 *   my_smart_ptr_ = std::move(NOT_NULL(suspicious_smart_ptr));
 *
 *   MyClass() : my_ptr_{NOT_NULL(suspicious_ptr)} {}
 *
 * @param ptr The pointer to check and return. Can be a smart pointer.
 */
<<<<<<< HEAD
<<<<<<< HEAD
#define NOT_NULL(ptr)                                                      \
  (static_cast<void>(ABSL_PREDICT_FALSE((ptr) == nullptr)                  \
                         ? INVOKE_INTERNAL_FAIL("Expected non-null " #ptr) \
                         : static_cast<void>(0)),                          \
   (ptr))  // NOLINT(whitespace/indent)
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#define NOT_NULL(ptr)                                                         \
  firebase::firestore::util::internal::NotNull(                               \
      __FILE__, FIRESTORE_FUNCTION_NAME, __LINE__, "Expected non-null " #ptr, \
      ptr)
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

namespace firebase {
namespace firestore {
namespace util {
<<<<<<< HEAD
<<<<<<< HEAD

using FailureHandler = void (*)(const char* file,
                                const char* func,
                                const int line,
                                const std::string& failure_message);

/**
 * Overrides the default failure handler.
 *
 * The default essentially just calls std::terminate. While reasonable for C++,
 * this isn't optimal for platforms that merely use the C++ core as their
 * implementation and would otherwise be expected to throw a platform specific
 * exception.
 *
 * @param callback A function that will handle the failure. This function is
 *     not expected to return. (If it does, std::terminate() will be called
 *     immediately after it does so.)
 * @return A pointer to the previous failure handler.
 */
FailureHandler SetFailureHandler(FailureHandler callback);

/**
 * Default failure handler. This should typically not be called directly.
 */
ABSL_ATTRIBUTE_NORETURN void DefaultFailureHandler(const char* file,
                                                   const char* func,
                                                   const int line,
                                                   const std::string& message);

=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
namespace internal {

// A no-return helper function. To raise an assertion, use Macro instead.
ABSL_ATTRIBUTE_NORETURN void Fail(const char* file,
                                  const char* func,
                                  int line,
                                  const std::string& message);

ABSL_ATTRIBUTE_NORETURN void Fail(const char* file,
                                  const char* func,
                                  int line,
                                  const std::string& message,
                                  const char* condition);

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
template <typename T>
T NotNull(const char* file,
          const char* func,
          int line,
          const std::string& message,
          T&& ptr) {
  if (ptr == nullptr) {
    Fail(file, func, line, message);
  }
  return std::forward<T>(ptr);
}

<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
}  // namespace internal
}  // namespace util
}  // namespace firestore
}  // namespace firebase

#endif  // FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_UTIL_HARD_ASSERT_H_
