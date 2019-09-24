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

#import <Foundation/Foundation.h>

#include <memory>
#include <vector>

#include "Firestore/core/include/firebase/firestore/timestamp.h"
<<<<<<< HEAD
<<<<<<< HEAD
#include "Firestore/core/src/firebase/firestore/core/field_filter.h"
#include "Firestore/core/src/firebase/firestore/core/query.h"
#include "Firestore/core/src/firebase/firestore/local/query_data.h"
=======
#include "Firestore/core/src/firebase/firestore/core/relation_filter.h"
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
#include "Firestore/core/src/firebase/firestore/core/relation_filter.h"
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#include "Firestore/core/src/firebase/firestore/model/database_id.h"
#include "Firestore/core/src/firebase/firestore/model/document_key.h"
#include "Firestore/core/src/firebase/firestore/model/field_mask.h"
#include "Firestore/core/src/firebase/firestore/model/field_transform.h"
#include "Firestore/core/src/firebase/firestore/model/field_value.h"
<<<<<<< HEAD
<<<<<<< HEAD
#include "Firestore/core/src/firebase/firestore/model/maybe_document.h"
#include "Firestore/core/src/firebase/firestore/model/mutation.h"
#include "Firestore/core/src/firebase/firestore/model/snapshot_version.h"
#include "Firestore/core/src/firebase/firestore/model/transform_operation.h"
#include "Firestore/core/src/firebase/firestore/remote/watch_change.h"

=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#include "Firestore/core/src/firebase/firestore/model/snapshot_version.h"
#include "Firestore/core/src/firebase/firestore/model/transform_operations.h"
#include "Firestore/core/src/firebase/firestore/remote/watch_change.h"

@class FSTMaybeDocument;
@class FSTMutation;
@class FSTMutationBatch;
@class FSTMutationResult;
@class FSTObjectValue;
@class FSTQuery;
@class FSTQueryData;

<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
@class GCFSBatchGetDocumentsResponse;
@class GCFSDocument;
@class GCFSDocumentMask;
@class GCFSDocumentTransform_FieldTransform;
@class GCFSListenResponse;
@class GCFSStructuredQuery_Filter;
<<<<<<< HEAD
<<<<<<< HEAD
@class GCFSStructuredQuery_FieldFilter;
@class GCFSStructuredQuery_UnaryFilter;
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
@class GCFSTarget;
@class GCFSTarget_DocumentsTarget;
@class GCFSTarget_QueryTarget;
@class GCFSValue;
@class GCFSWrite;
@class GCFSWriteResult;

@class GPBTimestamp;

namespace core = firebase::firestore::core;
<<<<<<< HEAD
<<<<<<< HEAD
namespace local = firebase::firestore::local;
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
namespace model = firebase::firestore::model;
namespace remote = firebase::firestore::remote;

NS_ASSUME_NONNULL_BEGIN

/**
 * Converts internal model objects to their equivalent protocol buffer form. Methods starting with
 * "encoded" convert to a protocol buffer and methods starting with "decoded" convert from a
 * protocol buffer.
 *
 * Throws an exception if a protocol buffer is missing a critical field or has a value we can't
 * interpret.
 */
@interface FSTSerializerBeta : NSObject

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithDatabaseID:(model::DatabaseId)databaseID NS_DESIGNATED_INITIALIZER;

- (GCFSValue *)encodedNull;
- (GCFSValue *)encodedBool:(bool)value;
- (GCFSValue *)encodedDouble:(double)value;
- (GCFSValue *)encodedInteger:(int64_t)value;
- (GCFSValue *)encodedString:(absl::string_view)value;

- (GPBTimestamp *)encodedTimestamp:(const firebase::Timestamp &)timestamp;
- (firebase::Timestamp)decodedTimestamp:(GPBTimestamp *)timestamp;

- (GPBTimestamp *)encodedVersion:(const model::SnapshotVersion &)version;
- (model::SnapshotVersion)decodedVersion:(GPBTimestamp *)version;

/** Returns the database ID, such as `projects/{project id}/databases/{database_id}`. */
- (NSString *)encodedDatabaseID;

/**
 * Encodes the given document key as a fully qualified name. This includes the
 * databaseId associated with this FSTSerializerBeta and the key path.
 */
- (NSString *)encodedDocumentKey:(const model::DocumentKey &)key;
- (model::DocumentKey)decodedDocumentKey:(NSString *)key;

- (GCFSValue *)encodedFieldValue:(const model::FieldValue &)fieldValue;
- (model::FieldValue)decodedFieldValue:(GCFSValue *)valueProto;

