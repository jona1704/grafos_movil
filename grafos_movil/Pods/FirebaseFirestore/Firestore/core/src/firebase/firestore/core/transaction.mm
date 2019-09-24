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

#include "Firestore/core/src/firebase/firestore/core/transaction.h"

#include <algorithm>
#include <unordered_set>
#include <utility>

<<<<<<< HEAD
#include "Firestore/core/include/firebase/firestore/firestore_errors.h"
#include "Firestore/core/src/firebase/firestore/core/user_data.h"
#include "Firestore/core/src/firebase/firestore/model/delete_mutation.h"
#include "Firestore/core/src/firebase/firestore/remote/datastore.h"
#include "Firestore/core/src/firebase/firestore/util/hard_assert.h"

using firebase::firestore::Error;
using firebase::firestore::core::ParsedSetData;
using firebase::firestore::core::ParsedUpdateData;
using firebase::firestore::model::DeleteMutation;
using firebase::firestore::model::DocumentKey;
using firebase::firestore::model::DocumentKeyHash;
using firebase::firestore::model::MaybeDocument;
using firebase::firestore::model::Mutation;
=======
#import "Firestore/Source/Model/FSTDocument.h"
#import "Firestore/Source/Model/FSTMutation.h"

#include "Firestore/core/include/firebase/firestore/firestore_errors.h"
#include "Firestore/core/src/firebase/firestore/core/user_data.h"
#include "Firestore/core/src/firebase/firestore/remote/datastore.h"
#include "Firestore/core/src/firebase/firestore/util/hard_assert.h"

using firebase::firestore::FirestoreErrorCode;
using firebase::firestore::core::ParsedSetData;
using firebase::firestore::core::ParsedUpdateData;
using firebase::firestore::model::DocumentKey;
using firebase::firestore::model::DocumentKeyHash;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
using firebase::firestore::model::Precondition;
using firebase::firestore::model::SnapshotVersion;
using firebase::firestore::remote::Datastore;
using firebase::firestore::util::Status;
using firebase::firestore::util::StatusOr;

