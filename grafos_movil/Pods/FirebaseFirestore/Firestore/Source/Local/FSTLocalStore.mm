/*
 * Copyright 2017 Google
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

#import "Firestore/Source/Local/FSTLocalStore.h"

#include <memory>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

#import "FIRTimestamp.h"
<<<<<<< HEAD
#import "Firestore/Source/Local/FSTPersistence.h"
=======
#import "Firestore/Source/Core/FSTQuery.h"
#import "Firestore/Source/Local/FSTLRUGarbageCollector.h"
#import "Firestore/Source/Local/FSTLocalViewChanges.h"
#import "Firestore/Source/Local/FSTLocalWriteResult.h"
#import "Firestore/Source/Local/FSTPersistence.h"
#import "Firestore/Source/Local/FSTQueryData.h"
#import "Firestore/Source/Model/FSTDocument.h"
#import "Firestore/Source/Model/FSTMutation.h"
#import "Firestore/Source/Model/FSTMutationBatch.h"
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

#include "Firestore/core/include/firebase/firestore/timestamp.h"
#include "Firestore/core/src/firebase/firestore/auth/user.h"
#include "Firestore/core/src/firebase/firestore/core/target_id_generator.h"
#include "Firestore/core/src/firebase/firestore/immutable/sorted_set.h"
#include "Firestore/core/src/firebase/firestore/local/local_documents_view.h"
<<<<<<< HEAD
#include "Firestore/core/src/firebase/firestore/local/local_view_changes.h"
#include "Firestore/core/src/firebase/firestore/local/local_write_result.h"
#include "Firestore/core/src/firebase/firestore/local/mutation_queue.h"
#include "Firestore/core/src/firebase/firestore/local/query_cache.h"
#include "Firestore/core/src/firebase/firestore/local/query_data.h"
=======
#include "Firestore/core/src/firebase/firestore/local/mutation_queue.h"
#include "Firestore/core/src/firebase/firestore/local/query_cache.h"
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#include "Firestore/core/src/firebase/firestore/local/reference_set.h"
#include "Firestore/core/src/firebase/firestore/local/remote_document_cache.h"
#include "Firestore/core/src/firebase/firestore/model/document_key_set.h"
#include "Firestore/core/src/firebase/firestore/model/document_map.h"
<<<<<<< HEAD
#include "Firestore/core/src/firebase/firestore/model/mutation_batch.h"
#include "Firestore/core/src/firebase/firestore/model/mutation_batch_result.h"
#include "Firestore/core/src/firebase/firestore/model/patch_mutation.h"
#include "Firestore/core/src/firebase/firestore/model/snapshot_version.h"
#include "Firestore/core/src/firebase/firestore/nanopb/nanopb_util.h"
#include "Firestore/core/src/firebase/firestore/remote/remote_event.h"
#include "Firestore/core/src/firebase/firestore/util/hard_assert.h"
#include "Firestore/core/src/firebase/firestore/util/log.h"
#include "Firestore/core/src/firebase/firestore/util/to_string.h"
#include "absl/memory/memory.h"
#include "absl/types/optional.h"

namespace util = firebase::firestore::util;
using firebase::Timestamp;
using firebase::firestore::auth::User;
using firebase::firestore::core::Query;
using firebase::firestore::core::TargetIdGenerator;
using firebase::firestore::local::LocalDocumentsView;
using firebase::firestore::local::LocalViewChanges;
using firebase::firestore::local::LocalWriteResult;
using firebase::firestore::local::LruResults;
using firebase::firestore::local::MutationQueue;
using firebase::firestore::local::QueryCache;
using firebase::firestore::local::QueryData;
using firebase::firestore::local::QueryPurpose;
=======
#include "Firestore/core/src/firebase/firestore/model/snapshot_version.h"
#include "Firestore/core/src/firebase/firestore/remote/remote_event.h"
#include "Firestore/core/src/firebase/firestore/util/hard_assert.h"
#include "Firestore/core/src/firebase/firestore/util/log.h"
#include "absl/memory/memory.h"
#include "absl/types/optional.h"

using firebase::Timestamp;
using firebase::firestore::auth::User;
using firebase::firestore::core::TargetIdGenerator;
using firebase::firestore::local::LocalDocumentsView;
using firebase::firestore::local::LruResults;
using firebase::firestore::local::MutationQueue;
using firebase::firestore::local::QueryCache;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
using firebase::firestore::local::ReferenceSet;
using firebase::firestore::local::RemoteDocumentCache;
using firebase::firestore::model::BatchId;
using firebase::firestore::model::DocumentKey;
using firebase::firestore::model::DocumentKeySet;
using firebase::firestore::model::DocumentMap;
using firebase::firestore::model::DocumentVersionMap;
using firebase::firestore::model::FieldMask;
using firebase::firestore::model::FieldPath;
using firebase::firestore::model::ListenSequenceNumber;
<<<<<<< HEAD
using firebase::firestore::model::MaybeDocument;
using firebase::firestore::model::MaybeDocumentMap;
using firebase::firestore::model::Mutation;
using firebase::firestore::model::MutationBatch;
using firebase::firestore::model::MutationBatchResult;
using firebase::firestore::model::ObjectValue;
using firebase::firestore::model::OptionalMaybeDocumentMap;
using firebase::firestore::model::PatchMutation;
using firebase::firestore::model::Precondition;
using firebase::firestore::model::SnapshotVersion;
using firebase::firestore::model::TargetId;
using firebase::firestore::nanopb::ByteString;
=======
using firebase::firestore::model::MaybeDocumentMap;
using firebase::firestore::model::ObjectValue;
using firebase::firestore::model::Precondition;
using firebase::firestore::model::SnapshotVersion;
using firebase::firestore::model::TargetId;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
using firebase::firestore::remote::RemoteEvent;
using firebase::firestore::remote::TargetChange;

NS_ASSUME_NONNULL_BEGIN

/**
 * The maximum time to leave a resume token buffered without writing it out. This value is
 * arbitrary: it's long enough to avoid several writes (possibly indefinitely if updates come more
 * frequently than this) but short enough that restarting after crashing will still have a pretty
 * recent resume token.
 */
