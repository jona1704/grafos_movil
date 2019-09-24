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

#include "Firestore/core/src/firebase/firestore/api/firestore.h"

#import "Firestore/Source/API/FIRCollectionReference+Internal.h"
#import "Firestore/Source/API/FIRDocumentReference+Internal.h"
#import "Firestore/Source/API/FIRFirestore+Internal.h"
#import "Firestore/Source/API/FIRQuery+Internal.h"
#import "Firestore/Source/API/FIRTransaction+Internal.h"
<<<<<<< HEAD
<<<<<<< HEAD
=======
#import "Firestore/Source/Core/FSTFirestoreClient.h"
#import "Firestore/Source/Core/FSTQuery.h"
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
#import "Firestore/Source/Core/FSTFirestoreClient.h"
#import "Firestore/Source/Core/FSTQuery.h"
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#import "Firestore/Source/Local/FSTLevelDB.h"

#include "Firestore/core/src/firebase/firestore/api/collection_reference.h"
#include "Firestore/core/src/firebase/firestore/api/document_reference.h"
#include "Firestore/core/src/firebase/firestore/api/settings.h"
#include "Firestore/core/src/firebase/firestore/api/write_batch.h"
#include "Firestore/core/src/firebase/firestore/auth/firebase_credentials_provider_apple.h"
<<<<<<< HEAD
<<<<<<< HEAD
#include "Firestore/core/src/firebase/firestore/core/firestore_client.h"
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#include "Firestore/core/src/firebase/firestore/core/transaction.h"
#include "Firestore/core/src/firebase/firestore/model/document_key.h"
#include "Firestore/core/src/firebase/firestore/model/resource_path.h"
#include "Firestore/core/src/firebase/firestore/util/async_queue.h"
#include "Firestore/core/src/firebase/firestore/util/executor_libdispatch.h"
#include "Firestore/core/src/firebase/firestore/util/hard_assert.h"
#include "Firestore/core/src/firebase/firestore/util/status.h"
#include "absl/memory/memory.h"

