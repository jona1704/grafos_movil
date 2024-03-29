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

#import "FIRDocumentSnapshot.h"

#include <memory>

#include "Firestore/core/src/firebase/firestore/api/document_snapshot.h"
#include "Firestore/core/src/firebase/firestore/api/snapshot_metadata.h"
<<<<<<< HEAD
<<<<<<< HEAD
#include "Firestore/core/src/firebase/firestore/model/document.h"
#include "Firestore/core/src/firebase/firestore/model/document_key.h"

=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#include "Firestore/core/src/firebase/firestore/model/document_key.h"

@class FIRFirestore;
@class FSTDocument;

<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
namespace api = firebase::firestore::api;
namespace model = firebase::firestore::model;

NS_ASSUME_NONNULL_BEGIN

@interface FIRDocumentSnapshot (/* Init */)

- (instancetype)initWithSnapshot:(api::DocumentSnapshot &&)snapshot NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithFirestore:(std::shared_ptr<api::Firestore>)firestore
                      documentKey:(model::DocumentKey)documentKey
<<<<<<< HEAD
<<<<<<< HEAD
                         document:(const absl::optional<model::Document> &)document
=======
                         document:(nullable FSTDocument *)document
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
                         document:(nullable FSTDocument *)document
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
                         metadata:(api::SnapshotMetadata)metadata;

- (instancetype)initWithFirestore:(std::shared_ptr<api::Firestore>)firestore
                      documentKey:(model::DocumentKey)documentKey
<<<<<<< HEAD
<<<<<<< HEAD
                         document:(const absl::optional<model::Document> &)document
=======
                         document:(nullable FSTDocument *)document
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
                         document:(nullable FSTDocument *)document
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
                        fromCache:(bool)fromCache
                 hasPendingWrites:(bool)hasPendingWrites;

@end

/** Internal FIRDocumentSnapshot API we don't want exposed in our public header files. */
@interface FIRDocumentSnapshot (Internal)

<<<<<<< HEAD
<<<<<<< HEAD
- (const absl::optional<model::Document> &)internalDocument;
=======
@property(nonatomic, strong, readonly, nullable) FSTDocument *internalDocument;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
@property(nonatomic, strong, readonly, nullable) FSTDocument *internalDocument;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

@end

NS_ASSUME_NONNULL_END