static const int64_t kResumeTokenMaxAgeSeconds = 5 * 60;  // 5 minutes

@interface FSTLocalStore ()

/** Manages our in-memory or durable persistence. */
@property(nonatomic, strong, readonly) id<FSTPersistence> persistence;

/** Maps a query to the data about that query. */
@property(nonatomic) QueryCache *queryCache;

@end

@implementation FSTLocalStore {
  /** Used to generate targetIDs for queries tracked locally. */
  TargetIdGenerator _targetIDGenerator;
  /** The set of all cached remote documents. */
  RemoteDocumentCache *_remoteDocumentCache;
  QueryCache *_queryCache;
  /** The set of all mutations that have been sent but not yet been applied to the backend. */
  MutationQueue *_mutationQueue;

  /** The "local" view of all documents (layering mutationQueue on top of remoteDocumentCache). */
  std::unique_ptr<LocalDocumentsView> _localDocuments;

  /** The set of document references maintained by any local views. */
  ReferenceSet _localViewReferences;

  /** Maps a targetID to data about its query. */
<<<<<<< HEAD
  std::unordered_map<TargetId, QueryData> _targetIDs;
=======
  std::unordered_map<TargetId, FSTQueryData *> _targetIDs;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
}

- (instancetype)initWithPersistence:(id<FSTPersistence>)persistence
                        initialUser:(const User &)initialUser {
  if (self = [super init]) {
    _persistence = persistence;
    _mutationQueue = [persistence mutationQueueForUser:initialUser];
    _remoteDocumentCache = [persistence remoteDocumentCache];
    _queryCache = [persistence queryCache];
    _localDocuments = absl::make_unique<LocalDocumentsView>(_remoteDocumentCache, _mutationQueue,
                                                            [_persistence indexManager]);
    [_persistence.referenceDelegate addInMemoryPins:&_localViewReferences];

    _targetIDGenerator = TargetIdGenerator::QueryCacheTargetIdGenerator(0);
  }
  return self;
}

- (void)start {
  [self startMutationQueue];
  TargetId targetID = _queryCache->highest_target_id();
  _targetIDGenerator = TargetIdGenerator::QueryCacheTargetIdGenerator(targetID);
}

- (void)startMutationQueue {
  self.persistence.run("Start MutationQueue", [&]() { _mutationQueue->Start(); });
}

