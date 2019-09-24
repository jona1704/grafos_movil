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

#ifndef FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_MODEL_DOCUMENT_H_
#define FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_MODEL_DOCUMENT_H_

<<<<<<< HEAD
<<<<<<< HEAD
#include <iosfwd>
#include <memory>
#include <string>
=======
#if __OBJC__
#import "Firestore/Source/Model/FSTDocument.h"
#endif
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
#if __OBJC__
#import "Firestore/Source/Model/FSTDocument.h"
#endif
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

#include "Firestore/core/src/firebase/firestore/model/field_path.h"
#include "Firestore/core/src/firebase/firestore/model/field_value.h"
#include "Firestore/core/src/firebase/firestore/model/maybe_document.h"
<<<<<<< HEAD
<<<<<<< HEAD
#include "absl/types/any.h"
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#include "absl/types/optional.h"

namespace firebase {
namespace firestore {
namespace model {

<<<<<<< HEAD
<<<<<<< HEAD
/** Describes the `has_pending_writes` state of a document. */
=======
/** Describes the `hasPendingWrites` state of a document. */
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
/** Describes the `hasPendingWrites` state of a document. */
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
enum class DocumentState {
  /**
   * Local mutations applied via the mutation queue. Document is potentially
   * inconsistent.
   */
  kLocalMutations,

  /**
   * Mutations applied based on a write acknowledgment. Document is potentially
   * inconsistent.
   */
  kCommittedMutations,

  /** No mutations applied. Document was sent to us by Watch. */
  kSynced,
};

<<<<<<< HEAD
<<<<<<< HEAD
std::ostream& operator<<(std::ostream& os, DocumentState state);

=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
/**
 * Represents a document in Firestore with a key, version, data and whether the
 * data has local mutations applied to it.
 */
class Document : public MaybeDocument {
 public:
<<<<<<< HEAD
<<<<<<< HEAD
  Document(ObjectValue data,
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  /**
   * Construct a document. ObjectValue must be passed by rvalue.
   */
  Document(ObjectValue&& data,
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
           DocumentKey key,
           SnapshotVersion version,
           DocumentState document_state);

<<<<<<< HEAD
<<<<<<< HEAD
  Document(ObjectValue data,
           DocumentKey key,
           SnapshotVersion version,
           DocumentState document_state,
           absl::any proto);

  /**
   * Casts a MaybeDocument to a Document. This is a checked operation that will
   * assert if the type of the MaybeDocument isn't actually Type::Document.
   */
  explicit Document(const MaybeDocument& document);

  /** Creates an invalid Document instance. */
  Document() = default;

  const ObjectValue& data() const;

  absl::optional<FieldValue> field(const FieldPath& path) const;

  DocumentState document_state() const;

  bool has_local_mutations() const;

  bool has_committed_mutations() const;

  const absl::any& proto() const;

  /** Compares against another Document. */
  friend bool operator==(const Document& lhs, const Document& rhs);

  friend std::ostream& operator<<(std::ostream& os, const Document& doc);

 private:
  class Rep;

  const Rep& doc_rep() const;
};

=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#if __OBJC__
  explicit Document(FSTDocument* doc)
      : MaybeDocument(doc.key, doc.version),
        data_(doc.data),
        document_state_(doc.documentState) {
  }

  FSTDocument* ToDocument() const {
    return [FSTDocument documentWithData:data_
                                     key:key()
                                 version:version()
                                   state:document_state_];
  }
#endif  // __OBJC__

  const ObjectValue& data() const {
    return data_;
  }

  absl::optional<FieldValue> field(const FieldPath& path) const {
    return data_.Get(path);
  }

  bool HasLocalMutations() const {
    return document_state_ == DocumentState::kLocalMutations;
  }

  bool HasCommittedMutations() const {
    return document_state_ == DocumentState::kCommittedMutations;
  }

  bool HasPendingWrites() const override {
    return HasLocalMutations() || HasCommittedMutations();
  }

 protected:
  bool Equals(const MaybeDocument& other) const override;

 private:
  ObjectValue data_;
  DocumentState document_state_;
};

/** Compares against another Document. */
inline bool operator==(const Document& lhs, const Document& rhs) {
  return lhs.version() == rhs.version() && lhs.key() == rhs.key() &&
         lhs.HasLocalMutations() == rhs.HasLocalMutations() &&
         lhs.data() == rhs.data();
}

<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
inline bool operator!=(const Document& lhs, const Document& rhs) {
  return !(lhs == rhs);
}

}  // namespace model
}  // namespace firestore
}  // namespace firebase

#endif  // FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_MODEL_DOCUMENT_H_
