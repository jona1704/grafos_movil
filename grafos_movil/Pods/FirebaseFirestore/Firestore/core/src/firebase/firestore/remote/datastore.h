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

#ifndef FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_REMOTE_DATASTORE_H_
#define FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_REMOTE_DATASTORE_H_

#if !defined(__OBJC__)
#error "This header only supports Objective-C++"
#endif  // !defined(__OBJC__)

<<<<<<< HEAD
<<<<<<< HEAD
=======
#import <Foundation/Foundation.h>

>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
#import <Foundation/Foundation.h>

>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "Firestore/core/src/firebase/firestore/auth/credentials_provider.h"
#include "Firestore/core/src/firebase/firestore/auth/token.h"
#include "Firestore/core/src/firebase/firestore/core/database_info.h"
#include "Firestore/core/src/firebase/firestore/model/document_key.h"
#include "Firestore/core/src/firebase/firestore/remote/grpc_call.h"
#include "Firestore/core/src/firebase/firestore/remote/grpc_connection.h"
#include "Firestore/core/src/firebase/firestore/remote/remote_objc_bridge.h"
#include "Firestore/core/src/firebase/firestore/remote/watch_stream.h"
#include "Firestore/core/src/firebase/firestore/remote/write_stream.h"
#include "Firestore/core/src/firebase/firestore/util/async_queue.h"
#include "Firestore/core/src/firebase/firestore/util/executor.h"
#include "Firestore/core/src/firebase/firestore/util/status.h"
#include "Firestore/core/src/firebase/firestore/util/statusor.h"
#include "absl/strings/string_view.h"
#include "grpcpp/completion_queue.h"
#include "grpcpp/support/status.h"

<<<<<<< HEAD
<<<<<<< HEAD
=======
#import "Firestore/Source/Core/FSTTypes.h"

>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
#import "Firestore/Source/Core/FSTTypes.h"

>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
namespace firebase {
namespace firestore {
namespace remote {

/**
 * `Datastore` represents a proxy for the remote server, hiding details of the
 * RPC layer. It:
 *
 *   - Manages connections to the server
 *   - Authenticates to the server
 *   - Manages threading and keeps higher-level code running on the worker queue
 *   - Serializes internal model objects to and from protocol buffers
 *
 * `Datastore` is generally not responsible for understanding the higher-level
 * protocol involved in actually making changes or reading data, and aside from
 * the connections it manages is otherwise stateless.
 *
 * This class is only intended to be inherited from by test mocks.
 */
class Datastore : public std::enable_shared_from_this<Datastore> {
 public:
<<<<<<< HEAD
<<<<<<< HEAD
  // TODO(varconst): change this to take a single `StatusOr` parameter.
  using LookupCallback = std::function<void(
      const std::vector<model::MaybeDocument>&, const util::Status&)>;
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  // TODO(varconst): once `FSTMaybeDocument` is replaced with a C++ equivalent,
  // this function could take a single `StatusOr` parameter.
  using LookupCallback = std::function<void(
      const std::vector<FSTMaybeDocument*>&, const util::Status&)>;
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  using CommitCallback = std::function<void(const util::Status&)>;

  Datastore(const core::DatabaseInfo& database_info,
            const std::shared_ptr<util::AsyncQueue>& worker_queue,
<<<<<<< HEAD
<<<<<<< HEAD
            std::shared_ptr<auth::CredentialsProvider> credentials);
=======
            auth::CredentialsProvider* credentials);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
            auth::CredentialsProvider* credentials);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

  virtual ~Datastore() {
  }

  /** Starts polling the gRPC completion queue. */
  void Start();
  /** Cancels any pending gRPC calls and drains the gRPC completion queue. */
  void Shutdown();

