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

#ifndef FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_LOCAL_MEMORY_REMOTE_DOCUMENT_CACHE_H_
#define FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_LOCAL_MEMORY_REMOTE_DOCUMENT_CACHE_H_

#if !defined(__OBJC__)
#error "For now, this file must only be included by ObjC source files."
#endif  // !defined(__OBJC__)

#include <vector>

#include "Firestore/core/src/firebase/firestore/local/remote_document_cache.h"
#include "Firestore/core/src/firebase/firestore/model/document_key.h"
#include "Firestore/core/src/firebase/firestore/model/document_key_set.h"
#include "Firestore/core/src/firebase/firestore/model/document_map.h"
#include "Firestore/core/src/firebase/firestore/model/types.h"

@class FSTLocalSerializer;
<<<<<<< HEAD
<<<<<<< HEAD
@class FSTMemoryLRUReferenceDelegate;
@class FSTMemoryPersistence;
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
@class FSTMaybeDocument;
@class FSTMemoryLRUReferenceDelegate;
@class FSTMemoryPersistence;
@class FSTQuery;
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

NS_ASSUME_NONNULL_BEGIN

namespace firebase {
namespace firestore {
namespace local {

<<<<<<< HEAD
<<<<<<< HEAD
class Sizer;

=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
class MemoryRemoteDocumentCache : public RemoteDocumentCache {
 public:
  explicit MemoryRemoteDocumentCache(FSTMemoryPersistence* persistence);

<<<<<<< HEAD
<<<<<<< HEAD
  void Add(const model::MaybeDocument& document) override;
  void Remove(const model::DocumentKey& key) override;

  absl::optional<model::MaybeDocument> Get(
      const model::DocumentKey& key) override;
  model::OptionalMaybeDocumentMap GetAll(
      const model::DocumentKeySet& keys) override;
  model::DocumentMap GetMatching(const core::Query& query) override;
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  void Add(FSTMaybeDocument* document) override;
  void Remove(const model::DocumentKey& key) override;

  FSTMaybeDocument* _Nullable Get(const model::DocumentKey& key) override;
  model::MaybeDocumentMap GetAll(const model::DocumentKeySet& keys) override;
  model::DocumentMap GetMatching(FSTQuery* query) override;
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

  std::vector<model::DocumentKey> RemoveOrphanedDocuments(
      FSTMemoryLRUReferenceDelegate* reference_delegate,
      model::ListenSequenceNumber upper_bound);

<<<<<<< HEAD
<<<<<<< HEAD
  int64_t CalculateByteSize(const Sizer& sizer);
=======
  size_t CalculateByteSize(FSTLocalSerializer* serializer);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  size_t CalculateByteSize(FSTLocalSerializer* serializer);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

 private:
  /** Underlying cache of documents. */
  model::MaybeDocumentMap docs_;

  // This instance is owned by FSTMemoryPersistence; avoid a retain cycle.
  __weak FSTMemoryPersistence* persistence_;
};

}  // namespace local
}  // namespace firestore
}  // namespace firebase

NS_ASSUME_NONNULL_END

#endif  // FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_LOCAL_MEMORY_REMOTE_DOCUMENT_CACHE_H_
