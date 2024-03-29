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

#ifndef FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_LOCAL_LEVELDB_MUTATION_QUEUE_H_
#define FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_LOCAL_LEVELDB_MUTATION_QUEUE_H_

#if !defined(__OBJC__)
#error "For now, this file must only be included by ObjC source files."
#endif  // !defined(__OBJC__)

#import <Foundation/Foundation.h>

#include <set>
#include <string>
#include <vector>

#include "Firestore/core/include/firebase/firestore/timestamp.h"
#include "Firestore/core/src/firebase/firestore/auth/user.h"
#include "Firestore/core/src/firebase/firestore/local/leveldb_key.h"
#include "Firestore/core/src/firebase/firestore/local/mutation_queue.h"
#include "Firestore/core/src/firebase/firestore/model/document_key.h"
#include "Firestore/core/src/firebase/firestore/model/document_key_set.h"
#include "Firestore/core/src/firebase/firestore/model/types.h"
#include "absl/strings/string_view.h"
#include "leveldb/db.h"

@class FSTLevelDB;
@class FSTLocalSerializer;
<<<<<<< HEAD
<<<<<<< HEAD
@class FSTPBMutationQueue;
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
@class FSTMutation;
@class FSTMutationBatch;
@class FSTPBMutationQueue;
@class FSTQuery;
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

NS_ASSUME_NONNULL_BEGIN

namespace firebase {
namespace firestore {
namespace local {

/**
 * Returns one larger than the largest batch ID that has been stored. If there
 * are no mutations returns 0. Note that batch IDs are global.
 */
model::BatchId LoadNextBatchIdFromDb(leveldb::DB* db);

class LevelDbMutationQueue : public MutationQueue {
 public:
  LevelDbMutationQueue(const auth::User& user,
                       FSTLevelDB* db,
                       FSTLocalSerializer* serializer);

  void Start() override;

  bool IsEmpty() override;

<<<<<<< HEAD
<<<<<<< HEAD
  void AcknowledgeBatch(const model::MutationBatch& batch,
                        const nanopb::ByteString& stream_token) override;

  model::MutationBatch AddMutationBatch(
      const Timestamp& local_write_time,
      std::vector<model::Mutation>&& base_mutations,
      std::vector<model::Mutation>&& mutations) override;

  void RemoveMutationBatch(const model::MutationBatch& batch) override;

  std::vector<model::MutationBatch> AllMutationBatches() override;

  std::vector<model::MutationBatch> AllMutationBatchesAffectingDocumentKeys(
      const model::DocumentKeySet& document_keys) override;

  std::vector<model::MutationBatch> AllMutationBatchesAffectingDocumentKey(
      const model::DocumentKey& key) override;

  std::vector<model::MutationBatch> AllMutationBatchesAffectingQuery(
      const core::Query& query) override;

  absl::optional<model::MutationBatch> LookupMutationBatch(
      model::BatchId batch_id) override;

  absl::optional<model::MutationBatch> NextMutationBatchAfterBatchId(
      model::BatchId batch_id) override;

  model::BatchId GetHighestUnacknowledgedBatchId() override;

  void PerformConsistencyCheck() override;

  nanopb::ByteString GetLastStreamToken() override;

  void SetLastStreamToken(const nanopb::ByteString& stream_token) override;
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  void AcknowledgeBatch(FSTMutationBatch* batch,
                        NSData* _Nullable stream_token) override;

  FSTMutationBatch* AddMutationBatch(
      const Timestamp& local_write_time,
      std::vector<FSTMutation*>&& base_mutations,
      std::vector<FSTMutation*>&& mutations) override;

  void RemoveMutationBatch(FSTMutationBatch* batch) override;

  std::vector<FSTMutationBatch*> AllMutationBatches() override;

  std::vector<FSTMutationBatch*> AllMutationBatchesAffectingDocumentKeys(
      const model::DocumentKeySet& document_keys) override;

  std::vector<FSTMutationBatch*> AllMutationBatchesAffectingDocumentKey(
      const model::DocumentKey& key) override;

  std::vector<FSTMutationBatch*> AllMutationBatchesAffectingQuery(
      FSTQuery* query) override;

  FSTMutationBatch* _Nullable LookupMutationBatch(
      model::BatchId batch_id) override;

  FSTMutationBatch* _Nullable NextMutationBatchAfterBatchId(
      model::BatchId batch_id) override;

  void PerformConsistencyCheck() override;

  NSData* _Nullable GetLastStreamToken() override;

  void SetLastStreamToken(NSData* _Nullable stream_token) override;
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

 private:
  /**
   * Constructs a vector of matching batches, sorted by batchID to ensure that
   * multiple mutations affecting the same document key are applied in order.
   */
<<<<<<< HEAD
<<<<<<< HEAD
  std::vector<model::MutationBatch> AllMutationBatchesWithIds(
=======
  std::vector<FSTMutationBatch*> AllMutationBatchesWithIds(
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  std::vector<FSTMutationBatch*> AllMutationBatchesWithIds(
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
      const std::set<model::BatchId>& batch_ids);

  std::string mutation_queue_key() {
    return LevelDbMutationQueueKey::Key(user_id_);
  }

  std::string mutation_batch_key(model::BatchId batch_id) {
    return LevelDbMutationKey::Key(user_id_, batch_id);
  }

  /** Parses the MutationQueue metadata from the given LevelDB row contents. */
  FSTPBMutationQueue* _Nullable MetadataForKey(const std::string& key);

<<<<<<< HEAD
<<<<<<< HEAD
  model::MutationBatch ParseMutationBatch(absl::string_view encoded);
=======
  FSTMutationBatch* ParseMutationBatch(absl::string_view encoded);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  FSTMutationBatch* ParseMutationBatch(absl::string_view encoded);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

  // This instance is owned by FSTLevelDB; avoid a retain cycle.
  __weak FSTLevelDB* db_;

  FSTLocalSerializer* serializer_;

  /**
   * The normalized userID (e.g. nil UID => @"" userID) used in our LevelDB
   * keys.
   */
  std::string user_id_;

  /**
   * Next value to use when assigning sequential IDs to each mutation batch.
   *
   * NOTE: There can only be one LevelDbMutationQueue for a given db at a time,
   * hence it is safe to track next_batch_id_ as an instance-level property.
   * Should we ever relax this constraint we'll need to revisit this.
   */
  model::BatchId next_batch_id_;

  /**
   * A write-through cache copy of the metadata describing the current queue.
   */
  FSTPBMutationQueue* _Nullable metadata_;
};

}  // namespace local
}  // namespace firestore
}  // namespace firebase

NS_ASSUME_NONNULL_END

#endif  // FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_LOCAL_LEVELDB_MUTATION_QUEUE_H_