namespace firebase {
namespace firestore {
namespace api {

using auth::CredentialsProvider;
using core::DatabaseInfo;
<<<<<<< HEAD
<<<<<<< HEAD
using core::FirestoreClient;
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
using core::Transaction;
using model::DocumentKey;
using model::ResourcePath;
using util::AsyncQueue;
using util::Executor;
using util::ExecutorLibdispatch;
using util::Status;

Firestore::Firestore(model::DatabaseId database_id,
                     std::string persistence_key,
<<<<<<< HEAD
<<<<<<< HEAD
                     std::shared_ptr<CredentialsProvider> credentials_provider,
=======
                     std::unique_ptr<CredentialsProvider> credentials_provider,
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
                     std::unique_ptr<CredentialsProvider> credentials_provider,
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
                     std::shared_ptr<AsyncQueue> worker_queue,
                     void* extension)
    : database_id_{std::move(database_id)},
      credentials_provider_{std::move(credentials_provider)},
      persistence_key_{std::move(persistence_key)},
      worker_queue_{std::move(worker_queue)},
      extension_{extension} {
}

<<<<<<< HEAD
<<<<<<< HEAD
const std::shared_ptr<FirestoreClient>& Firestore::client() {
=======
FSTFirestoreClient* Firestore::client() {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
FSTFirestoreClient* Firestore::client() {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  HARD_ASSERT(client_, "Client is not yet configured.");
  return client_;
}

const std::shared_ptr<AsyncQueue>& Firestore::worker_queue() {
  return worker_queue_;
}

const Settings& Firestore::settings() const {
  std::lock_guard<std::mutex> lock{mutex_};
  return settings_;
}

void Firestore::set_settings(const Settings& settings) {
  std::lock_guard<std::mutex> lock{mutex_};
  if (client_) {
    HARD_FAIL(
        "Firestore instance has already been started and its settings can "
        "no longer be changed. You can only set settings before calling any "
        "other methods on a Firestore instance.");
  }
  settings_ = settings;
}

void Firestore::set_user_executor(
    std::unique_ptr<util::Executor> user_executor) {
  std::lock_guard<std::mutex> lock{mutex_};
  HARD_ASSERT(!client_ && user_executor,
              "set_user_executor() must be called with a valid executor, "
              "before the client is initialized.");
  user_executor_ = std::move(user_executor);
}

CollectionReference Firestore::GetCollection(
    absl::string_view collection_path) {
  EnsureClientConfigured();
  ResourcePath path = ResourcePath::FromString(collection_path);
  return CollectionReference{std::move(path), shared_from_this()};
}

DocumentReference Firestore::GetDocument(absl::string_view document_path) {
  EnsureClientConfigured();
  return DocumentReference{ResourcePath::FromString(document_path),
                           shared_from_this()};
}

WriteBatch Firestore::GetBatch() {
  EnsureClientConfigured();
  return WriteBatch(shared_from_this());
}

FIRQuery* Firestore::GetCollectionGroup(std::string collection_id) {
  EnsureClientConfigured();

<<<<<<< HEAD
<<<<<<< HEAD
  core::Query query(ResourcePath::Empty(), std::make_shared<const std::string>(
                                               std::move(collection_id)));
  return [[FIRQuery alloc] initWithQuery:std::move(query)
                               firestore:shared_from_this()];
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  FSTQuery* query = [FSTQuery queryWithPath:ResourcePath::Empty()
                            collectionGroup:std::make_shared<const std::string>(
                                                std::move(collection_id))];
  return [[FIRQuery alloc] initWithQuery:query firestore:shared_from_this()];
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
}

void Firestore::RunTransaction(
    core::TransactionUpdateCallback update_callback,
    core::TransactionResultCallback result_callback) {
  EnsureClientConfigured();

<<<<<<< HEAD
<<<<<<< HEAD
  client_->Transaction(5, std::move(update_callback),
                       std::move(result_callback));
}

void Firestore::Terminate(util::StatusCallback callback) {
  // The client must be initialized to ensure that all subsequent API usage
  // throws an exception.
  EnsureClientConfigured();
  client_->Terminate(std::move(callback));
}

void Firestore::WaitForPendingWrites(util::StatusCallback callback) {
  EnsureClientConfigured();
  client_->WaitForPendingWrites(std::move(callback));
}

void Firestore::ClearPersistence(util::StatusCallback callback) {
  worker_queue()->EnqueueEvenAfterShutdown([this, callback] {
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  [client_ transactionWithRetries:5
                   updateCallback:std::move(update_callback)
                   resultCallback:std::move(result_callback)];
}

void Firestore::Shutdown(util::StatusCallback callback) {
  // The client must be initialized to ensure that all subsequent API usage
  // throws an exception.
  EnsureClientConfigured();
  [client_ shutdownWithCallback:std::move(callback)];
}

void Firestore::ClearPersistence(util::StatusCallback callback) {
  worker_queue()->Enqueue([this, callback] {
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    auto Yield = [=](Status status) {
      if (callback) {
        this->user_executor_->Execute([=] { callback(status); });
      }
    };

    {
      std::lock_guard<std::mutex> lock{mutex_};
<<<<<<< HEAD
<<<<<<< HEAD
      if (client_ && !client()->is_terminated()) {
        Yield(util::Status(
            Error::FailedPrecondition,
=======
      if (client_ && !client().isShutdown) {
        Yield(util::Status(
            FirestoreErrorCode::FailedPrecondition,
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
      if (client_ && !client().isShutdown) {
        Yield(util::Status(
            FirestoreErrorCode::FailedPrecondition,
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
            "Persistence cannot be cleared while the client is running."));
        return;
      }
    }

    Yield([FSTLevelDB clearPersistence:MakeDatabaseInfo()]);
  });
}

void Firestore::EnableNetwork(util::StatusCallback callback) {
  EnsureClientConfigured();
<<<<<<< HEAD
<<<<<<< HEAD
  client_->EnableNetwork(std::move(callback));
=======
  [client_ enableNetworkWithCallback:std::move(callback)];
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  [client_ enableNetworkWithCallback:std::move(callback)];
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
}

void Firestore::DisableNetwork(util::StatusCallback callback) {
  EnsureClientConfigured();
<<<<<<< HEAD
<<<<<<< HEAD
  client_->DisableNetwork(std::move(callback));
=======
  [client_ disableNetworkWithCallback:std::move(callback)];
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  [client_ disableNetworkWithCallback:std::move(callback)];
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
}

void Firestore::EnsureClientConfigured() {
  std::lock_guard<std::mutex> lock{mutex_};

  if (!client_) {
    HARD_ASSERT(worker_queue_, "Expected non-null worker queue");
<<<<<<< HEAD
<<<<<<< HEAD
    client_ = FirestoreClient::Create(MakeDatabaseInfo(), settings_,
                                      std::move(credentials_provider_),
                                      user_executor_, worker_queue_);
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    client_ =
        [FSTFirestoreClient clientWithDatabaseInfo:MakeDatabaseInfo()
                                          settings:settings_
                               credentialsProvider:credentials_provider_.get()
                                      userExecutor:user_executor_
                                       workerQueue:worker_queue_];
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  }
}

DatabaseInfo Firestore::MakeDatabaseInfo() const {
  return DatabaseInfo(database_id_, persistence_key_, settings_.host(),
                      settings_.ssl_enabled());
}

}  // namespace api
}  // namespace firestore
}  // namespace firebase
