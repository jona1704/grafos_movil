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

#include "Firestore/core/src/firebase/firestore/model/mutation_batch.h"

<<<<<<< HEAD
<<<<<<< HEAD
#include <ostream>
#include <utility>

#include "Firestore/core/src/firebase/firestore/model/mutation_batch_result.h"
#include "Firestore/core/src/firebase/firestore/util/hard_assert.h"
#include "Firestore/core/src/firebase/firestore/util/to_string.h"
=======
#include <utility>

#include "Firestore/core/src/firebase/firestore/util/hard_assert.h"
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
#include <utility>

#include "Firestore/core/src/firebase/firestore/util/hard_assert.h"
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

namespace firebase {
namespace firestore {
namespace model {

<<<<<<< HEAD
<<<<<<< HEAD
MutationBatch::MutationBatch(int batch_id,
                             Timestamp local_write_time,
                             std::vector<Mutation> base_mutations,
                             std::vector<Mutation> mutations)
    : batch_id_(batch_id),
      local_write_time_(std::move(local_write_time)),
      base_mutations_(std::move(base_mutations)),
      mutations_(std::move(mutations)) {
  HARD_ASSERT(!mutations_.empty(), "Cannot create an empty mutation batch");
}

absl::optional<MaybeDocument> MutationBatch::ApplyToRemoteDocument(
    absl::optional<MaybeDocument> maybe_doc,
    const DocumentKey& document_key,
    const MutationBatchResult& mutation_batch_result) const {
  HARD_ASSERT(!maybe_doc || maybe_doc->key() == document_key,
              "ApplyTo: key %s doesn't match maybe_doc key %s",
              document_key.ToString(), maybe_doc->key().ToString());

  const auto& mutation_results = mutation_batch_result.mutation_results();
  HARD_ASSERT(mutation_results.size() == mutations_.size(),
              "Mismatch between mutations length (%s) and results length (%s)",
              mutations_.size(), mutation_results.size());

  for (size_t i = 0; i < mutations_.size(); i++) {
    const Mutation& mutation = mutations_[i];
    const MutationResult& mutation_result = mutation_results[i];
    if (mutation.key() == document_key) {
      maybe_doc = mutation.ApplyToRemoteDocument(maybe_doc, mutation_result);
    }
  }
  return maybe_doc;
}

absl::optional<MaybeDocument> MutationBatch::ApplyToLocalDocument(
    absl::optional<MaybeDocument> maybe_doc,
    const DocumentKey& document_key) const {
  HARD_ASSERT(!maybe_doc || maybe_doc->key() == document_key,
              "key %s doesn't match maybe_doc key %s", document_key.ToString(),
              maybe_doc->key().ToString());

  // First, apply the base state. This allows us to apply non-idempotent
  // transform against a consistent set of values.
  for (const Mutation& mutation : base_mutations_) {
    if (mutation.key() == document_key) {
      maybe_doc =
          mutation.ApplyToLocalView(maybe_doc, maybe_doc, local_write_time_);
    }
  }

  absl::optional<MaybeDocument> base_doc = maybe_doc;

  // Second, apply all user-provided mutations.
  for (const Mutation& mutation : mutations_) {
    if (mutation.key() == document_key) {
      maybe_doc =
          mutation.ApplyToLocalView(maybe_doc, base_doc, local_write_time_);
    }
  }
  return maybe_doc;
}

MaybeDocumentMap MutationBatch::ApplyToLocalDocumentSet(
    const MaybeDocumentMap& document_set) const {
  // TODO(mrschmidt): This implementation is O(n^2). If we iterate through the
  // mutations first (as done in `applyToLocalDocument:documentKey:`), we can
  // reduce the complexity to O(n).

  MaybeDocumentMap mutated_documents = document_set;
  for (const Mutation& mutation : mutations_) {
    const DocumentKey& key = mutation.key();

    absl::optional<MaybeDocument> previous_document =
        mutated_documents.get(key);
    absl::optional<MaybeDocument> mutated_document =
        ApplyToLocalDocument(std::move(previous_document), key);
    if (mutated_document) {
      mutated_documents = mutated_documents.insert(key, *mutated_document);
    }
  }
  return mutated_documents;
}

DocumentKeySet MutationBatch::keys() const {
  DocumentKeySet set;
  for (const Mutation& mutation : mutations_) {
    set = set.insert(mutation.key());
  }
  return set;
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
namespace {

/**
 * Compares two vectors of unique pointers, and ensures the Mutation contents of
 * the pointer (not just the memory address itself) is equal.
 */
bool deep_equals(const std::vector<std::unique_ptr<Mutation>>& lhs,
                 const std::vector<std::unique_ptr<Mutation>>& rhs) {
  if (lhs.size() != rhs.size()) return false;

  for (size_t i = 0; i < lhs.size(); i++) {
    if (!lhs[i] && !rhs[i])
      continue;
    else if (!lhs[i] || !rhs[i])
      return false;
    else if (*lhs[i] != *rhs[i])
      return false;
  }

  return true;
}

}  // namespace

MutationBatch::MutationBatch(int batch_id,
                             Timestamp local_write_time,
                             std::vector<std::unique_ptr<Mutation>>&& mutations)
    : batch_id_(batch_id),
      local_write_time_(std::move(local_write_time)),
      mutations_(std::move(mutations)) {
  HARD_ASSERT(!mutations_.empty(), "Cannot create an empty mutation batch");
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
}

bool operator==(const MutationBatch& lhs, const MutationBatch& rhs) {
  return lhs.batch_id() == rhs.batch_id() &&
         lhs.local_write_time() == rhs.local_write_time() &&
<<<<<<< HEAD
<<<<<<< HEAD
         lhs.base_mutations() == rhs.base_mutations() &&
         lhs.mutations() == rhs.mutations();
}

std::string MutationBatch::ToString() const {
  return absl::StrCat("MutationBatch(id=", batch_id_,
                      ", local_write_time=", local_write_time_.ToString(),
                      ", mutations=", util::ToString(mutations_), ")");
}

std::ostream& operator<<(std::ostream& os, const MutationBatch& batch) {
  return os << batch.ToString();
=======
         deep_equals(lhs.mutations(), rhs.mutations());
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
         deep_equals(lhs.mutations(), rhs.mutations());
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
}

}  // namespace model
}  // namespace firestore
}  // namespace firebase
