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

#ifndef FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_LOCAL_MUTATION_QUEUE_H_
#define FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_LOCAL_MUTATION_QUEUE_H_

#if !defined(__OBJC__)
#error "For now, this file must only be included by ObjC source files."
#endif  // !defined(__OBJC__)

#import <Foundation/Foundation.h>

#include <vector>

#include "Firestore/core/include/firebase/firestore/timestamp.h"
<<<<<<< HEAD
<<<<<<< HEAD
#include "Firestore/core/src/firebase/firestore/core/query.h"
#include "Firestore/core/src/firebase/firestore/model/document_key.h"
#include "Firestore/core/src/firebase/firestore/model/document_key_set.h"
#include "Firestore/core/src/firebase/firestore/model/mutation_batch.h"
#include "Firestore/core/src/firebase/firestore/model/types.h"
#include "Firestore/core/src/firebase/firestore/nanopb/byte_string.h"
#include "absl/types/optional.h"
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#include "Firestore/core/src/firebase/firestore/model/document_key.h"
#include "Firestore/core/src/firebase/firestore/model/document_key_set.h"
#include "Firestore/core/src/firebase/firestore/model/types.h"

@class FSTMutation;
@class FSTMutationBatch;
@class FSTQuery;
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

NS_ASSUME_NONNULL_BEGIN

namespace firebase {
namespace firestore {
namespace local {

/** A queue of mutations to apply to the remote store. */
class MutationQueue {
 public:
  virtual ~MutationQueue() {
  }

  /**
   * Starts the mutation queue, performing any initial reads that might be
   * required to establish invariants, etc.
   */
  virtual void Start() = 0;

  /** Returns true if this queue contains no mutation batches. */
  virtual bool IsEmpty() = 0;

  /** Acknowledges the given batch. */
<<<<<<< HEAD
<<<<<<< HEAD
  virtual void AcknowledgeBatch(const model::MutationBatch& batch,
                                const nanopb::ByteString& stream_token) = 0;
=======
  virtual void AcknowledgeBatch(FSTMutationBatch* batch,
                                NSData* _Nullable stream_token) = 0;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  virtual void AcknowledgeBatch(FSTMutationBatch* batch,
                                NSData* _Nullable stream_token) = 0;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

  /**
   * Creates a new mutation batch and adds it to this mutation queue.
   *
   * @param local_write_time The original write time of this mutation.
   * @param base_mutations Mutations that are used to populate the base values
   * when this mutation is applied locally. These mutations are used to locally
   * overwrite values that are persisted in the remote document cache.
   * @param mutations The user-provided mutations in this mutation batch.
   */
<<<<<<< HEAD
<<<<<<< HEAD
  virtual model::MutationBatch AddMutationBatch(
      const Timestamp& local_write_time,
      std::vector<model::Mutation>&& base_mutations,
      std::vector<model::Mutation>&& mutations) = 0;
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  virtual FSTMutationBatch* AddMutationBatch(
      const Timestamp& local_write_time,
      std::vector<FSTMutation*>&& base_mutations,
      std::vector<FSTMutation*>&& mutations) = 0;
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

  /**
   * Removes the given mutation batch from the queue. This is useful in two
   * circumstances:
   *
   * + Removing applied mutations from the head of the queue
   * + Removing rejected mutations from anywhere in the queue
   */
<<<<<<< HEAD
<<<<<<< HEAD
  virtual void RemoveMutationBatch(const model::MutationBatch& batch) = 0;
=======
  virtual void RemoveMutationBatch(FSTMutationBatch* batch) = 0;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  virtual void RemoveMutationBatch(FSTMutationBatch* batch) = 0;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

  /** Gets all mutation batches in the mutation queue. */
  // TODO(mikelehen): PERF: Current consumer only needs mutated keys; if we can
  // provide that cheaply, we should replace this.
<<<<<<< HEAD
<<<<<<< HEAD
  virtual std::vector<model::MutationBatch> AllMutationBatches() = 0;
=======
  virtual std::vector<FSTMutationBatch*> AllMutationBatches() = 0;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  virtual std::vector<FSTMutationBatch*> AllMutationBatches() = 0;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

  /**
   * Finds all mutation batches that could @em possibly affect the given
   * document keys. Not all mutations in a batch will necessarily affect each
   * key, so when looping through the batches you'll need to check that the
   * mutation itself matches the key.
   *
   * Note that because of this requirement implementations are free to return
   * mutation batches that don't contain any of the given document keys at all
   * if it's convenient.
   */
  // TODO(mcg): This should really return an iterator
<<<<<<< HEAD
<<<<<<< HEAD
  virtual std::vector<model::MutationBatch>
=======
  virtual std::vector<FSTMutationBatch*>
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  virtual std::vector<FSTMutationBatch*>
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  AllMutationBatchesAffectingDocumentKeys(
      const model::DocumentKeySet& document_keys) = 0;