  /**
   * Creates a new `WatchStream` that is still unstarted but uses a common
   * shared channel.
   */
  virtual std::shared_ptr<WatchStream> CreateWatchStream(
      WatchStreamCallback* callback);
  /**
   * Creates a new `WriteStream` that is still unstarted but uses a common
   * shared channel.
   */
  virtual std::shared_ptr<WriteStream> CreateWriteStream(
      WriteStreamCallback* callback);

<<<<<<< HEAD
<<<<<<< HEAD
  void CommitMutations(const std::vector<model::Mutation>& mutations,
=======
  void CommitMutations(const std::vector<FSTMutation*>& mutations,
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  void CommitMutations(const std::vector<FSTMutation*>& mutations,
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
                       CommitCallback&& callback);
  void LookupDocuments(const std::vector<model::DocumentKey>& keys,
                       LookupCallback&& callback);

  /** Returns true if the given error is a gRPC ABORTED error. */
  static bool IsAbortedError(const util::Status& status);

  /**
   * Determines whether an error code represents a permanent error when received
   * in response to a non-write operation.
   *
   * See `IsPermanentWriteError` for classifying write errors.
   */
  static bool IsPermanentError(const util::Status& status);

  /**
   * Determines whether an error code represents a permanent error when received
   * in response to a write operation.
   *
   * Write operations must be handled specially because as of b/119437764,
   * ABORTED errors on the write stream should be retried too (even though
   * ABORTED errors are not generally retryable).
   *
   * Note that during the initial handshake on the write stream an ABORTED error
   * signals that we should discard our stream token (i.e. it is permanent).
   * This means a handshake error should be classified with `IsPermanentError`,
   * above.
   */
  static bool IsPermanentWriteError(const util::Status& status);

  static std::string GetWhitelistedHeadersAsString(
      const GrpcCall::Metadata& headers);

  Datastore(const Datastore& other) = delete;
  Datastore(Datastore&& other) = delete;
  Datastore& operator=(const Datastore& other) = delete;
  Datastore& operator=(Datastore&& other) = delete;

 protected:
  /** Test-only constructor */
  Datastore(const core::DatabaseInfo& database_info,
            const std::shared_ptr<util::AsyncQueue>& worker_queue,
<<<<<<< HEAD
<<<<<<< HEAD
            std::shared_ptr<auth::CredentialsProvider> credentials,
=======
            auth::CredentialsProvider* credentials,
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
            auth::CredentialsProvider* credentials,
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
            std::unique_ptr<ConnectivityMonitor> connectivity_monitor);

  /** Test-only method */
  grpc::CompletionQueue* grpc_queue() {
    return &grpc_queue_;
  }
  /** Test-only method */
  GrpcCall* LastCall() {
    return !active_calls_.empty() ? active_calls_.back().get() : nullptr;
  }

  /** Test-only getter for mocking */
  GrpcConnection* grpc_connection() {
    return &grpc_connection_;
  }

 private:
  void PollGrpcQueue();

  void CommitMutationsWithCredentials(
      const auth::Token& token,
<<<<<<< HEAD
<<<<<<< HEAD
      const std::vector<model::Mutation>& mutations,
=======
      const std::vector<FSTMutation*>& mutations,
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
      const std::vector<FSTMutation*>& mutations,
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
      CommitCallback&& callback);

  void LookupDocumentsWithCredentials(
      const auth::Token& token,
      const std::vector<model::DocumentKey>& keys,
      LookupCallback&& callback);
  void OnLookupDocumentsResponse(
      const util::StatusOr<std::vector<grpc::ByteBuffer>>& result,
      const LookupCallback& callback);

  using OnCredentials = std::function<void(const util::StatusOr<auth::Token>&)>;
  void ResumeRpcWithCredentials(const OnCredentials& on_token);

  void HandleCallStatus(const util::Status& status);

  void RemoveGrpcCall(GrpcCall* to_remove);

  static GrpcCall::Metadata ExtractWhitelistedHeaders(
      const GrpcCall::Metadata& headers);

  // In case Auth tries to invoke a callback after `Datastore` has been shut
  // down.
  bool is_shut_down_ = false;

  std::shared_ptr<util::AsyncQueue> worker_queue_;
<<<<<<< HEAD
<<<<<<< HEAD
  std::shared_ptr<auth::CredentialsProvider> credentials_;
=======
  auth::CredentialsProvider* credentials_ = nullptr;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  auth::CredentialsProvider* credentials_ = nullptr;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

  // A separate executor dedicated to polling gRPC completion queue (which is
  // shared for all spawned gRPC streams and calls).
  std::unique_ptr<util::Executor> rpc_executor_;
  grpc::CompletionQueue grpc_queue_;
  // TODO(varconst): move `ConnectivityMonitor` to `FSTFirestoreClient`.
  std::unique_ptr<ConnectivityMonitor> connectivity_monitor_;
  GrpcConnection grpc_connection_;

  std::vector<std::unique_ptr<GrpcCall>> active_calls_;
  bridge::DatastoreSerializer serializer_bridge_;
};

}  // namespace remote
}  // namespace firestore
}  // namespace firebase

#endif  // FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_REMOTE_DATASTORE_H_
