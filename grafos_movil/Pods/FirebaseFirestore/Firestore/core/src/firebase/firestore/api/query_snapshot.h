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

#ifndef FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_API_QUERY_SNAPSHOT_H_
#define FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_API_QUERY_SNAPSHOT_H_

#include <functional>
#include <memory>
#include <utility>

#include "Firestore/core/src/firebase/firestore/api/document_change.h"
#include "Firestore/core/src/firebase/firestore/api/document_snapshot.h"
#include "Firestore/core/src/firebase/firestore/api/snapshot_metadata.h"
#include "Firestore/core/src/firebase/firestore/core/event_listener.h"
<<<<<<< HEAD
<<<<<<< HEAD
#include "Firestore/core/src/firebase/firestore/core/query.h"
#include "Firestore/core/src/firebase/firestore/core/view_snapshot.h"
#include "Firestore/core/src/firebase/firestore/model/document_set.h"
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#include "Firestore/core/src/firebase/firestore/core/view_snapshot.h"
#include "Firestore/core/src/firebase/firestore/model/document_set.h"
#include "Firestore/core/src/firebase/firestore/objc/objc_class.h"

NS_ASSUME_NONNULL_BEGIN

OBJC_CLASS(FSTQuery);
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

namespace firebase {
namespace firestore {
namespace api {

class Query;

/**
 * A `QuerySnapshot` contains zero or more `DocumentSnapshot` objects.
 */
class QuerySnapshot {
 public:
  using Listener = std::unique_ptr<core::EventListener<QuerySnapshot>>;

  QuerySnapshot(std::shared_ptr<Firestore> firestore,
<<<<<<< HEAD
<<<<<<< HEAD
                core::Query query,
=======
                FSTQuery* query,
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
                FSTQuery* query,
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
                core::ViewSnapshot&& snapshot,
                SnapshotMetadata metadata);

  size_t Hash() const;

  /**
   * Indicates whether this `QuerySnapshot` is empty (contains no documents).
   */
  bool empty() const {
    return snapshot_.documents().empty();
  }

  /** The count of documents in this `QuerySnapshot`. */
  size_t size() const {
    return snapshot_.documents().size();
  }

  const std::shared_ptr<Firestore>& firestore() const {
    return firestore_;
  }

  Query query() const;

<<<<<<< HEAD
<<<<<<< HEAD
  const core::Query& internal_query() const;
=======
  FSTQuery* internal_query() const;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  FSTQuery* internal_query() const;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

  /**
   * Metadata about this snapshot, concerning its source and if it has local
   * modifications.
   */
  const SnapshotMetadata& metadata() const {
    return metadata_;
  }

  /** Iterates over the `DocumentSnapshots` that make up this query snapshot. */
  void ForEachDocument(
      const std::function<void(DocumentSnapshot)>& callback) const;

  /**
   * Iterates over the `DocumentChanges` representing the changes between
   * the prior snapshot and this one.
   */
  void ForEachChange(bool include_metadata_changes,
                     const std::function<void(DocumentChange)>& callback) const;

  friend bool operator==(const QuerySnapshot& lhs, const QuerySnapshot& rhs);

 private:
  std::shared_ptr<Firestore> firestore_;
<<<<<<< HEAD
<<<<<<< HEAD
  core::Query internal_query_;
=======
  objc::Handle<FSTQuery> internal_query_;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  objc::Handle<FSTQuery> internal_query_;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  core::ViewSnapshot snapshot_;
  SnapshotMetadata metadata_;
};

}  // namespace api
}  // namespace firestore
}  // namespace firebase

<<<<<<< HEAD
<<<<<<< HEAD
=======
NS_ASSUME_NONNULL_END

>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
NS_ASSUME_NONNULL_END

>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#endif  // FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_API_QUERY_SNAPSHOT_H_
