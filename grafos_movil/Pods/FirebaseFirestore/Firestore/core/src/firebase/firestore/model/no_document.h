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

#ifndef FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_MODEL_NO_DOCUMENT_H_
#define FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_MODEL_NO_DOCUMENT_H_

<<<<<<< HEAD
<<<<<<< HEAD
#include <memory>

=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#include "Firestore/core/src/firebase/firestore/model/maybe_document.h"

namespace firebase {
namespace firestore {
namespace model {

/** Represents that no documents exists for the key at the given version. */
class NoDocument : public MaybeDocument {
 public:
  NoDocument(DocumentKey key,
             SnapshotVersion version,
             bool has_committed_mutations);

<<<<<<< HEAD
<<<<<<< HEAD
  /**
   * Casts a MaybeDocument to a NoDocument. This is a checked operation that
   * will assert if the type of the MaybeDocument isn't actually
   * Type::NoDocument.
   */
  explicit NoDocument(const MaybeDocument& document);

  /** Creates an invalid NoDocument instance. */
  NoDocument() = default;

  bool has_committed_mutations() const;

 private:
  class Rep;

  const Rep& doc_rep() const;
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  bool HasPendingWrites() const override {
    return has_committed_mutations_;
  }

 private:
  bool has_committed_mutations_;
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
};

}  // namespace model
}  // namespace firestore
}  // namespace firebase

#endif  // FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_MODEL_NO_DOCUMENT_H_