namespace firebase {
namespace firestore {
namespace core {

Transaction::Transaction(Datastore* datastore)
    : datastore_{NOT_NULL(datastore)} {
}

<<<<<<< HEAD
Status Transaction::RecordVersion(const MaybeDocument& doc) {
  SnapshotVersion doc_version;

  if (doc.is_document()) {
    doc_version = doc.version();
  } else if (doc.is_no_document()) {
=======
Status Transaction::RecordVersion(FSTMaybeDocument* doc) {
  SnapshotVersion doc_version;

  if ([doc isKindOfClass:[FSTDocument class]]) {
    doc_version = doc.version;
  } else if ([doc isKindOfClass:[FSTDeletedDocument class]]) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    // For deleted docs, we must record an explicit no version to build the
    // right precondition when writing.
    doc_version = SnapshotVersion::None();
  } else {
<<<<<<< HEAD
    HARD_FAIL("Unexpected document type in transaction: %s", doc.type());
  }

  absl::optional<SnapshotVersion> existing_version = GetVersion(doc.key());
  if (existing_version.has_value()) {
    if (doc_version != existing_version.value()) {
      // This transaction will fail no matter what.
      return Status{Error::Aborted,
=======
    HARD_FAIL("Unexpected document type in transaction: %s",
              NSStringFromClass([doc class]));
  }

  absl::optional<SnapshotVersion> existing_version = GetVersion(doc.key);
  if (existing_version.has_value()) {
    if (doc_version != existing_version.value()) {
      // This transaction will fail no matter what.
      return Status{FirestoreErrorCode::Aborted,
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
                    "Document version changed between two reads."};
    }
    return Status::OK();
  } else {
<<<<<<< HEAD
    read_versions_[doc.key()] = doc_version;
=======
    read_versions_[doc.key] = doc_version;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    return Status::OK();
  }
}

void Transaction::Lookup(const std::vector<DocumentKey>& keys,
                         LookupCallback&& callback) {
  EnsureCommitNotCalled();

  if (!mutations_.empty()) {
<<<<<<< HEAD
    Status lookup_error = Status{Error::InvalidArgument,
=======
    Status lookup_error = Status{FirestoreErrorCode::InvalidArgument,
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
                                 "Firestore transactions require all reads to "
                                 "be executed before all writes"};
    callback({}, lookup_error);
    return;
  }

  datastore_->LookupDocuments(
<<<<<<< HEAD
      keys, [this, callback](const std::vector<MaybeDocument>& documents,
=======
      keys, [this, callback](const std::vector<FSTMaybeDocument*>& documents,
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
                             const Status& status) {
        if (!status.ok()) {
          callback({}, status);
          return;
        }

<<<<<<< HEAD
        for (const MaybeDocument& doc : documents) {
=======
        for (FSTMaybeDocument* doc : documents) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
          Status record_error = RecordVersion(doc);
          if (!record_error.ok()) {
            callback({}, record_error);
            return;
          }
        }

        callback(documents, Status::OK());
      });
}

<<<<<<< HEAD
void Transaction::WriteMutations(std::vector<Mutation>&& mutations) {
  EnsureCommitNotCalled();
  // `move` will become appropriate once `Mutation` is replaced by the C++
=======
void Transaction::WriteMutations(std::vector<FSTMutation*>&& mutations) {
  EnsureCommitNotCalled();
  // `move` will become appropriate once `FSTMutation` is replaced by the C++
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  // equivalent.
  std::move(mutations.begin(), mutations.end(), std::back_inserter(mutations_));
}

Precondition Transaction::CreatePrecondition(const DocumentKey& key) {
  absl::optional<SnapshotVersion> version = GetVersion(key);
<<<<<<< HEAD
  if (written_docs_.count(key) == 0 && version.has_value()) {
=======
  if (version.has_value()) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    return Precondition::UpdateTime(version.value());
  } else {
    return Precondition::None();
  }
}

StatusOr<Precondition> Transaction::CreateUpdatePrecondition(
    const DocumentKey& key) {
  absl::optional<SnapshotVersion> version = GetVersion(key);
<<<<<<< HEAD
  // The first time a document is written, we want to take into account the
  // read time and existence.
  if (written_docs_.count(key) == 0 && version.has_value()) {
    if (version.value() == SnapshotVersion::None()) {
      // The document doesn't exist, so fail the transaction.
      //
      // This has to be validated locally because you can't send a
      // precondition that a document does not exist without changing the
      // semantics of the backend write to be an insert. This is the reverse
      // of what we want, since we want to assert that the document doesn't
      // exist but then send the update and have it fail. Since we can't
      // express that to the backend, we have to validate locally.
      //
      // Note: this can change once we can send separate verify writes in the
      // transaction.
      return Status{Error::InvalidArgument,
                    "Can't update a document that doesn't exist."};
    }
=======

  if (version.has_value() && version.value() == SnapshotVersion::None()) {
    // The document to update doesn't exist, so fail the transaction.
    return Status{FirestoreErrorCode::InvalidArgument,
                  "Can't update a document that doesn't exist."};
  } else if (version.has_value()) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    // Document exists, just base precondition on document update time.
    return Precondition::UpdateTime(version.value());
  } else {
    // Document was not read, so we just use the preconditions for a blind
    // update.
    return Precondition::Exists(true);
  }
}

void Transaction::Set(const DocumentKey& key, ParsedSetData&& data) {
  WriteMutations(std::move(data).ToMutations(key, CreatePrecondition(key)));
<<<<<<< HEAD
  written_docs_.insert(key);
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
}

void Transaction::Update(const DocumentKey& key, ParsedUpdateData&& data) {
  StatusOr<Precondition> maybe_precondition = CreateUpdatePrecondition(key);
  if (!maybe_precondition.ok()) {
    last_write_error_ = maybe_precondition.status();
  } else {
    WriteMutations(
        std::move(data).ToMutations(key, maybe_precondition.ValueOrDie()));
  }
<<<<<<< HEAD
  written_docs_.insert(key);
}

void Transaction::Delete(const DocumentKey& key) {
  Mutation mutation = DeleteMutation(key, CreatePrecondition(key));
  WriteMutations({mutation});
  written_docs_.insert(key);
=======
}

void Transaction::Delete(const DocumentKey& key) {
  FSTMutation* mutation =
      [[FSTDeleteMutation alloc] initWithKey:key
                                precondition:CreatePrecondition(key)];
  WriteMutations({mutation});

  // Since the delete will be applied before all following writes, we need to
  // ensure that the precondition for the next write will be exists: false.
  read_versions_[key] = SnapshotVersion::None();
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
}

void Transaction::Commit(util::StatusCallback&& callback) {
  EnsureCommitNotCalled();

  // If there was an error writing, raise that error now
  if (!last_write_error_.ok()) {
    callback(last_write_error_);
    return;
  }

  // Make a list of read documents that haven't been written.
  std::unordered_set<DocumentKey, DocumentKeyHash> unwritten;
  for (const auto& kv : read_versions_) {
    unwritten.insert(kv.first);
  };
  // For each mutation, note that the doc was written.
<<<<<<< HEAD
  for (const Mutation& mutation : mutations_) {
    unwritten.erase(mutation.key());
=======
  for (FSTMutation* mutation : mutations_) {
    unwritten.erase(mutation.key);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  }

  if (!unwritten.empty()) {
    // TODO(klimt): This is a temporary restriction, until "verify" is supported
    // on the backend.
    callback(
<<<<<<< HEAD
        Status{Error::InvalidArgument,
=======
        Status{FirestoreErrorCode::InvalidArgument,
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
               "Every document read in a transaction must also be written in "
               "that transaction."});
  } else {
    committed_ = true;
    datastore_->CommitMutations(mutations_, std::move(callback));
  }
}

<<<<<<< HEAD
void Transaction::MarkPermanentlyFailed() {
  permanentError_ = true;
}

bool Transaction::IsPermanentlyFailed() const {
  return permanentError_;
}

=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
void Transaction::EnsureCommitNotCalled() {
  HARD_ASSERT(!committed_, "A transaction object cannot be used after its "
                           "update callback has been invoked.");
}

absl::optional<SnapshotVersion> Transaction::GetVersion(
    const DocumentKey& key) const {
  auto found = read_versions_.find(key);
  if (found != read_versions_.end()) {
    return found->second;
  }
  return absl::nullopt;
}

}  // namespace core
}  // namespace firestore
}  // namespace firebase