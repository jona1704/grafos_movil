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

#ifndef FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_CORE_VIEW_SNAPSHOT_H_
#define FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_CORE_VIEW_SNAPSHOT_H_

#include <functional>
#include <iosfwd>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "Firestore/core/src/firebase/firestore/core/event_listener.h"
<<<<<<< HEAD
<<<<<<< HEAD
#include "Firestore/core/src/firebase/firestore/core/query.h"
#include "Firestore/core/src/firebase/firestore/immutable/sorted_map.h"
#include "Firestore/core/src/firebase/firestore/model/document.h"
#include "Firestore/core/src/firebase/firestore/model/document_key.h"
#include "Firestore/core/src/firebase/firestore/model/document_key_set.h"
#include "Firestore/core/src/firebase/firestore/model/document_set.h"
#include "Firestore/core/src/firebase/firestore/util/statusor.h"

=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#include "Firestore/core/src/firebase/firestore/immutable/sorted_map.h"
#include "Firestore/core/src/firebase/firestore/model/document_key.h"
#include "Firestore/core/src/firebase/firestore/model/document_key_set.h"
#include "Firestore/core/src/firebase/firestore/model/document_set.h"
#include "Firestore/core/src/firebase/firestore/objc/objc_class.h"
#include "Firestore/core/src/firebase/firestore/util/statusor.h"

OBJC_CLASS(FSTDocument);
OBJC_CLASS(FSTQuery);

NS_ASSUME_NONNULL_BEGIN

<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
namespace firebase {
namespace firestore {
namespace core {

/** A change to a single document's state within a view. */
class DocumentViewChange {
 public:
  /**
   * The types of changes that can happen to a document with respect to a view.
   * NOTE: We sort document changes by their type, so the ordering of this enum
   * is significant.
   */
<<<<<<< HEAD
<<<<<<< HEAD
  enum class Type { Removed = 0, Added, Modified, Metadata };

  DocumentViewChange() = default;

  DocumentViewChange(model::Document document, Type type);

  const model::Document& document() const;
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  enum class Type { kRemoved = 0, kAdded, kModified, kMetadata };

  DocumentViewChange() = default;

  DocumentViewChange(FSTDocument* document, Type type);

  FSTDocument* document() const;
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  DocumentViewChange::Type type() const {
    return type_;
  }

  std::string ToString() const;
  size_t Hash() const;

 private:
<<<<<<< HEAD
<<<<<<< HEAD
  model::Document document_;
=======
  objc::Handle<FSTDocument> document_;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  objc::Handle<FSTDocument> document_;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  Type type_{};
};

bool operator==(const DocumentViewChange& lhs, const DocumentViewChange& rhs);

/**
 * The possible states a document can be in w.r.t syncing from local storage to
 * the backend.
 */
enum class SyncState { None = 0, Local, Synced };

/**
 * A set of changes to docs in a query, merging duplicate events for the same
 * doc.
 */
class DocumentViewChangeSet {
 public:
  /** Takes a new change and applies it to the set. */
  void AddChange(DocumentViewChange&& change);

  /** Returns the set of all changes tracked in this set. */
  std::vector<DocumentViewChange> GetChanges() const;

  std::string ToString() const;

 private:
  /** The set of all changes tracked so far, with redundant changes merged. */
  immutable::SortedMap<model::DocumentKey, DocumentViewChange> change_map_;
};

/**
 * A view snapshot is an immutable capture of the results of a query and the
 * changes to them.
 */
class ViewSnapshot {
 public:
  using Listener = std::unique_ptr<EventListener<ViewSnapshot>>;
  using SharedListener = std::shared_ptr<EventListener<ViewSnapshot>>;

<<<<<<< HEAD
<<<<<<< HEAD
  ViewSnapshot(Query query,
=======
  ViewSnapshot(FSTQuery* query,
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  ViewSnapshot(FSTQuery* query,
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
               model::DocumentSet documents,
               model::DocumentSet old_documents,
               std::vector<DocumentViewChange> document_changes,
               model::DocumentKeySet mutated_keys,
               bool from_cache,
               bool sync_state_changed,
               bool excludes_metadata_changes);

  /**
   * Returns a view snapshot as if all documents in the snapshot were
   * added.
   */
<<<<<<< HEAD
<<<<<<< HEAD
  static ViewSnapshot FromInitialDocuments(Query query,
=======
  static ViewSnapshot FromInitialDocuments(FSTQuery* query,
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  static ViewSnapshot FromInitialDocuments(FSTQuery* query,
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
                                           model::DocumentSet documents,
                                           model::DocumentKeySet mutated_keys,
                                           bool from_cache,
                                           bool excludes_metadata_changes);

  /** The query this view is tracking the results for. */
<<<<<<< HEAD
<<<<<<< HEAD
  const Query& query() const;
=======
  FSTQuery* query() const;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  FSTQuery* query() const;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

  /** The documents currently known to be results of the query. */
  const model::DocumentSet& documents() const {
    return documents_;
  }

  /** The documents of the last snapshot. */
  const model::DocumentSet& old_documents() const {
    return old_documents_;
  }

  /** The set of changes that have been applied to the documents. */
  const std::vector<DocumentViewChange>& document_changes() const {
    return document_changes_;
  }

  /** Whether any document in the snapshot was served from the local cache. */
  bool from_cache() const {
    return from_cache_;
  }

  /** Whether any document in the snapshot has pending local writes. */
  bool has_pending_writes() const {
    return !mutated_keys_.empty();
  }

  /** Whether the sync state changed as part of this snapshot. */
  bool sync_state_changed() const {
    return sync_state_changed_;
  }

  /** Whether this snapshot has been filtered to not include metadata changes */
  bool excludes_metadata_changes() const {
    return excludes_metadata_changes_;
  }

  /** The document in this snapshot that have unconfirmed writes. */
  model::DocumentKeySet mutated_keys() const {
    return mutated_keys_;
  }

  std::string ToString() const;
  friend std::ostream& operator<<(std::ostream& out, const ViewSnapshot& value);
  size_t Hash() const;

 private:
<<<<<<< HEAD
<<<<<<< HEAD
  Query query_;
=======
  objc::Handle<FSTQuery> query_;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  objc::Handle<FSTQuery> query_;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

  model::DocumentSet documents_;
  model::DocumentSet old_documents_;
  std::vector<DocumentViewChange> document_changes_;
  model::DocumentKeySet mutated_keys_;

  bool from_cache_ = false;
  bool sync_state_changed_ = false;
  bool excludes_metadata_changes_ = false;
};

bool operator==(const ViewSnapshot& lhs, const ViewSnapshot& rhs);

}  // namespace core
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
#endif  // FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_CORE_VIEW_SNAPSHOT_H_
