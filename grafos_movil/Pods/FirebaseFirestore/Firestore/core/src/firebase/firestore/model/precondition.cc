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

#include "Firestore/core/src/firebase/firestore/model/precondition.h"

#include "Firestore/core/src/firebase/firestore/model/maybe_document.h"
#include "Firestore/core/src/firebase/firestore/model/snapshot_version.h"
#include "Firestore/core/src/firebase/firestore/util/hard_assert.h"
<<<<<<< HEAD
<<<<<<< HEAD
#include "absl/strings/str_cat.h"
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

namespace firebase {
namespace firestore {
namespace model {

Precondition::Precondition(Type type, SnapshotVersion update_time, bool exists)
    : type_(type), update_time_(std::move(update_time)), exists_(exists) {
}

/* static */
Precondition Precondition::Exists(bool exists) {
  return Precondition{Type::Exists, SnapshotVersion::None(), exists};
}

/* static */
Precondition Precondition::UpdateTime(SnapshotVersion update_time) {
  // update_time could be SnapshotVersion::None() in particular for locally
  // deleted documents.
  return Precondition{Type::UpdateTime, std::move(update_time), false};
}

/* static */
Precondition Precondition::None() {
  return Precondition{Type::None, SnapshotVersion::None(), false};
}

<<<<<<< HEAD
<<<<<<< HEAD
bool Precondition::IsValidFor(
    const absl::optional<MaybeDocument>& maybe_doc) const {
  switch (type_) {
    case Type::UpdateTime:
      return maybe_doc && maybe_doc->type() == MaybeDocument::Type::Document &&
             maybe_doc->version() == update_time_;
    case Type::Exists:
      return (exists_ == (maybe_doc &&
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
bool Precondition::IsValidFor(const MaybeDocument* maybe_doc) const {
  switch (type_) {
    case Type::UpdateTime:
      return maybe_doc != nullptr &&
             maybe_doc->type() == MaybeDocument::Type::Document &&
             maybe_doc->version() == update_time_;
    case Type::Exists:
      return (exists_ == (maybe_doc != nullptr &&
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
                          maybe_doc->type() == MaybeDocument::Type::Document));
    case Type::None:
      return true;
  }
  UNREACHABLE();
}

<<<<<<< HEAD
<<<<<<< HEAD
size_t Precondition::Hash() const {
  return util::Hash(update_time_, exists_, type_);
}

std::string Precondition::ToString() const {
  switch (type_) {
    case Type::None:
      return "Precondition(<none>)";
    case Type::Exists:
      return absl::StrCat("Precondition(exists=", exists_, ")");
    case Type::UpdateTime:
      return absl::StrCat("Precondition(update_time=", update_time_.ToString(),
                          ")");
  }
  UNREACHABLE();
}

=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
}  // namespace model
}  // namespace firestore
}  // namespace firebase
