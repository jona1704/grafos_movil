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

#include "Firestore/core/src/firebase/firestore/local/memory_remote_document_cache.h"

<<<<<<< HEAD
#include <utility>

#import "Firestore/Source/Local/FSTMemoryPersistence.h"

#include "Firestore/core/src/firebase/firestore/local/sizer.h"
#include "Firestore/core/src/firebase/firestore/util/hard_assert.h"

=======
#import "Firestore/Protos/objc/firestore/local/MaybeDocument.pbobjc.h"
#import "Firestore/Source/Core/FSTQuery.h"
#import "Firestore/Source/Local/FSTMemoryPersistence.h"
#import "Firestore/Source/Model/FSTDocument.h"

#include "Firestore/core/src/firebase/firestore/util/hard_assert.h"

using firebase::firestore::model::DocumentKey;
using firebase::firestore::model::DocumentKeySet;
using firebase::firestore::model::DocumentMap;
using firebase::firestore::model::ListenSequenceNumber;
using firebase::firestore::model::MaybeDocumentMap;

>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
namespace firebase {
namespace firestore {
namespace local {

<<<<<<< HEAD
using core::Query;
using model::Document;
using model::DocumentKey;
using model::DocumentKeySet;
using model::DocumentMap;
using model::ListenSequenceNumber;
using model::MaybeDocument;
using model::MaybeDocumentMap;
using model::OptionalMaybeDocumentMap;
=======
namespace {
/**
 * Returns an estimate of the number of bytes used to store the given
 * document key in memory. This is only an estimate and includes the size
 * of the segments of the path, but not any object overhead or path separators.
 */
size_t DocumentKeyByteSize(const DocumentKey& key) {
  size_t count = 0;
  for (const auto& segment : key.path()) {
    count += segment.size();
  }
  return count;
}
}  // namespace
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

MemoryRemoteDocumentCache::MemoryRemoteDocumentCache(
    FSTMemoryPersistence* persistence) {
  persistence_ = persistence;
}

<<<<<<< HEAD
void MemoryRemoteDocumentCache::Add(const MaybeDocument& document) {
  docs_ = docs_.insert(document.key(), document);

  persistence_.indexManager->AddToCollectionParentIndex(
      document.key().path().PopLast());
=======
void MemoryRemoteDocumentCache::Add(FSTMaybeDocument* document) {
  docs_ = docs_.insert(document.key, document);

  persistence_.indexManager->AddToCollectionParentIndex(
      document.key.path().PopLast());
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
}

void MemoryRemoteDocumentCache::Remove(const DocumentKey& key) {
  docs_ = docs_.erase(key);
}

<<<<<<< HEAD
absl::optional<MaybeDocument> MemoryRemoteDocumentCache::Get(
    const DocumentKey& key) {
  return docs_.get(key);
}

OptionalMaybeDocumentMap MemoryRemoteDocumentCache::GetAll(
    const DocumentKeySet& keys) {
  OptionalMaybeDocumentMap results;
  for (const DocumentKey& key : keys) {
    // Make sure each key has a corresponding entry, which is nullopt in case
    // the document is not found.
=======
FSTMaybeDocument* _Nullable MemoryRemoteDocumentCache::Get(
    const DocumentKey& key) {
  auto found = docs_.find(key);
  return found != docs_.end() ? found->second : nil;
}

MaybeDocumentMap MemoryRemoteDocumentCache::GetAll(const DocumentKeySet& keys) {
  MaybeDocumentMap results;
  for (const DocumentKey& key : keys) {
    // Make sure each key has a corresponding entry, which is null in case the
    // document is not found.
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    // TODO(http://b/32275378): Don't conflate missing / deleted.
    results = results.insert(key, Get(key));
  }
  return results;
}

<<<<<<< HEAD
DocumentMap MemoryRemoteDocumentCache::GetMatching(const Query& query) {
  HARD_ASSERT(
      !query.IsCollectionGroupQuery(),
=======
DocumentMap MemoryRemoteDocumentCache::GetMatching(FSTQuery* query) {
  HARD_ASSERT(
      ![query isCollectionGroupQuery],
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
      "CollectionGroup queries should be handled in LocalDocumentsView");

  DocumentMap results;

  // Documents are ordered by key, so we can use a prefix scan to narrow down
  // the documents we need to match the query against.
<<<<<<< HEAD
  DocumentKey prefix{query.path().Append("")};
  for (auto it = docs_.lower_bound(prefix); it != docs_.end(); ++it) {
    const DocumentKey& key = it->first;
    if (!query.path().IsPrefixOf(key.path())) {
      break;
    }
    const MaybeDocument& maybe_doc = it->second;
    if (!maybe_doc.is_document()) {
      continue;
    }

    Document doc(maybe_doc);
    if (query.Matches(doc)) {
      results = results.insert(key, std::move(doc));
=======
  DocumentKey prefix{query.path.Append("")};
  for (auto it = docs_.lower_bound(prefix); it != docs_.end(); ++it) {
    const DocumentKey& key = it->first;
    if (!query.path.IsPrefixOf(key.path())) {
      break;
    }
    FSTMaybeDocument* maybeDoc = it->second;
    if (![maybeDoc isKindOfClass:[FSTDocument class]]) {
      continue;
    }
    FSTDocument* doc = static_cast<FSTDocument*>(maybeDoc);
    if ([query matchesDocument:doc]) {
      results = results.insert(key, doc);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    }
  }
  return results;
}

std::vector<DocumentKey> MemoryRemoteDocumentCache::RemoveOrphanedDocuments(
    FSTMemoryLRUReferenceDelegate* reference_delegate,
    ListenSequenceNumber upper_bound) {
  std::vector<DocumentKey> removed;
  MaybeDocumentMap updated_docs = docs_;
  for (const auto& kv : docs_) {
    const DocumentKey& key = kv.first;
    if (![reference_delegate isPinnedAtSequenceNumber:upper_bound
                                             document:key]) {
      updated_docs = updated_docs.erase(key);
      removed.push_back(key);
    }
  }
  docs_ = updated_docs;
  return removed;
}

<<<<<<< HEAD
int64_t MemoryRemoteDocumentCache::CalculateByteSize(const Sizer& sizer) {
  int64_t count = 0;
  for (const auto& kv : docs_) {
    count += sizer.CalculateByteSize(kv.second);
=======
size_t MemoryRemoteDocumentCache::CalculateByteSize(
    FSTLocalSerializer* serializer) {
  size_t count = 0;
  for (const auto& kv : docs_) {
    count += DocumentKeyByteSize(kv.first);
    count += [[serializer encodedMaybeDocument:kv.second] serializedSize];
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  }
  return count;
}

}  // namespace local
}  // namespace firestore
}  // namespace firebase