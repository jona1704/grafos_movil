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

#ifndef FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_API_FIRESTORE_H_
#define FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_API_FIRESTORE_H_

#include <dispatch/dispatch.h>

#include <memory>
#include <mutex>  // NOLINT(build/c++11)
#include <string>
#include <utility>

#include "Firestore/core/src/firebase/firestore/api/settings.h"
#include "Firestore/core/src/firebase/firestore/auth/credentials_provider.h"
#include "Firestore/core/src/firebase/firestore/core/database_info.h"
#include "Firestore/core/src/firebase/firestore/core/transaction.h"
#include "Firestore/core/src/firebase/firestore/model/database_id.h"
#include "Firestore/core/src/firebase/firestore/objc/objc_class.h"
#include "Firestore/core/src/firebase/firestore/util/async_queue.h"
<<<<<<< HEAD
<<<<<<< HEAD
#include "Firestore/core/src/firebase/firestore/util/nullability.h"
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#include "Firestore/core/src/firebase/firestore/util/status.h"
#include "Firestore/core/src/firebase/firestore/util/statusor_callback.h"
#include "absl/types/any.h"

NS_ASSUME_NONNULL_BEGIN

OBJC_CLASS(FIRQuery);
OBJC_CLASS(FIRTransaction);
<<<<<<< HEAD
<<<<<<< HEAD
=======
OBJC_CLASS(FSTFirestoreClient);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
OBJC_CLASS(FSTFirestoreClient);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
OBJC_CLASS(NSString);

namespace firebase {
namespace firestore {
<<<<<<< HEAD
<<<<<<< HEAD
namespace core {
class FirestoreClient;
}
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
namespace api {

class CollectionReference;
class DocumentReference;
class WriteBatch;

class Firestore : public std::enable_shared_from_this<Firestore> {
 public:
  Firestore() = default;

  Firestore(model::DatabaseId database_id,
            std::string persistence_key,
<<<<<<< HEAD
<<<<<<< HEAD
            std::shared_ptr<auth::CredentialsProvider> credentials_provider,
=======
            std::unique_ptr<auth::CredentialsProvider> credentials_provider,
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
            std::unique_ptr<auth::CredentialsProvider> credentials_provider,
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
            std::shared_ptr<util::AsyncQueue> worker_queue,
            void* extension);

  const model::DatabaseId& database_id() const {
    return database_id_;
  }

  const std::string& persistence_key() const {
    return persistence_key_;
  }

<<<<<<< HEAD
<<<<<<< HEAD
  const std::shared_ptr<core::FirestoreClient>& client();
=======
  FSTFirestoreClient* client();
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  FSTFirestoreClient* client();
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

  const std::shared_ptr<util::AsyncQueue>& worker_queue();

  void* extension() {
    return extension_;
  }

  const Settings& settings() const;
  void set_settings(const Settings& settings);

  void set_user_executor(std::unique_ptr<util::Executor> user_executor);

  CollectionReference GetCollection(absl::string_view collection_path);
  DocumentReference GetDocument(absl::string_view document_path);
  WriteBatch GetBatch();
  FIRQuery* GetCollectionGroup(std::string collection_id);

  void RunTransaction(core::TransactionUpdateCallback update_callback,
                      core::TransactionResultCallback result_callback);

<<<<<<< HEAD
<<<<<<< HEAD
  void Terminate(util::StatusCallback callback);
  void ClearPersistence(util::StatusCallback callback);
  void WaitForPendingWrites(util::StatusCallback callback);
=======
  void Shutdown(util::StatusCallback callback);
  void ClearPersistence(util::StatusCallback callback);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  void Shutdown(util::StatusCallback callback);
  void ClearPersistence(util::StatusCallback callback);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

  void EnableNetwork(util::StatusCallback callback);
  void DisableNetwork(util::StatusCallback callback);

 private:
  void EnsureClientConfigured();
  core::DatabaseInfo MakeDatabaseInfo() const;

  model::DatabaseId database_id_;
<<<<<<< HEAD
<<<<<<< HEAD
  std::shared_ptr<auth::CredentialsProvider> credentials_provider_;
  std::string persistence_key_;
  std::shared_ptr<core::FirestoreClient> client_;
=======
  std::unique_ptr<auth::CredentialsProvider> credentials_provider_;
  std::string persistence_key_;
  objc::Handle<FSTFirestoreClient> client_;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  std::unique_ptr<auth::CredentialsProvider> credentials_provider_;
  std::string persistence_key_;
  objc::Handle<FSTFirestoreClient> client_;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

  std::shared_ptr<util::Executor> user_executor_;
  std::shared_ptr<util::AsyncQueue> worker_queue_;

  void* extension_ = nullptr;

  Settings settings_;

  mutable std::mutex mutex_;
};

}  // namespace api
}  // namespace firestore
}  // namespace firebase

NS_ASSUME_NONNULL_END

#endif  // FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_API_FIRESTORE_H_
