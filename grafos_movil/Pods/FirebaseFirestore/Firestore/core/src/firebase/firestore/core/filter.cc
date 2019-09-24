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

#include "Firestore/core/src/firebase/firestore/core/filter.h"

#include <ostream>
<<<<<<< HEAD
=======
#include <utility>

#include "Firestore/core/src/firebase/firestore/api/input_validation.h"
#include "Firestore/core/src/firebase/firestore/core/nan_filter.h"
#include "Firestore/core/src/firebase/firestore/core/null_filter.h"
#include "Firestore/core/src/firebase/firestore/core/relation_filter.h"
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

namespace firebase {
namespace firestore {
namespace core {

<<<<<<< HEAD
bool operator==(const Filter& lhs, const Filter& rhs) {
  return lhs.rep_ == nullptr
             ? rhs.rep_ == nullptr
             : (rhs.rep_ != nullptr && lhs.rep_->Equals(*rhs.rep_));
=======
using api::ThrowInvalidArgument;
using model::FieldPath;
using model::FieldValue;

std::shared_ptr<Filter> Filter::Create(FieldPath path,
                                       Operator op,
                                       FieldValue value_rhs) {
  if (value_rhs.type() == FieldValue::Type::Null) {
    if (op != Filter::Operator::Equal) {
      ThrowInvalidArgument(
          "Invalid Query. Null supports only equality comparisons.");
    }
    return std::make_shared<NullFilter>(std::move(path));

  } else if (value_rhs.is_nan()) {
    if (op != Filter::Operator::Equal) {
      ThrowInvalidArgument(
          "Invalid Query. NaN supports only equality comparisons.");
    }
    return std::make_shared<NanFilter>(std::move(path));

  } else {
    return std::make_shared<RelationFilter>(std::move(path), op,
                                            std::move(value_rhs));
  }
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
}

std::ostream& operator<<(std::ostream& os, const Filter& filter) {
  return os << filter.ToString();
}

}  // namespace core
}  // namespace firestore
}  // namespace firebase
