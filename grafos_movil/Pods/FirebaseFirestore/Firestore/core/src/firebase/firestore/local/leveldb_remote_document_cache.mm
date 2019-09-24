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

#include "Firestore/core/src/firebase/firestore/local/leveldb_remote_document_cache.h"

#import <Foundation/Foundation.h>

#include <string>

#import "Firestore/Protos/objc/firestore/local/MaybeDocument.pbobjc.h"
<<<<<<< HEAD
#import "Firestore/Source/Local/FSTLevelDB.h"
#import "Firestore/Source/Local/FSTLocalSerializer.h"
=======
#import "Firestore/Source/Core/FSTQuery.h"
#import "Firestore/Source/Local/FSTLevelDB.h"
#import "Firestore/Source/Local/FSTLocalSerializer.h"
#import "Firestore/Source/Model/FSTDocument.h"
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

#include "Firestore/core/src/firebase/firestore/local/leveldb_key.h"
#include "Firestore/core/src/firebase/firestore/util/status.h"
#include "leveldb/db.h"

<<<<<<< HEAD
=======
using firebase::firestore::model::DocumentKey;
using firebase::firestore::model::DocumentKeySet;
using firebase::firestore::model::DocumentMap;
using firebase::firestore::model::MaybeDocumentMap;
using leveldb::Status;

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
using model::MaybeDocument;
using model::MaybeDocumentMap;
using model::OptionalMaybeDocumentMap;
using leveldb::Status;

=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
LevelDbRemoteDocumentCache::LevelDbRemoteDocumentCache(
    FSTLevelDB* db, FSTLocalSerializer* serializer)
    : db_(db), serializer_(serializer) {
}

