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

#ifndef FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_MODEL_UNKNOWN_DOCUMENT_H_
#define FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_MODEL_UNKNOWN_DOCUMENT_H_

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

/**
 * A class representing an existing document whose data is unknown (e.g. a
 * document that was updated without a known base document).
 */
class UnknownDocument : public MaybeDocument {
 public:
  UnknownDocument(DocumentKey key, SnapshotVersion version);

<<<<<<< HEAD
<<<<<<< HEAD
  /**
   * Casts a MaybeDocument to a UnknownDocument. This is a checked operation
   * that will assert if the type of the MaybeDocument isn't actually
   * Type::UnknownDocument.
   */
  explicit UnknownDocument(const MaybeDocument& document);

  /** Creates an invalid UnknownDocument. */
  UnknownDocument() = default;

 private:
  class Rep;
=======
  bool HasPendingWrites() const override {
    return true;
  }
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  bool HasPendingWrites() const override {
    return true;
  }
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
};

}  // namespace model
}  // namespace firestore
}  // namespace firebase

#endif  // FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_MODEL_UNKNOWN_DOCUMENT_H_
