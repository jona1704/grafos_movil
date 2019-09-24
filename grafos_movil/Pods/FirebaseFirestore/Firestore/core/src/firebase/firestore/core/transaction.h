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

#ifndef FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_CORE_TRANSACTION_H_
#define FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_CORE_TRANSACTION_H_

#include <functional>
#include <memory>
#include <unordered_map>
<<<<<<< HEAD
#include <unordered_set>
#include <vector>

#include "Firestore/core/src/firebase/firestore/model/document_key.h"
#include "Firestore/core/src/firebase/firestore/model/mutation.h"
#include "Firestore/core/src/firebase/firestore/model/precondition.h"
#include "Firestore/core/src/firebase/firestore/model/snapshot_version.h"
=======
#include <vector>

#include "Firestore/core/src/firebase/firestore/model/document_key.h"
#include "Firestore/core/src/firebase/firestore/model/precondition.h"
#include "Firestore/core/src/firebase/firestore/model/snapshot_version.h"
#include "Firestore/core/src/firebase/firestore/objc/objc_class.h"
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#include "Firestore/core/src/firebase/firestore/util/status.h"
#include "Firestore/core/src/firebase/firestore/util/statusor.h"
#include "Firestore/core/src/firebase/firestore/util/statusor_callback.h"
#include "absl/types/any.h"
#include "absl/types/optional.h"

<<<<<<< HEAD
=======
NS_ASSUME_NONNULL_BEGIN

OBJC_CLASS(FSTMaybeDocument);
OBJC_CLASS(FSTMutation);

>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
namespace firebase {
namespace firestore {
namespace remote {

class Datastore;

}  // namespace remote

namespace core {

class ParsedSetData;
class ParsedUpdateData;

class Transaction {
 public:
<<<<<<< HEAD
  // TODO(varconst): change this to take a single `StatusOr` parameter.
  using LookupCallback = std::function<void(
      const std::vector<model::MaybeDocument>&, const util::Status&)>;
=======
  // TODO(varconst): once `FSTMaybeDocument` is replaced with a C++ equivalent,
  // this function could take a single `StatusOr` parameter.
  using LookupCallback = std::function<void(
      const std::vector<FSTMaybeDocument*>&, const util::Status&)>;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

  Transaction() = default;
  explicit Transaction(remote::Datastore* transaction);

  /**
   * Takes a set of keys and asynchronously attempts to fetch all the documents
   * from the backend, ignoring any local changes.
   */
  void Lookup(const std::vector<model::DocumentKey>& keys,
              LookupCallback&& callback);

  /**
   * Stores mutation for the given key and set data, to be committed when
   * `Commit` is called.
   */
  void Set(const model::DocumentKey& key, ParsedSetData&& data);

  /**
   * Stores mutations for the given key and update data, to be committed when
   * `Commit` is called.
   */
  void Update(const model::DocumentKey& key, ParsedUpdateData&& data);

  /**
   * Stores a delete mutation for the given key, to be committed when `Commit`
   * is called.
   */
  void Delete(const model::DocumentKey& key);

  /**
   * Attempts to commit the mutations set on this transaction. Invokes the given
   * callback when finished. Once this is called, no other mutations or
   * commits are allowed on the transaction.
   */
  void Commit(util::StatusCallback&& callback);

<<<<<<< HEAD
  /**
   * Marks the transaction as permanently failed, so the transaction will not
   * retry.
   */
  void MarkPermanentlyFailed();

  /**
   * Checks if the transaction is permanently failed.
   */
  bool IsPermanentlyFailed() const;

=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
 private:
  /**
   * Every time a document is read, this should be called to record its version.
   * If we read two different versions of the same document, this will return an
   * error. When the transaction is committed, the versions recorded will be set
   * as preconditions on the writes sent to the backend.
   */
<<<<<<< HEAD
  util::Status RecordVersion(const model::MaybeDocument& doc);

  /** Stores mutations to be written when `Commit` is called. */
  void WriteMutations(std::vector<model::Mutation>&& mutations);
=======
  util::Status RecordVersion(FSTMaybeDocument* doc);

  /** Stores mutations to be written when `Commit` is called. */
  void WriteMutations(std::vector<FSTMutation*>&& mutations);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

  /**
   * Returns version of this doc when it was read in this transaction as a
   * precondition, or no precondition if it was not read.
   */
  model::Precondition CreatePrecondition(const model::DocumentKey& key);

  /**
   * Returns the precondition for a document if the operation is an update. Will
   * return a failed status if an error occurred.
   */
  util::StatusOr<model::Precondition> CreateUpdatePrecondition(
      const model::DocumentKey& key);

  void EnsureCommitNotCalled();

  absl::optional<model::SnapshotVersion> GetVersion(
      const model::DocumentKey& key) const;

  remote::Datastore* datastore_ = nullptr;

<<<<<<< HEAD
  std::vector<model::Mutation> mutations_;
  bool committed_ = false;
  bool permanentError_ = false;
=======
  std::vector<FSTMutation*> mutations_;
  bool committed_ = false;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

  /**
   * A deferred usage error that occurred previously in this transaction that
   * will cause the transaction to fail once it actually commits.
   */
  util::Status last_write_error_;

<<<<<<< HEAD
  /**
   * Set of documents that have been written in the transaction.
   *
   * When there's more than one write to the same key in a transaction, any
   * writes after the first are handled differently.
   */
  std::unordered_set<model::DocumentKey, model::DocumentKeyHash> written_docs_;

=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  std::unordered_map<model::DocumentKey,
                     model::SnapshotVersion,
                     model::DocumentKeyHash>
      read_versions_;
};

using TransactionResultCallback = util::StatusOrCallback<absl::any>;

/**
 * TransactionUpdateCallback is a block that wraps a user's transaction update
 * block internally.
 *
 * The update block will be called with two parameters:
 *   * The transaction: an object with methods for performing reads and writes
 * within the transaction.
 *   * The callback: to be called by the block once the user's code is finished.
 */
using TransactionUpdateCallback = std::function<void(
    std::shared_ptr<Transaction>, TransactionResultCallback)>;

}  // namespace core
}  // namespace firestore
}  // namespace firebase

<<<<<<< HEAD
=======
NS_ASSUME_NONNULL_END

>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#endif  // FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_CORE_TRANSACTION_H_