<<<<<<< HEAD
<<<<<<< HEAD
- (GCFSWrite *)encodedMutation:(const model::Mutation &)mutation;
- (model::Mutation)decodedMutation:(GCFSWrite *)mutation;
=======
- (GCFSWrite *)encodedMutation:(FSTMutation *)mutation;
- (FSTMutation *)decodedMutation:(GCFSWrite *)mutation;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
- (GCFSWrite *)encodedMutation:(FSTMutation *)mutation;
- (FSTMutation *)decodedMutation:(GCFSWrite *)mutation;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

- (GCFSDocumentMask *)encodedFieldMask:(const model::FieldMask &)fieldMask;

- (NSMutableArray<GCFSDocumentTransform_FieldTransform *> *)encodedFieldTransforms:
    (const std::vector<model::FieldTransform> &)fieldTransforms;

<<<<<<< HEAD
<<<<<<< HEAD
- (model::MutationResult)decodedMutationResult:(GCFSWriteResult *)mutation
                                 commitVersion:(const model::SnapshotVersion &)commitVersion;

- (nullable NSMutableDictionary<NSString *, NSString *> *)encodedListenRequestLabelsForQueryData:
    (const local::QueryData &)queryData;

- (GCFSTarget *)encodedTarget:(const local::QueryData &)queryData;

- (GCFSTarget_DocumentsTarget *)encodedDocumentsTarget:(const core::Query &)query;
- (core::Query)decodedQueryFromDocumentsTarget:(GCFSTarget_DocumentsTarget *)target;

- (GCFSTarget_QueryTarget *)encodedQueryTarget:(const core::Query &)query;
- (core::Query)decodedQueryFromQueryTarget:(GCFSTarget_QueryTarget *)target;

- (GCFSStructuredQuery_Filter *)encodedUnaryOrFieldFilter:(const core::FieldFilter &)filter;
- (core::FieldFilter)decodedFieldFilter:(GCFSStructuredQuery_FieldFilter *)proto;
- (core::FieldFilter)decodedUnaryFilter:(GCFSStructuredQuery_UnaryFilter *)proto;
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
- (FSTMutationResult *)decodedMutationResult:(GCFSWriteResult *)mutation
                               commitVersion:(const model::SnapshotVersion &)commitVersion;

- (nullable NSMutableDictionary<NSString *, NSString *> *)encodedListenRequestLabelsForQueryData:
    (FSTQueryData *)queryData;

- (GCFSTarget *)encodedTarget:(FSTQueryData *)queryData;

- (GCFSTarget_DocumentsTarget *)encodedDocumentsTarget:(FSTQuery *)query;
- (FSTQuery *)decodedQueryFromDocumentsTarget:(GCFSTarget_DocumentsTarget *)target;

- (GCFSTarget_QueryTarget *)encodedQueryTarget:(FSTQuery *)query;
- (FSTQuery *)decodedQueryFromQueryTarget:(GCFSTarget_QueryTarget *)target;

- (GCFSStructuredQuery_Filter *)encodedRelationFilter:(const core::RelationFilter &)filter;
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

- (std::unique_ptr<remote::WatchChange>)decodedWatchChange:(GCFSListenResponse *)watchChange;
- (model::SnapshotVersion)versionFromListenResponse:(GCFSListenResponse *)watchChange;

- (GCFSDocument *)encodedDocumentWithFields:(const model::ObjectValue &)objectValue
                                        key:(const model::DocumentKey &)key;

/**
<<<<<<< HEAD
<<<<<<< HEAD
 * Encodes an ObjectValue into a dictionary.
=======
 * Encodes an FSTObjectValue into a dictionary.
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
 * Encodes an FSTObjectValue into a dictionary.
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
 * @return a new dictionary that can be assigned to a field in another proto.
 */
- (NSMutableDictionary<NSString *, GCFSValue *> *)encodedFields:(const model::ObjectValue &)value;

- (model::ObjectValue)decodedFields:(NSDictionary<NSString *, GCFSValue *> *)fields;

<<<<<<< HEAD
<<<<<<< HEAD
- (model::MaybeDocument)decodedMaybeDocumentFromBatch:(GCFSBatchGetDocumentsResponse *)response;
=======
- (FSTMaybeDocument *)decodedMaybeDocumentFromBatch:(GCFSBatchGetDocumentsResponse *)response;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
- (FSTMaybeDocument *)decodedMaybeDocumentFromBatch:(GCFSBatchGetDocumentsResponse *)response;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

@end

NS_ASSUME_NONNULL_END
