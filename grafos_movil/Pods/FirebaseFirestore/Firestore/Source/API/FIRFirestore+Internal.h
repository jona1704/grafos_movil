/*
 * Copyright 2017 Google
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

#import "FIRFirestore.h"

#include <memory>
#include <string>

#include "Firestore/core/src/firebase/firestore/api/firestore.h"
#include "Firestore/core/src/firebase/firestore/auth/credentials_provider.h"
#include "Firestore/core/src/firebase/firestore/util/async_queue.h"

@class FIRApp;
@class FSTFirestoreClient;
@class FSTUserDataConverter;

namespace api = firebase::firestore::api;
namespace auth = firebase::firestore::auth;
namespace model = firebase::firestore::model;
namespace util = firebase::firestore::util;

NS_ASSUME_NONNULL_BEGIN

<<<<<<< HEAD
/** Provides a registry management interface for FIRFirestore instances. */
@protocol FSTFirestoreInstanceRegistry

/** Removes the FIRFirestore instance with given database name from registry. */
- (void)removeInstanceWithDatabase:(NSString *)database;

@end

=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
@interface FIRFirestore (/* Init */)

/**
 * Initializes a Firestore object with all the required parameters directly. This exists so that
 * tests can create FIRFirestore objects without needing FIRApp.
 */
- (instancetype)initWithDatabaseID:(model::DatabaseId)databaseID
                    persistenceKey:(std::string)persistenceKey
<<<<<<< HEAD
               credentialsProvider:(std::shared_ptr<auth::CredentialsProvider>)credentialsProvider
                       workerQueue:(std::shared_ptr<util::AsyncQueue>)workerQueue
                       firebaseApp:(FIRApp *)app
                  instanceRegistry:(nullable id<FSTFirestoreInstanceRegistry>)registry;
=======
               credentialsProvider:(std::unique_ptr<auth::CredentialsProvider>)credentialsProvider
                       workerQueue:(std::shared_ptr<util::AsyncQueue>)workerQueue
                       firebaseApp:(FIRApp *)app;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
@end

/** Internal FIRFirestore API we don't want exposed in our public header files. */
@interface FIRFirestore (Internal)

/** Checks to see if logging is is globally enabled for the Firestore client. */
+ (BOOL)isLoggingEnabled;

+ (FIRFirestore *)recoverFromFirestore:(std::shared_ptr<api::Firestore>)firestore;

<<<<<<< HEAD
- (void)terminateInternalWithCompletion:(nullable void (^)(NSError *_Nullable error))completion;
=======
/**
 * Shutdown this `FIRFirestore`, releasing all resources (abandoning any outstanding writes,
 * removing all listens, closing all network connections, etc.).
 *
 * @param completion A block to execute once everything has shut down.
 */
- (void)shutdownWithCompletion:(nullable void (^)(NSError *_Nullable error))completion
    NS_SWIFT_NAME(shutdown(completion:));
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

- (const std::shared_ptr<util::AsyncQueue> &)workerQueue;

@property(nonatomic, assign, readonly) std::shared_ptr<api::Firestore> wrapped;

@property(nonatomic, assign, readonly) const model::DatabaseId &databaseID;
@property(nonatomic, strong, readonly) FSTUserDataConverter *dataConverter;

@end

NS_ASSUME_NONNULL_END