<<<<<<< HEAD
void LevelDbRemoteDocumentCache::Add(const MaybeDocument& document) {
  std::string ldb_key = LevelDbRemoteDocumentKey::Key(document.key());
  db_.currentTransaction->Put(ldb_key,
                              [serializer_ encodedMaybeDocument:document]);

  db_.indexManager->AddToCollectionParentIndex(document.key().path().PopLast());
=======
void LevelDbRemoteDocumentCache::Add(FSTMaybeDocument* document) {
  std::string ldb_key = LevelDbRemoteDocumentKey::Key(document.key);
  db_.currentTransaction->Put(ldb_key,
                              [serializer_ encodedMaybeDocument:document]);

  db_.indexManager->AddToCollectionParentIndex(document.key.path().PopLast());
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
}

void LevelDbRemoteDocumentCache::Remove(const DocumentKey& key) {
  std::string ldb_key = LevelDbRemoteDocumentKey::Key(key);
  db_.currentTransaction->Delete(ldb_key);
}

<<<<<<< HEAD
absl::optional<MaybeDocument> LevelDbRemoteDocumentCache::Get(
=======
FSTMaybeDocument* _Nullable LevelDbRemoteDocumentCache::Get(
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    const DocumentKey& key) {
  std::string ldb_key = LevelDbRemoteDocumentKey::Key(key);
  std::string value;
  Status status = db_.currentTransaction->Get(ldb_key, &value);
  if (status.IsNotFound()) {
<<<<<<< HEAD
    return absl::nullopt;
=======
    return nil;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  } else if (status.ok()) {
    return DecodeMaybeDocument(value, key);
  } else {
    HARD_FAIL("Fetch document for key (%s) failed with status: %s",
              key.ToString(), status.ToString());
  }
}

<<<<<<< HEAD
OptionalMaybeDocumentMap LevelDbRemoteDocumentCache::GetAll(
    const DocumentKeySet& keys) {
  OptionalMaybeDocumentMap results;
=======
MaybeDocumentMap LevelDbRemoteDocumentCache::GetAll(
    const DocumentKeySet& keys) {
  MaybeDocumentMap results;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

  LevelDbRemoteDocumentKey currentKey;
  auto it = db_.currentTransaction->NewIterator();

  for (const DocumentKey& key : keys) {
    it->Seek(LevelDbRemoteDocumentKey::Key(key));
    if (!it->Valid() || !currentKey.Decode(it->key()) ||
        currentKey.document_key() != key) {
<<<<<<< HEAD
      results = results.insert(key, absl::nullopt);
=======
      results = results.insert(key, nil);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    } else {
      results = results.insert(key, DecodeMaybeDocument(it->value(), key));
    }
  }

  return results;
}

<<<<<<< HEAD
DocumentMap LevelDbRemoteDocumentCache::GetMatching(const Query& query) {
  HARD_ASSERT(
      !query.IsCollectionGroupQuery(),
=======
DocumentMap LevelDbRemoteDocumentCache::GetMatching(FSTQuery* query) {
  HARD_ASSERT(
      ![query isCollectionGroupQuery],
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
      "CollectionGroup queries should be handled in LocalDocumentsView");

  DocumentMap results;

  // Use the query path as a prefix for testing if a document matches the query.
<<<<<<< HEAD
  const model::ResourcePath& query_path = query.path();
=======
  const model::ResourcePath& query_path = query.path;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  size_t immediate_children_path_length = query_path.size() + 1;

  // Documents are ordered by key, so we can use a prefix scan to narrow down
  // the documents we need to match the query against.
  std::string start_key = LevelDbRemoteDocumentKey::KeyPrefix(query_path);
  auto it = db_.currentTransaction->NewIterator();
  it->Seek(start_key);

  LevelDbRemoteDocumentKey current_key;
  for (; it->Valid() && current_key.Decode(it->key()); it->Next()) {
    // The query is actually returning any path that starts with the query path
    // prefix which may include documents in subcollections. For example, a
    // query on 'rooms' will return rooms/abc/messages/xyx but we shouldn't
    // match it. Fix this by discarding rows with document keys more than one
    // segment longer than the query path.
    const DocumentKey& document_key = current_key.document_key();
    if (document_key.path().size() != immediate_children_path_length) {
      continue;
    }

<<<<<<< HEAD
    MaybeDocument maybe_doc = DecodeMaybeDocument(it->value(), document_key);
    if (!query_path.IsPrefixOf(maybe_doc.key().path())) {
      break;
    } else if (maybe_doc.is_document()) {
      results = results.insert(maybe_doc.key(), Document(maybe_doc));
=======
    FSTMaybeDocument* maybe_doc =
        DecodeMaybeDocument(it->value(), document_key);
    if (!query_path.IsPrefixOf(maybe_doc.key.path())) {
      break;
    } else if ([maybe_doc isKindOfClass:[FSTDocument class]]) {
      results =
          results.insert(maybe_doc.key, static_cast<FSTDocument*>(maybe_doc));
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    }
  }

  return results;
}

<<<<<<< HEAD
MaybeDocument LevelDbRemoteDocumentCache::DecodeMaybeDocument(
=======
FSTMaybeDocument* LevelDbRemoteDocumentCache::DecodeMaybeDocument(
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    absl::string_view encoded, const DocumentKey& key) {
  NSData* data = [[NSData alloc] initWithBytesNoCopy:(void*)encoded.data()
                                              length:encoded.size()
                                        freeWhenDone:false];

  NSError* error;
  FSTPBMaybeDocument* proto = [FSTPBMaybeDocument parseFromData:data
                                                          error:&error];
  if (!proto) {
    HARD_FAIL("FSTPBMaybeDocument failed to parse: %s", error);
  }

<<<<<<< HEAD
  MaybeDocument maybeDocument = [serializer_ decodedMaybeDocument:proto];
  HARD_ASSERT(maybeDocument.key() == key,
              "Read document has key (%s) instead of expected key (%s).",
              maybeDocument.key().ToString(), key.ToString());
=======
  FSTMaybeDocument* maybeDocument = [serializer_ decodedMaybeDocument:proto];
  HARD_ASSERT(maybeDocument.key == key,
              "Read document has key (%s) instead of expected key (%s).",
              maybeDocument.key.ToString(), key.ToString());
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  return maybeDocument;
}

}  // namespace local
}  // namespace firestore
}  // namespace firebase
