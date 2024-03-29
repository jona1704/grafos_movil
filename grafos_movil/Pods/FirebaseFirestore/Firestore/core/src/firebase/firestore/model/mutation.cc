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

#include "Firestore/core/src/firebase/firestore/model/mutation.h"

#include <cstdlib>
<<<<<<< HEAD
<<<<<<< HEAD
#include <ostream>
#include <sstream>
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#include <utility>

#include "Firestore/core/src/firebase/firestore/model/document.h"
#include "Firestore/core/src/firebase/firestore/model/field_path.h"
#include "Firestore/core/src/firebase/firestore/model/field_value.h"
#include "Firestore/core/src/firebase/firestore/model/no_document.h"
#include "Firestore/core/src/firebase/firestore/util/hard_assert.h"
<<<<<<< HEAD
<<<<<<< HEAD
#include "Firestore/core/src/firebase/firestore/util/to_string.h"
#include "absl/strings/str_cat.h"
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

namespace firebase {
namespace firestore {
namespace model {

<<<<<<< HEAD
<<<<<<< HEAD
std::string MutationResult::ToString() const {
  return absl::StrCat(
      "MutationResult(version=", version_.ToString(),
      ", transform_results=", util::ToString(transform_results_), ")");
}

std::ostream& operator<<(std::ostream& os, const MutationResult& result) {
  return os << result.ToString();
}

Mutation::Rep::Rep(DocumentKey&& key, Precondition&& precondition)
    : key_(std::move(key)), precondition_(std::move(precondition)) {
}

bool Mutation::Rep::Equals(const Mutation::Rep& other) const {
  return type() == other.type() && key_ == other.key_ &&
         precondition_ == other.precondition_;
}

void Mutation::Rep::VerifyKeyMatches(
    const absl::optional<MaybeDocument>& maybe_doc) const {
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
Mutation::Mutation(DocumentKey&& key, Precondition&& precondition)
    : key_(std::move(key)), precondition_(std::move(precondition)) {
}

void Mutation::VerifyKeyMatches(const MaybeDocument* maybe_doc) const {
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  if (maybe_doc) {
    HARD_ASSERT(maybe_doc->key() == key(),
                "Can only apply a mutation to a document with the same key");
  }
}

<<<<<<< HEAD
<<<<<<< HEAD
SnapshotVersion Mutation::Rep::GetPostMutationVersion(
    const absl::optional<MaybeDocument>& maybe_doc) {
=======
SnapshotVersion Mutation::GetPostMutationVersion(
    const MaybeDocument* maybe_doc) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
SnapshotVersion Mutation::GetPostMutationVersion(
    const MaybeDocument* maybe_doc) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  if (maybe_doc && maybe_doc->type() == MaybeDocument::Type::Document) {
    return maybe_doc->version();
  } else {
    return SnapshotVersion::None();
  }
}

<<<<<<< HEAD
<<<<<<< HEAD
bool operator==(const Mutation& lhs, const Mutation& rhs) {
  return lhs.rep_ == nullptr
             ? rhs.rep_ == nullptr
             : (rhs.rep_ != nullptr && lhs.rep_->Equals(*rhs.rep_));
}

size_t Mutation::Rep::Hash() const {
  return util::Hash(type(), key(), precondition());
}

std::ostream& operator<<(std::ostream& os, const Mutation& mutation) {
  return os << mutation.ToString();
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
bool Mutation::equal_to(const Mutation& other) const {
  return key_ == other.key_ && precondition_ == other.precondition_ &&
         type() == other.type();
}

SetMutation::SetMutation(DocumentKey&& key,
                         ObjectValue&& value,
                         Precondition&& precondition)
    : Mutation(std::move(key), std::move(precondition)),
      value_(std::move(value)) {
}

MaybeDocumentPtr SetMutation::ApplyToRemoteDocument(
    const MaybeDocumentPtr& maybe_doc,
    const MutationResult& mutation_result) const {
  VerifyKeyMatches(maybe_doc.get());

  HARD_ASSERT(mutation_result.transform_results() == nullptr,
              "Transform results received by SetMutation.");

  // Unlike applyToLocalView, if we're applying a mutation to a remote document
  // the server has accepted the mutation so the precondition must have held.

  const SnapshotVersion& version = mutation_result.version();
  return absl::make_unique<Document>(ObjectValue(value_), key(), version,
                                     DocumentState::kCommittedMutations);
}

MaybeDocumentPtr SetMutation::ApplyToLocalView(
    const MaybeDocumentPtr& maybe_doc,
    const MaybeDocument*,
    const Timestamp&) const {
  VerifyKeyMatches(maybe_doc.get());

  if (!precondition().IsValidFor(maybe_doc.get())) {
    return maybe_doc;
  }

  SnapshotVersion version = GetPostMutationVersion(maybe_doc.get());
  return absl::make_unique<Document>(ObjectValue(value_), key(), version,
                                     DocumentState::kLocalMutations);
}

bool SetMutation::equal_to(const Mutation& other) const {
  if (!Mutation::equal_to(other)) return false;
  return value_ == static_cast<const SetMutation&>(other).value_;
}

PatchMutation::PatchMutation(DocumentKey&& key,
                             ObjectValue&& value,
                             FieldMask&& mask,
                             Precondition&& precondition)
    : Mutation(std::move(key), std::move(precondition)),
      value_(std::move(value)),
      mask_(std::move(mask)) {
}

MaybeDocumentPtr PatchMutation::ApplyToRemoteDocument(
    const MaybeDocumentPtr& maybe_doc,
    const MutationResult& mutation_result) const {
  VerifyKeyMatches(maybe_doc.get());
  HARD_ASSERT(mutation_result.transform_results() == nullptr,
              "Transform results received by PatchMutation.");

  if (!precondition().IsValidFor(maybe_doc.get())) {
    // Since the mutation was not rejected, we know that the precondition
    // matched on the backend. We therefore must not have the expected version
    // of the document in our cache and return an UnknownDocument with the known
    // updateTime.

    // TODO(rsgowman): heldwriteacks: Implement. Like this (once UnknownDocument
    // is ported):
    // return absl::make_unique<UnknownDocument>(key(),
    // mutation_result.version());

    abort();
  }

  const SnapshotVersion& version = mutation_result.version();
  ObjectValue new_data = PatchDocument(maybe_doc.get());
  return absl::make_unique<Document>(std::move(new_data), key(), version,
                                     DocumentState::kCommittedMutations);
}

MaybeDocumentPtr PatchMutation::ApplyToLocalView(
    const MaybeDocumentPtr& maybe_doc,
    const MaybeDocument*,
    const Timestamp&) const {
  VerifyKeyMatches(maybe_doc.get());

  if (!precondition().IsValidFor(maybe_doc.get())) {
    return maybe_doc;
  }

  SnapshotVersion version = GetPostMutationVersion(maybe_doc.get());
  ObjectValue new_data = PatchDocument(maybe_doc.get());
  return absl::make_unique<Document>(std::move(new_data), key(), version,
                                     DocumentState::kLocalMutations);
}

ObjectValue PatchMutation::PatchDocument(const MaybeDocument* maybe_doc) const {
  if (maybe_doc && maybe_doc->type() == MaybeDocument::Type::Document) {
    return PatchObject(static_cast<const Document*>(maybe_doc)->data());
  } else {
    return PatchObject(ObjectValue::Empty());
  }
}

ObjectValue PatchMutation::PatchObject(ObjectValue obj) const {
  for (const FieldPath& path : mask_) {
    if (!path.empty()) {
      absl::optional<FieldValue> new_value = value_.Get(path);
      if (!new_value) {
        obj = obj.Delete(path);
      } else {
        obj = obj.Set(path, *new_value);
      }
    }
  }
  return obj;
}

bool PatchMutation::equal_to(const Mutation& other) const {
  if (!Mutation::equal_to(other)) return false;
  const PatchMutation& patch_other = static_cast<const PatchMutation&>(other);
  return value_ == patch_other.value_ && mask_ == patch_other.mask_;
}

DeleteMutation::DeleteMutation(DocumentKey&& key, Precondition&& precondition)
    : Mutation(std::move(key), std::move(precondition)) {
}

MaybeDocumentPtr DeleteMutation::ApplyToRemoteDocument(
    const MaybeDocumentPtr& /*maybe_doc*/,
    const MutationResult& /*mutation_result*/) const {
  // TODO(rsgowman): Implement.
  abort();
}

MaybeDocumentPtr DeleteMutation::ApplyToLocalView(
    const MaybeDocumentPtr& maybe_doc,
    const MaybeDocument*,
    const Timestamp&) const {
  VerifyKeyMatches(maybe_doc.get());

  if (!precondition().IsValidFor(maybe_doc.get())) {
    return maybe_doc;
  }

  return absl::make_unique<NoDocument>(key(), SnapshotVersion::None(),
                                       /*hasCommittedMutations=*/false);
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
}

}  // namespace model
}  // namespace firestore
}  // namespace firebase
