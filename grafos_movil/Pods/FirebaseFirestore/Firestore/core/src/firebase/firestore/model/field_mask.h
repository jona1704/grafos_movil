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

#ifndef FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_MODEL_FIELD_MASK_H_
#define FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_MODEL_FIELD_MASK_H_

#include <initializer_list>
#include <set>
#include <string>
#include <utility>

#include "Firestore/core/src/firebase/firestore/model/field_path.h"

namespace firebase {
namespace firestore {
namespace model {

class ObjectValue;

/**
 * Provides a set of fields that can be used to partially patch a document.
 * FieldMask is used in conjunction with FieldValue of Object type.
 *
 * Examples:
 *   foo - Overwrites foo entirely with the provided value. If foo is not
 *       present in the companion FieldValue, the field is deleted.
 *   foo.bar - Overwrites only the field bar of the object foo. If foo is not an
 *       object, foo is replaced with an object containing bar.
 */
class FieldMask {
 public:
  using const_iterator = std::set<FieldPath>::const_iterator;

<<<<<<< HEAD
<<<<<<< HEAD
  FieldMask() = default;

=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  FieldMask(std::initializer_list<FieldPath> list) : fields_{list} {
  }
  template <class InputIt>
  FieldMask(InputIt first, InputIt last) : fields_{first, last} {
  }
  explicit FieldMask(std::set<FieldPath> fields) : fields_{std::move(fields)} {
  }

  FieldMask(const FieldMask& f) : fields_{f.begin(), f.end()} {
  }

  const_iterator begin() const {
    return fields_.begin();
  }
  const_iterator end() const {
    return fields_.end();
  }

  size_t size() const {
    return fields_.size();
  }

  /**
   * Verifies that `fieldPath` is included by at least one field in this field
   * mask.
   *
   * This is an O(n) operation, where `n` is the size of the field mask.
   */
  bool covers(const FieldPath& fieldPath) const;

  std::string ToString() const;

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#if defined(__OBJC__)
  FieldMask() {
  }
#endif

<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  size_t Hash() const;

  friend bool operator==(const FieldMask& lhs, const FieldMask& rhs);

 private:
  std::set<FieldPath> fields_;
};

inline bool operator==(const FieldMask& lhs, const FieldMask& rhs) {
  return lhs.fields_ == rhs.fields_;
}

}  // namespace model
}  // namespace firestore
}  // namespace firebase

#endif  // FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_MODEL_FIELD_MASK_H_
