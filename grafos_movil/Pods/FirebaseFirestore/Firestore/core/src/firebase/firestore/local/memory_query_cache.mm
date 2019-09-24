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

#include "Firestore/core/src/firebase/firestore/local/memory_query_cache.h"

<<<<<<< HEAD
#include <vector>

#import "Firestore/Source/Local/FSTMemoryPersistence.h"

#include "Firestore/core/src/firebase/firestore/local/query_data.h"
#include "Firestore/core/src/firebase/firestore/local/sizer.h"
#include "Firestore/core/src/firebase/firestore/model/document_key.h"

NS_ASSUME_NONNULL_BEGIN
=======
#import <Protobuf/GPBMessage.h>

#include <vector>

#import "Firestore/Protos/objc/firestore/local/Target.pbobjc.h"
#import "Firestore/Source/Core/FSTQuery.h"
#import "Firestore/Source/Local/FSTMemoryPersistence.h"
#import "Firestore/Source/Local/FSTQueryData.h"

#include "Firestore/core/src/firebase/firestore/model/document_key.h"

using firebase::firestore::model::DocumentKey;
using firebase::firestore::model::DocumentKeySet;
using firebase::firestore::model::ListenSequenceNumber;
using firebase::firestore::model::SnapshotVersion;
using firebase::firestore::model::TargetId;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

namespace firebase {
namespace firestore {
namespace local {

<<<<<<< HEAD
using core::Query;
using model::DocumentKey;
using model::DocumentKeySet;
using model::ListenSequenceNumber;
using model::SnapshotVersion;
using model::TargetId;
=======
NS_ASSUME_NONNULL_BEGIN
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

MemoryQueryCache::MemoryQueryCache(FSTMemoryPersistence* persistence)
    : persistence_(persistence),
      highest_listen_sequence_number_(ListenSequenceNumber(0)),
      highest_target_id_(TargetId(0)),
      last_remote_snapshot_version_(SnapshotVersion::None()),
      queries_() {
}

<<<<<<< HEAD
void MemoryQueryCache::AddTarget(const QueryData& query_data) {
  queries_[query_data.query()] = query_data;
  if (query_data.target_id() > highest_target_id_) {
    highest_target_id_ = query_data.target_id();
  }
  if (query_data.sequence_number() > highest_listen_sequence_number_) {
    highest_listen_sequence_number_ = query_data.sequence_number();
  }
}

void MemoryQueryCache::UpdateTarget(const QueryData& query_data) {
=======
void MemoryQueryCache::AddTarget(FSTQueryData* query_data) {
  queries_[query_data.query] = query_data;
  if (query_data.targetID > highest_target_id_) {
    highest_target_id_ = query_data.targetID;
  }
  if (query_data.sequenceNumber > highest_listen_sequence_number_) {
    highest_listen_sequence_number_ = query_data.sequenceNumber;
  }
}

void MemoryQueryCache::UpdateTarget(FSTQueryData* query_data) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  // For the memory query cache, adds and updates are treated the same.
  AddTarget(query_data);
}

<<<<<<< HEAD
void MemoryQueryCache::RemoveTarget(const QueryData& query_data) {
  queries_.erase(query_data.query());
  references_.RemoveReferences(query_data.target_id());
}

absl::optional<QueryData> MemoryQueryCache::GetTarget(const Query& query) {
  auto iter = queries_.find(query);
  return iter == queries_.end() ? absl::optional<QueryData>{} : iter->second;
=======
void MemoryQueryCache::RemoveTarget(FSTQueryData* query_data) {
  queries_.erase(query_data.query);
  references_.RemoveReferences(query_data.targetID);
}

FSTQueryData* _Nullable MemoryQueryCache::GetTarget(FSTQuery* query) {
  auto iter = queries_.find(query);
  return iter == queries_.end() ? nil : iter->second;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
}

void MemoryQueryCache::EnumerateTargets(const TargetCallback& callback) {
  for (const auto& kv : queries_) {
    callback(kv.second);
  }
}

int MemoryQueryCache::RemoveTargets(
    model::ListenSequenceNumber upper_bound,
<<<<<<< HEAD
    const std::unordered_map<TargetId, QueryData>& live_targets) {
  std::vector<const Query*> to_remove;
  for (const auto& kv : queries_) {
    const Query& query = kv.first;
    const QueryData& query_data = kv.second;

    if (query_data.sequence_number() <= upper_bound) {
      if (live_targets.find(query_data.target_id()) == live_targets.end()) {
        to_remove.push_back(&query);
        references_.RemoveReferences(query_data.target_id());
=======
    const std::unordered_map<TargetId, FSTQueryData*>& live_targets) {
  std::vector<FSTQuery*> to_remove;
  for (const auto& kv : queries_) {
    FSTQuery* query = kv.first;
    FSTQueryData* query_data = kv.second;

    if (query_data.sequenceNumber <= upper_bound) {
      if (live_targets.find(query_data.targetID) == live_targets.end()) {
        to_remove.push_back(query);
        references_.RemoveReferences(query_data.targetID);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
      }
    }
  }

<<<<<<< HEAD
  for (const Query* element : to_remove) {
    queries_.erase(*element);
=======
  for (FSTQuery* element : to_remove) {
    queries_.erase(element);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  }
  return static_cast<int>(to_remove.size());
}

void MemoryQueryCache::AddMatchingKeys(const DocumentKeySet& keys,
                                       TargetId target_id) {
  references_.AddReferences(keys, target_id);
  for (const DocumentKey& key : keys) {
    [persistence_.referenceDelegate addReference:key];
  }
}

void MemoryQueryCache::RemoveMatchingKeys(const DocumentKeySet& keys,
                                          TargetId target_id) {
  references_.RemoveReferences(keys, target_id);
  for (const DocumentKey& key : keys) {
    [persistence_.referenceDelegate removeReference:key];
  }
}

DocumentKeySet MemoryQueryCache::GetMatchingKeys(TargetId target_id) {
  return references_.ReferencedKeys(target_id);
}

bool MemoryQueryCache::Contains(const DocumentKey& key) {
  return references_.ContainsKey(key);
}

<<<<<<< HEAD
int64_t MemoryQueryCache::CalculateByteSize(const Sizer& sizer) {
  int64_t count = 0;
  for (const auto& kv : queries_) {
    count += sizer.CalculateByteSize(kv.second);
=======
size_t MemoryQueryCache::CalculateByteSize(FSTLocalSerializer* serializer) {
  size_t count = 0;
  for (const auto& kv : queries_) {
    FSTQueryData* query_data = kv.second;
    count += [[serializer encodedQueryData:query_data] serializedSize];
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  }
  return count;
}

const SnapshotVersion& MemoryQueryCache::GetLastRemoteSnapshotVersion() const {
  return last_remote_snapshot_version_;
}

void MemoryQueryCache::SetLastRemoteSnapshotVersion(SnapshotVersion version) {
  last_remote_snapshot_version_ = std::move(version);
}

NS_ASSUME_NONNULL_END

}  // namespace local
}  // namespace firestore
}  // namespace firebase