  /**
   * Finds all mutation batches that could @em possibly affect the given
   * document key. Not all mutations in a batch will necessarily affect the
   * document key, so when looping through the batch you'll need to check that
   * the mutation itself matches the key.
   *
   * Note that because of this requirement implementations are free to return
   * mutation batches that don't contain the document key at all if it's
   * convenient.
   */
  // TODO(mcg): This should really return an iterator
<<<<<<< HEAD
<<<<<<< HEAD
  virtual std::vector<model::MutationBatch>
  AllMutationBatchesAffectingDocumentKey(const model::DocumentKey& key) = 0;
=======
  virtual std::vector<FSTMutationBatch*> AllMutationBatchesAffectingDocumentKey(
      const model::DocumentKey& key) = 0;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  virtual std::vector<FSTMutationBatch*> AllMutationBatchesAffectingDocumentKey(
      const model::DocumentKey& key) = 0;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

  /**
   * Finds all mutation batches that could affect the results for the given
   * query. Not all mutations in a batch will necessarily affect the query, so
   * when looping through the batch you'll need to check that the mutation
   * itself matches the query.
   *
   * Note that because of this requirement implementations are free to return
   * mutation batches that don't match the query at all if it's convenient.
   *
<<<<<<< HEAD
<<<<<<< HEAD
   * NOTE: A PatchMutation does not need to include all fields in the query
=======
   * NOTE: A FSTPatchMutation does not need to include all fields in the query
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
   * NOTE: A FSTPatchMutation does not need to include all fields in the query
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
   * filter criteria in order to be a match (but any fields it does contain do
   * need to match).
   */
  // TODO(mikelehen): This should perhaps return an iterator, though I'm not
  // sure we can avoid loading them all in memory.
<<<<<<< HEAD
<<<<<<< HEAD
  virtual std::vector<model::MutationBatch> AllMutationBatchesAffectingQuery(
      const core::Query& query) = 0;

  /** Loads the mutation batch with the given batch_id. */
  virtual absl::optional<model::MutationBatch> LookupMutationBatch(
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  virtual std::vector<FSTMutationBatch*> AllMutationBatchesAffectingQuery(
      FSTQuery* query) = 0;

  /** Loads the mutation batch with the given batch_id. */
  virtual FSTMutationBatch* _Nullable LookupMutationBatch(
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
      model::BatchId batch_id) = 0;

  /**
   * Gets the first unacknowledged mutation batch after the passed in batchId in
   * the mutation queue or nil if empty.
   *
   * @param batch_id The batch to search after, or kBatchIdUnknown for the first
   * mutation in the queue.
   *
   * @return the next mutation or nil if there wasn't one.
   */
<<<<<<< HEAD
<<<<<<< HEAD
  virtual absl::optional<model::MutationBatch> NextMutationBatchAfterBatchId(
      model::BatchId batch_id) = 0;

  /**
   * Gets the largest (latest) batch id in mutation queue for the current user
   * that is pending server response, returns `kBatchIdUnknown` if the queue
   * is empty.
   *
   * @return the largest batch id in the mutation queue that is not
   * acknowledged.
   */
  virtual model::BatchId GetHighestUnacknowledgedBatchId() = 0;

  /**
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  virtual FSTMutationBatch* _Nullable NextMutationBatchAfterBatchId(
      model::BatchId batch_id) = 0;

  /**
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
   * Performs a consistency check, examining the mutation queue for any leaks,
   * if possible.
   */
  virtual void PerformConsistencyCheck() = 0;

  /** Returns the current stream token for this mutation queue. */
<<<<<<< HEAD
<<<<<<< HEAD
  virtual nanopb::ByteString GetLastStreamToken() = 0;

  /** Sets the stream token for this mutation queue. */
  virtual void SetLastStreamToken(const nanopb::ByteString& stream_token) = 0;
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  virtual NSData* _Nullable GetLastStreamToken() = 0;

  /** Sets the stream token for this mutation queue. */
  virtual void SetLastStreamToken(NSData* _Nullable stream_token) = 0;
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
};

}  // namespace local
}  // namespace firestore
}  // namespace firebase

NS_ASSUME_NONNULL_END

#endif  // FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_LOCAL_MUTATION_QUEUE_H_