- (MaybeDocumentMap)userDidChange:(const User &)user {
  // Swap out the mutation queue, grabbing the pending mutation batches before and after.
<<<<<<< HEAD
  std::vector<MutationBatch> oldBatches =
      self.persistence.run("OldBatches", [&] { return _mutationQueue->AllMutationBatches(); });
=======
  std::vector<FSTMutationBatch *> oldBatches = self.persistence.run(
      "OldBatches",
      [&]() -> std::vector<FSTMutationBatch *> { return _mutationQueue->AllMutationBatches(); });
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

  // The old one has a reference to the mutation queue, so nil it out first.
  _localDocuments.reset();
  _mutationQueue = [self.persistence mutationQueueForUser:user];

  [self startMutationQueue];

<<<<<<< HEAD
  return self.persistence.run("NewBatches", [&] {
    std::vector<MutationBatch> newBatches = _mutationQueue->AllMutationBatches();
=======
  return self.persistence.run("NewBatches", [&]() -> MaybeDocumentMap {
    std::vector<FSTMutationBatch *> newBatches = _mutationQueue->AllMutationBatches();
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

    // Recreate our LocalDocumentsView using the new MutationQueue.
    _localDocuments = absl::make_unique<LocalDocumentsView>(_remoteDocumentCache, _mutationQueue,
                                                            [_persistence indexManager]);

    // Union the old/new changed keys.
    DocumentKeySet changedKeys;
<<<<<<< HEAD
    for (const std::vector<MutationBatch> *batches : {&oldBatches, &newBatches}) {
      for (const MutationBatch &batch : *batches) {
        for (const Mutation &mutation : batch.mutations()) {
          changedKeys = changedKeys.insert(mutation.key());
=======
    for (const std::vector<FSTMutationBatch *> &batches : {oldBatches, newBatches}) {
      for (FSTMutationBatch *batch : batches) {
        for (FSTMutation *mutation : [batch mutations]) {
          changedKeys = changedKeys.insert(mutation.key);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
        }
      }
    }

    // Return the set of all (potentially) changed documents as the result of the user change.
    return _localDocuments->GetDocuments(changedKeys);
  });
}

<<<<<<< HEAD
- (LocalWriteResult)locallyWriteMutations:(std::vector<Mutation> &&)mutations {
  Timestamp localWriteTime = Timestamp::Now();
  DocumentKeySet keys;
  for (const Mutation &mutation : mutations) {
    keys = keys.insert(mutation.key());
  }

  return self.persistence.run("Locally write mutations", [&] {
=======
- (FSTLocalWriteResult *)locallyWriteMutations:(std::vector<FSTMutation *> &&)mutations {
  Timestamp localWriteTime = Timestamp::Now();
  DocumentKeySet keys;
  for (FSTMutation *mutation : mutations) {
    keys = keys.insert(mutation.key);
  }

  return self.persistence.run("Locally write mutations", [&]() -> FSTLocalWriteResult * {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    // Load and apply all existing mutations. This lets us compute the current base state for
    // all non-idempotent transforms before applying any additional user-provided writes.
    MaybeDocumentMap existingDocuments = _localDocuments->GetDocuments(keys);

    // For non-idempotent mutations (such as `FieldValue.increment()`), we record the base
    // state in a separate patch mutation. This is later used to guarantee consistent values
    // and prevents flicker even if the backend sends us an update that already includes our
    // transform.
<<<<<<< HEAD
    std::vector<Mutation> baseMutations;
    for (const Mutation &mutation : mutations) {
      absl::optional<MaybeDocument> base_document = existingDocuments.get(mutation.key());

      absl::optional<ObjectValue> base_value = mutation.ExtractBaseValue(base_document);
      if (base_value) {
        // NOTE: The base state should only be applied if there's some existing document to
        // override, so use a Precondition of exists=true
        baseMutations.push_back(PatchMutation(
            mutation.key(), *base_value, base_value->ToFieldMask(), Precondition::Exists(true)));
      }
    }

    MutationBatch batch = _mutationQueue->AddMutationBatch(localWriteTime, std::move(baseMutations),
                                                           std::move(mutations));
    MaybeDocumentMap changedDocuments = batch.ApplyToLocalDocumentSet(existingDocuments);
    return LocalWriteResult{batch.batch_id(), std::move(changedDocuments)};
  });
}

- (MaybeDocumentMap)acknowledgeBatchWithResult:(const MutationBatchResult &)batchResult {
  return self.persistence.run("Acknowledge batch", [&] {
    const MutationBatch &batch = batchResult.batch();
    _mutationQueue->AcknowledgeBatch(batch, batchResult.stream_token());
    [self applyBatchResult:batchResult];
    _mutationQueue->PerformConsistencyCheck();

    return _localDocuments->GetDocuments(batch.keys());
=======
    std::vector<FSTMutation *> baseMutations;
    for (FSTMutation *mutation : mutations) {
      auto base_document_it = existingDocuments.find(mutation.key);
      FSTMaybeDocument *base_document =
          base_document_it != existingDocuments.end() ? base_document_it->second : nil;

      absl::optional<ObjectValue> base_value = [mutation extractBaseValue:base_document];
      if (base_value) {
        // NOTE: The base state should only be applied if there's some existing document to
        // override, so use a Precondition of exists=true
        baseMutations.push_back([[FSTPatchMutation alloc] initWithKey:mutation.key
                                                            fieldMask:base_value->ToFieldMask()
                                                                value:*base_value
                                                         precondition:Precondition::Exists(true)]);
      }
    }

    FSTMutationBatch *batch = _mutationQueue->AddMutationBatch(
        localWriteTime, std::move(baseMutations), std::move(mutations));
    MaybeDocumentMap changedDocuments = [batch applyToLocalDocumentSet:existingDocuments];
    return [FSTLocalWriteResult resultForBatchID:batch.batchID changes:std::move(changedDocuments)];
  });
}

- (MaybeDocumentMap)acknowledgeBatchWithResult:(FSTMutationBatchResult *)batchResult {
  return self.persistence.run("Acknowledge batch", [&]() -> MaybeDocumentMap {
    FSTMutationBatch *batch = batchResult.batch;
    _mutationQueue->AcknowledgeBatch(batch, batchResult.streamToken);
    [self applyBatchResult:batchResult];
    _mutationQueue->PerformConsistencyCheck();

    return _localDocuments->GetDocuments(batch.keys);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  });
}

- (MaybeDocumentMap)rejectBatchID:(BatchId)batchID {
<<<<<<< HEAD
  return self.persistence.run("Reject batch", [&] {
    absl::optional<MutationBatch> toReject = _mutationQueue->LookupMutationBatch(batchID);
    HARD_ASSERT(toReject.has_value(), "Attempt to reject nonexistent batch!");

    _mutationQueue->RemoveMutationBatch(*toReject);
    _mutationQueue->PerformConsistencyCheck();

    return _localDocuments->GetDocuments(toReject->keys());
  });
}

- (ByteString)lastStreamToken {
  return _mutationQueue->GetLastStreamToken();
}

- (void)setLastStreamToken:(const ByteString &)streamToken {
=======
  return self.persistence.run("Reject batch", [&]() -> MaybeDocumentMap {
    FSTMutationBatch *toReject = _mutationQueue->LookupMutationBatch(batchID);
    HARD_ASSERT(toReject, "Attempt to reject nonexistent batch!");

    _mutationQueue->RemoveMutationBatch(toReject);
    _mutationQueue->PerformConsistencyCheck();

    return _localDocuments->GetDocuments(toReject.keys);
  });
}

- (nullable NSData *)lastStreamToken {
  return _mutationQueue->GetLastStreamToken();
}

- (void)setLastStreamToken:(nullable NSData *)streamToken {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  self.persistence.run("Set stream token",
                       [&]() { _mutationQueue->SetLastStreamToken(streamToken); });
}

- (const SnapshotVersion &)lastRemoteSnapshotVersion {
  return self.queryCache->GetLastRemoteSnapshotVersion();
}

- (MaybeDocumentMap)applyRemoteEvent:(const RemoteEvent &)remoteEvent {
<<<<<<< HEAD
  const SnapshotVersion &lastRemoteVersion = _queryCache->GetLastRemoteSnapshotVersion();

  return self.persistence.run("Apply remote event", [&] {
    // TODO(gsoltis): move the sequence number into the reference delegate.
    ListenSequenceNumber sequenceNumber = self.persistence.currentSequenceNumber;

=======
  return self.persistence.run("Apply remote event", [&]() -> MaybeDocumentMap {
    // TODO(gsoltis): move the sequence number into the reference delegate.
    ListenSequenceNumber sequenceNumber = self.persistence.currentSequenceNumber;

    DocumentKeySet authoritativeUpdates;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    for (const auto &entry : remoteEvent.target_changes()) {
      TargetId targetID = entry.first;
      const TargetChange &change = entry.second;

<<<<<<< HEAD
      auto found = _targetIDs.find(targetID);
      if (found == _targetIDs.end()) {
        // We don't update the remote keys if the query is not active. This ensures that
        // we persist the updated query data along with the updated assignment.
        continue;
      }

      QueryData oldQueryData = found->second;
=======
      // Do not ref/unref unassigned targetIDs - it may lead to leaks.
      auto found = _targetIDs.find(targetID);
      if (found == _targetIDs.end()) {
        continue;
      }
      FSTQueryData *queryData = found->second;

      // When a global snapshot contains updates (either add or modify) we can completely trust
      // these updates as authoritative and blindly apply them to our cache (as a defensive measure
      // to promote self-healing in the unfortunate case that our cache is ever somehow corrupted /
      // out-of-sync).
      //
      // If the document is only updated while removing it from a target then watch isn't obligated
      // to send the absolute latest version: it can send the first version that caused the document
      // not to match.
      for (const DocumentKey &key : change.added_documents()) {
        authoritativeUpdates = authoritativeUpdates.insert(key);
      }
      for (const DocumentKey &key : change.modified_documents()) {
        authoritativeUpdates = authoritativeUpdates.insert(key);
      }
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

      _queryCache->RemoveMatchingKeys(change.removed_documents(), targetID);
      _queryCache->AddMatchingKeys(change.added_documents(), targetID);

      // Update the resume token if the change includes one. Don't clear any preexisting value.
      // Bump the sequence number as well, so that documents being removed now are ordered later
      // than documents that were previously removed from this target.
<<<<<<< HEAD
      const ByteString &resumeToken = change.resume_token();
      // Update the resume token if the change includes one.
      if (!resumeToken.empty()) {
        QueryData newQueryData =
            oldQueryData.Copy(remoteEvent.snapshot_version(), resumeToken, sequenceNumber);
        _targetIDs[targetID] = newQueryData;

        // Update the query data if there are target changes (or if sufficient time has
        // passed since the last update).
        if ([self shouldPersistQueryData:newQueryData oldQueryData:oldQueryData change:change]) {
          _queryCache->UpdateTarget(newQueryData);
=======
      NSData *resumeToken = change.resume_token();
      if (resumeToken.length > 0) {
        FSTQueryData *oldQueryData = queryData;
        queryData = [queryData queryDataByReplacingSnapshotVersion:remoteEvent.snapshot_version()
                                                       resumeToken:resumeToken
                                                    sequenceNumber:sequenceNumber];
        _targetIDs[targetID] = queryData;

        if ([self shouldPersistQueryData:queryData oldQueryData:oldQueryData change:change]) {
          _queryCache->UpdateTarget(queryData);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
        }
      }
    }

<<<<<<< HEAD
    OptionalMaybeDocumentMap changedDocs;
=======
    MaybeDocumentMap changedDocs;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    const DocumentKeySet &limboDocuments = remoteEvent.limbo_document_changes();
    DocumentKeySet updatedKeys;
    for (const auto &kv : remoteEvent.document_updates()) {
      updatedKeys = updatedKeys.insert(kv.first);
    }
    // Each loop iteration only affects its "own" doc, so it's safe to get all the remote
    // documents in advance in a single call.
<<<<<<< HEAD
    OptionalMaybeDocumentMap existingDocs = _remoteDocumentCache->GetAll(updatedKeys);

    for (const auto &kv : remoteEvent.document_updates()) {
      const DocumentKey &key = kv.first;
      const MaybeDocument &doc = kv.second;
      absl::optional<MaybeDocument> existingDoc;
      auto foundExisting = existingDocs.get(key);
      if (foundExisting) {
        existingDoc = *foundExisting;
      }

      if (!existingDoc || doc.version() > existingDoc->version() ||
          (doc.version() == existingDoc->version() && existingDoc->has_pending_writes())) {
        _remoteDocumentCache->Add(doc);
        changedDocs = changedDocs.insert(key, doc);
      } else if (doc.type() == MaybeDocument::Type::NoDocument &&
                 doc.version() == SnapshotVersion::None()) {
        // NoDocuments with SnapshotVersion.MIN are used in manufactured events (e.g. in the case
        // of a limbo document resolution failing). We remove these documents from cache since we
        // lost access.
        _remoteDocumentCache->Remove(key);
        changedDocs = changedDocs.insert(key, doc);
      } else {
        LOG_DEBUG("FSTLocalStore Ignoring outdated watch update for %s. "
                  "Current version: %s  Watch version: %s",
                  key.ToString(), existingDoc->version().ToString(), doc.version().ToString());
=======
    MaybeDocumentMap existingDocs = _remoteDocumentCache->GetAll(updatedKeys);

    for (const auto &kv : remoteEvent.document_updates()) {
      const DocumentKey &key = kv.first;
      FSTMaybeDocument *doc = kv.second;
      FSTMaybeDocument *existingDoc = nil;
      auto foundExisting = existingDocs.find(key);
      if (foundExisting != existingDocs.end()) {
        existingDoc = foundExisting->second;
      }

      // If a document update isn't authoritative, make sure we don't apply an old document version
      // to the remote cache. We make an exception for SnapshotVersion.MIN which can happen for
      // manufactured events (e.g. in the case of a limbo document resolution failing).
      if (!existingDoc || doc.version == SnapshotVersion::None() ||
          (authoritativeUpdates.contains(doc.key) && !existingDoc.hasPendingWrites) ||
          doc.version >= existingDoc.version) {
        _remoteDocumentCache->Add(doc);
        changedDocs = changedDocs.insert(key, doc);
      } else {
        LOG_DEBUG("FSTLocalStore Ignoring outdated watch update for %s. "
                  "Current version: %s  Watch version: %s",
                  key.ToString(), existingDoc.version.timestamp().ToString(),
                  doc.version.timestamp().ToString());
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
      }

      // If this was a limbo resolution, make sure we mark when it was accessed.
      if (limboDocuments.contains(key)) {
        [self.persistence.referenceDelegate limboDocumentUpdated:key];
      }
    }

    // HACK: The only reason we allow omitting snapshot version is so we can synthesize remote
    // events when we get permission denied errors while trying to resolve the state of a locally
    // cached document that is in limbo.
<<<<<<< HEAD
=======
    const SnapshotVersion &lastRemoteVersion = _queryCache->GetLastRemoteSnapshotVersion();
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    const SnapshotVersion &remoteVersion = remoteEvent.snapshot_version();
    if (remoteVersion != SnapshotVersion::None()) {
      HARD_ASSERT(remoteVersion >= lastRemoteVersion,
                  "Watch stream reverted to previous snapshot?? (%s < %s)",
<<<<<<< HEAD
                  remoteVersion.ToString(), lastRemoteVersion.ToString());
=======
                  remoteVersion.timestamp().ToString(), lastRemoteVersion.timestamp().ToString());
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
      _queryCache->SetLastRemoteSnapshotVersion(remoteVersion);
    }

    return _localDocuments->GetLocalViewOfDocuments(changedDocs);
  });
}

/**
 * Returns YES if the newQueryData should be persisted during an update of an active target.
 * QueryData should always be persisted when a target is being released and should not call this
 * function.
 *
 * While the target is active, QueryData updates can be omitted when nothing about the target has
 * changed except metadata like the resume token or snapshot version. Occasionally it's worth the
 * extra write to prevent these values from getting too stale after a crash, but this doesn't have
 * to be too frequent.
 */
<<<<<<< HEAD
- (BOOL)shouldPersistQueryData:(const QueryData &)newQueryData
                  oldQueryData:(const QueryData &)oldQueryData
                        change:(const TargetChange &)change {
  // Avoid clearing any existing value
  HARD_ASSERT(!newQueryData.resume_token().empty(),
              "Attempted to persist query data with empty resume token");

  // Always persist query data if we don't already have a resume token.
  if (oldQueryData.resume_token().empty()) return YES;
=======
- (BOOL)shouldPersistQueryData:(FSTQueryData *)newQueryData
                  oldQueryData:(FSTQueryData *)oldQueryData
                        change:(const TargetChange &)change {
  // Avoid clearing any existing value
  if (newQueryData.resumeToken.length == 0) return NO;

  // Any resume token is interesting if there isn't one already.
  if (oldQueryData.resumeToken.length == 0) return YES;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

  // Don't allow resume token changes to be buffered indefinitely. This allows us to be reasonably
  // up-to-date after a crash and avoids needing to loop over all active queries on shutdown.
  // Especially in the browser we may not get time to do anything interesting while the current
  // tab is closing.
<<<<<<< HEAD
  int64_t newSeconds = newQueryData.snapshot_version().timestamp().seconds();
  int64_t oldSeconds = oldQueryData.snapshot_version().timestamp().seconds();
=======
  int64_t newSeconds = newQueryData.snapshotVersion.timestamp().seconds();
  int64_t oldSeconds = oldQueryData.snapshotVersion.timestamp().seconds();
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  int64_t timeDelta = newSeconds - oldSeconds;
  if (timeDelta >= kResumeTokenMaxAgeSeconds) return YES;

  // Otherwise if the only thing that has changed about a target is its resume token then it's not
  // worth persisting. Note that the RemoteStore keeps an in-memory view of the currently active
  // targets which includes the current resume token, so stream failure or user changes will still
  // use an up-to-date resume token regardless of what we do here.
  size_t changes = change.added_documents().size() + change.modified_documents().size() +
                   change.removed_documents().size();
  return changes > 0;
}

<<<<<<< HEAD
- (void)notifyLocalViewChanges:(const std::vector<LocalViewChanges> &)viewChanges {
  self.persistence.run("NotifyLocalViewChanges", [&]() {
    for (const LocalViewChanges &viewChange : viewChanges) {
      for (const DocumentKey &key : viewChange.removed_keys()) {
        [self->_persistence.referenceDelegate removeReference:key];
      }
      _localViewReferences.AddReferences(viewChange.added_keys(), viewChange.target_id());
      _localViewReferences.RemoveReferences(viewChange.removed_keys(), viewChange.target_id());
=======
- (void)notifyLocalViewChanges:(NSArray<FSTLocalViewChanges *> *)viewChanges {
  self.persistence.run("NotifyLocalViewChanges", [&]() {
    for (FSTLocalViewChanges *viewChange in viewChanges) {
      for (const DocumentKey &key : viewChange.removedKeys) {
        [self->_persistence.referenceDelegate removeReference:key];
      }
      _localViewReferences.AddReferences(viewChange.addedKeys, viewChange.targetID);
      _localViewReferences.AddReferences(viewChange.removedKeys, viewChange.targetID);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    }
  });
}

<<<<<<< HEAD
- (absl::optional<MutationBatch>)nextMutationBatchAfterBatchID:(BatchId)batchID {
  return self.persistence.run("NextMutationBatchAfterBatchID", [&] {
    return _mutationQueue->NextMutationBatchAfterBatchId(batchID);
  });
}

- (absl::optional<MaybeDocument>)readDocument:(const DocumentKey &)key {
  return self.persistence.run("ReadDocument", [&] { return _localDocuments->GetDocument(key); });
}

- (model::BatchId)getHighestUnacknowledgedBatchId {
  return self.persistence.run("getHighestUnacknowledgedBatchId",
                              [&]() { return _mutationQueue->GetHighestUnacknowledgedBatchId(); });
}

- (QueryData)allocateQuery:(Query)query {
  QueryData queryData = self.persistence.run("Allocate query", [&] {
    absl::optional<QueryData> cached = _queryCache->GetTarget(query);
    // TODO(mcg): freshen last accessed date if cached exists?
    if (!cached) {
      cached = QueryData(query, _targetIDGenerator.NextId(), self.persistence.currentSequenceNumber,
                         QueryPurpose::Listen);
      _queryCache->AddTarget(*cached);
    }
    return *cached;
  });
  // Sanity check to ensure that even when resuming a query it's not currently active.
  TargetId targetID = queryData.target_id();
  HARD_ASSERT(_targetIDs.find(targetID) == _targetIDs.end(),
              "Tried to allocate an already allocated query: %s", query.ToString());
=======
- (nullable FSTMutationBatch *)nextMutationBatchAfterBatchID:(BatchId)batchID {
  FSTMutationBatch *result =
      self.persistence.run("NextMutationBatchAfterBatchID", [&]() -> FSTMutationBatch * {
        return _mutationQueue->NextMutationBatchAfterBatchId(batchID);
      });
  return result;
}

- (nullable FSTMaybeDocument *)readDocument:(const DocumentKey &)key {
  return self.persistence.run("ReadDocument", [&]() -> FSTMaybeDocument *_Nullable {
    return _localDocuments->GetDocument(key);
  });
}

- (FSTQueryData *)allocateQuery:(FSTQuery *)query {
  FSTQueryData *queryData = self.persistence.run("Allocate query", [&]() -> FSTQueryData * {
    FSTQueryData *cached = _queryCache->GetTarget(query);
    // TODO(mcg): freshen last accessed date if cached exists?
    if (!cached) {
      cached = [[FSTQueryData alloc] initWithQuery:query
                                          targetID:_targetIDGenerator.NextId()
                              listenSequenceNumber:self.persistence.currentSequenceNumber
                                           purpose:FSTQueryPurposeListen];
      _queryCache->AddTarget(cached);
    }
    return cached;
  });
  // Sanity check to ensure that even when resuming a query it's not currently active.
  TargetId targetID = queryData.targetID;
  HARD_ASSERT(_targetIDs.find(targetID) == _targetIDs.end(),
              "Tried to allocate an already allocated query: %s", query);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  _targetIDs[targetID] = queryData;
  return queryData;
}

<<<<<<< HEAD
- (void)releaseQuery:(const Query &)query {
  self.persistence.run("Release query", [&]() {
    absl::optional<QueryData> queryData = _queryCache->GetTarget(query);
    HARD_ASSERT(queryData, "Tried to release nonexistent query: %s", query.ToString());

    TargetId targetID = queryData->target_id();

    auto found = _targetIDs.find(targetID);
    if (found != _targetIDs.end()) {
      const QueryData &cachedQueryData = found->second;

      if (cachedQueryData.snapshot_version() > queryData->snapshot_version()) {
=======
- (void)releaseQuery:(FSTQuery *)query {
  self.persistence.run("Release query", [&]() {
    FSTQueryData *queryData = _queryCache->GetTarget(query);
    HARD_ASSERT(queryData, "Tried to release nonexistent query: %s", query);

    TargetId targetID = queryData.targetID;

    auto found = _targetIDs.find(targetID);
    if (found != _targetIDs.end()) {
      FSTQueryData *cachedQueryData = found->second;

      if (cachedQueryData.snapshotVersion > queryData.snapshotVersion) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
        // If we've been avoiding persisting the resumeToken (see shouldPersistQueryData for
        // conditions and rationale) we need to persist the token now because there will no
        // longer be an in-memory version to fall back on.
        queryData = cachedQueryData;
<<<<<<< HEAD
        _queryCache->UpdateTarget(*queryData);
=======
        _queryCache->UpdateTarget(queryData);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
      }
    }

    // References for documents sent via Watch are automatically removed when we delete a
    // query's target data from the reference delegate. Since this does not remove references
    // for locally mutated documents, we have to remove the target associations for these
    // documents manually.
    DocumentKeySet removed = _localViewReferences.RemoveReferences(targetID);
    for (const DocumentKey &key : removed) {
      [self.persistence.referenceDelegate removeReference:key];
    }
    _targetIDs.erase(targetID);
<<<<<<< HEAD
    [self.persistence.referenceDelegate removeTarget:*queryData];
  });
}

- (DocumentMap)executeQuery:(const Query &)query {
  return self.persistence.run("ExecuteQuery",
                              [&] { return _localDocuments->GetDocumentsMatchingQuery(query); });
}

- (DocumentKeySet)remoteDocumentKeysForTarget:(TargetId)targetID {
  return self.persistence.run("RemoteDocumentKeysForTarget",
                              [&] { return _queryCache->GetMatchingKeys(targetID); });
}

- (void)applyBatchResult:(const MutationBatchResult &)batchResult {
  const MutationBatch &batch = batchResult.batch();
  DocumentKeySet docKeys = batch.keys();
  const DocumentVersionMap &versions = batchResult.doc_versions();
  for (const DocumentKey &docKey : docKeys) {
    absl::optional<MaybeDocument> remoteDoc = _remoteDocumentCache->Get(docKey);
    absl::optional<MaybeDocument> doc = remoteDoc;
=======
    [self.persistence.referenceDelegate removeTarget:queryData];
  });
}

- (DocumentMap)executeQuery:(FSTQuery *)query {
  return self.persistence.run("ExecuteQuery", [&]() -> DocumentMap {
    return _localDocuments->GetDocumentsMatchingQuery(query);
  });
}

- (DocumentKeySet)remoteDocumentKeysForTarget:(TargetId)targetID {
  return self.persistence.run("RemoteDocumentKeysForTarget", [&]() -> DocumentKeySet {
    return _queryCache->GetMatchingKeys(targetID);
  });
}

- (void)applyBatchResult:(FSTMutationBatchResult *)batchResult {
  FSTMutationBatch *batch = batchResult.batch;
  DocumentKeySet docKeys = batch.keys;
  const DocumentVersionMap &versions = batchResult.docVersions;
  for (const DocumentKey &docKey : docKeys) {
    FSTMaybeDocument *_Nullable remoteDoc = _remoteDocumentCache->Get(docKey);
    FSTMaybeDocument *_Nullable doc = remoteDoc;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

    auto ackVersionIter = versions.find(docKey);
    HARD_ASSERT(ackVersionIter != versions.end(),
                "docVersions should contain every doc in the write.");
    const SnapshotVersion &ackVersion = ackVersionIter->second;
<<<<<<< HEAD
    if (!doc || doc->version() < ackVersion) {
      doc = batch.ApplyToRemoteDocument(doc, docKey, batchResult);
      if (!doc) {
        HARD_ASSERT(!remoteDoc, "Mutation batch %s applied to document %s resulted in nullopt.",
                    batch.ToString(), util::ToString(remoteDoc));
      } else {
        _remoteDocumentCache->Add(*doc);
=======
    if (!doc || doc.version < ackVersion) {
      doc = [batch applyToRemoteDocument:doc documentKey:docKey mutationBatchResult:batchResult];
      if (!doc) {
        HARD_ASSERT(!remoteDoc, "Mutation batch %s applied to document %s resulted in nil.", batch,
                    remoteDoc);
      } else {
        _remoteDocumentCache->Add(doc);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
      }
    }
  }

  _mutationQueue->RemoveMutationBatch(batch);
}

<<<<<<< HEAD
- (LruResults)collectGarbage:(local::LruGarbageCollector *)garbageCollector {
  return self.persistence.run("Collect garbage",
                              [&] { return garbageCollector->Collect(_targetIDs); });
=======
- (LruResults)collectGarbage:(FSTLRUGarbageCollector *)garbageCollector {
  return self.persistence.run("Collect garbage", [&]() -> LruResults {
    return [garbageCollector collectWithLiveTargets:_targetIDs];
  });
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
}

@end

NS_ASSUME_NONNULL_END
