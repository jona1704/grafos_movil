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

#ifndef FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_API_WRITE_BATCH_H_
#define FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_API_WRITE_BATCH_H_

#include <memory>
#include <utility>
#include <vector>

#include "Firestore/core/src/firebase/firestore/api/document_reference.h"
<<<<<<< HEAD
<<<<<<< HEAD
#include "Firestore/core/src/firebase/firestore/model/mutation.h"
#include "Firestore/core/src/firebase/firestore/util/status.h"

=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#include "Firestore/core/src/firebase/firestore/objc/objc_class.h"
#include "Firestore/core/src/firebase/firestore/util/status.h"

NS_ASSUME_NONNULL_BEGIN

OBJC_CLASS(FSTMutation);

<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
namespace firebase {
namespace firestore {
namespace core {

class ParsedSetData;
class ParsedUpdateData;

}  // namespace core

namespace api {

class Firestore;

class WriteBatch {
 public:
  explicit WriteBatch(std::shared_ptr<Firestore> firestore)
      : firestore_{std::move(firestore)} {
  }

  void SetData(const DocumentReference& reference,
               core::ParsedSetData&& setData);
  void UpdateData(const DocumentReference& reference,
                  core::ParsedUpdateData&& updateData);
  void DeleteData(const DocumentReference& reference);

  void Commit(util::StatusCallback callback);

  const std::shared_ptr<Firestore>& firestore() const {
    return firestore_;
  }

 private:
  std::shared_ptr<Firestore> firestore_;
<<<<<<< HEAD
<<<<<<< HEAD
  std::vector<model::Mutation> mutations_;
=======
  std::vector<FSTMutation*> mutations_;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  std::vector<FSTMutation*> mutations_;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  bool committed_ = false;

  void VerifyNotCommitted() const;
  void ValidateReference(const DocumentReference& reference) const;
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
#endif  // FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_API_WRITE_BATCH_H_
