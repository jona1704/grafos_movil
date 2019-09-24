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

#import "Firestore/Source/Local/FSTLocalSerializer.h"

#include <cinttypes>
#include <utility>
#include <vector>

#import "FIRTimestamp.h"
#import "Firestore/Protos/objc/firestore/local/MaybeDocument.pbobjc.h"
#import "Firestore/Protos/objc/firestore/local/Mutation.pbobjc.h"
#import "Firestore/Protos/objc/firestore/local/Target.pbobjc.h"
#import "Firestore/Protos/objc/google/firestore/v1/Document.pbobjc.h"
<<<<<<< HEAD
#import "Firestore/Source/Remote/FSTSerializerBeta.h"

#include "Firestore/core/include/firebase/firestore/timestamp.h"
#include "Firestore/core/src/firebase/firestore/core/query.h"
#include "Firestore/core/src/firebase/firestore/local/query_data.h"
#include "Firestore/core/src/firebase/firestore/model/document.h"
#include "Firestore/core/src/firebase/firestore/model/document_key.h"
#include "Firestore/core/src/firebase/firestore/model/mutation_batch.h"
#include "Firestore/core/src/firebase/firestore/model/no_document.h"
#include "Firestore/core/src/firebase/firestore/model/snapshot_version.h"
#include "Firestore/core/src/firebase/firestore/model/unknown_document.h"
#include "Firestore/core/src/firebase/firestore/nanopb/nanopb_util.h"
#include "Firestore/core/src/firebase/firestore/util/hard_assert.h"

using firebase::Timestamp;
using firebase::firestore::core::Query;
using firebase::firestore::local::QueryData;
using firebase::firestore::local::QueryPurpose;
using firebase::firestore::model::Document;
using firebase::firestore::model::DocumentKey;
using firebase::firestore::model::DocumentState;
using firebase::firestore::model::ListenSequenceNumber;
using firebase::firestore::model::MaybeDocument;
using firebase::firestore::model::Mutation;
using firebase::firestore::model::MutationBatch;
using firebase::firestore::model::NoDocument;
using firebase::firestore::model::ObjectValue;
using firebase::firestore::model::SnapshotVersion;
using firebase::firestore::model::TargetId;
using firebase::firestore::model::UnknownDocument;
using firebase::firestore::nanopb::ByteString;
using firebase::firestore::nanopb::MakeByteString;
using firebase::firestore::nanopb::MakeNSData;
=======
#import "Firestore/Source/Core/FSTQuery.h"
#import "Firestore/Source/Local/FSTQueryData.h"
#import "Firestore/Source/Model/FSTDocument.h"
#import "Firestore/Source/Model/FSTMutationBatch.h"
#import "Firestore/Source/Remote/FSTSerializerBeta.h"

#include "Firestore/core/include/firebase/firestore/timestamp.h"
#include "Firestore/core/src/firebase/firestore/model/document.h"
#include "Firestore/core/src/firebase/firestore/model/document_key.h"
#include "Firestore/core/src/firebase/firestore/model/snapshot_version.h"
#include "Firestore/core/src/firebase/firestore/util/hard_assert.h"

using firebase::Timestamp;
using firebase::firestore::model::DocumentKey;
using firebase::firestore::model::DocumentState;
using firebase::firestore::model::ListenSequenceNumber;
using firebase::firestore::model::ObjectValue;
using firebase::firestore::model::SnapshotVersion;
using firebase::firestore::model::TargetId;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

@interface FSTLocalSerializer ()

@property(nonatomic, strong, readonly) FSTSerializerBeta *remoteSerializer;

@end

/** Serializer for values stored in the LocalStore. */
@implementation FSTLocalSerializer

- (instancetype)initWithRemoteSerializer:(FSTSerializerBeta *)remoteSerializer {
  self = [super init];
  if (self) {
    _remoteSerializer = remoteSerializer;
  }
  return self;
}

<<<<<<< HEAD
- (FSTPBMaybeDocument *)encodedMaybeDocument:(const MaybeDocument &)document {
  FSTPBMaybeDocument *proto = [FSTPBMaybeDocument message];

  if (document.is_no_document()) {
    NoDocument deletedDocument(document);
    proto.noDocument = [self encodedDeletedDocument:deletedDocument];
    proto.hasCommittedMutations = deletedDocument.has_committed_mutations();
  } else if (document.is_document()) {
    Document existingDocument(document);
    const absl::any &docProto = existingDocument.proto();
    if (docProto.has_value()) {
      proto.document = absl::any_cast<GCFSDocument *>(docProto);
    } else {
      proto.document = [self encodedDocument:existingDocument];
    }
    proto.hasCommittedMutations = existingDocument.has_committed_mutations();
  } else if (document.is_unknown_document()) {
    UnknownDocument unknownDocument(document);
    proto.unknownDocument = [self encodedUnknownDocument:unknownDocument];
    proto.hasCommittedMutations = YES;
  } else {
    HARD_FAIL("Unknown document type %s", document.type());
=======
- (FSTPBMaybeDocument *)encodedMaybeDocument:(FSTMaybeDocument *)document {
  FSTPBMaybeDocument *proto = [FSTPBMaybeDocument message];

  if ([document isKindOfClass:[FSTDeletedDocument class]]) {
    FSTDeletedDocument *deletedDocument = (FSTDeletedDocument *)document;
    proto.noDocument = [self encodedDeletedDocument:deletedDocument];
    proto.hasCommittedMutations = deletedDocument.hasCommittedMutations;
  } else if ([document isKindOfClass:[FSTDocument class]]) {
    FSTDocument *existingDocument = (FSTDocument *)document;
    if (existingDocument.proto != nil) {
      proto.document = existingDocument.proto;
    } else {
      proto.document = [self encodedDocument:existingDocument];
    }
    proto.hasCommittedMutations = existingDocument.hasCommittedMutations;
  } else if ([document isKindOfClass:[FSTUnknownDocument class]]) {
    FSTUnknownDocument *unknownDocument = (FSTUnknownDocument *)document;
    proto.unknownDocument = [self encodedUnknownDocument:unknownDocument];
    proto.hasCommittedMutations = YES;
  } else {
    HARD_FAIL("Unknown document type %s", NSStringFromClass([document class]));
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  }

  return proto;
}

<<<<<<< HEAD
- (MaybeDocument)decodedMaybeDocument:(FSTPBMaybeDocument *)proto {
=======
- (FSTMaybeDocument *)decodedMaybeDocument:(FSTPBMaybeDocument *)proto {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  switch (proto.documentTypeOneOfCase) {
    case FSTPBMaybeDocument_DocumentType_OneOfCase_Document:
      return [self decodedDocument:proto.document
            withCommittedMutations:proto.hasCommittedMutations];

    case FSTPBMaybeDocument_DocumentType_OneOfCase_NoDocument:
      return [self decodedDeletedDocument:proto.noDocument
                   withCommittedMutations:proto.hasCommittedMutations];

    case FSTPBMaybeDocument_DocumentType_OneOfCase_UnknownDocument:
      return [self decodedUnknownDocument:proto.unknownDocument];

    default:
      HARD_FAIL("Unknown MaybeDocument %s", proto);
  }
}

/**
 * Encodes a Document for local storage. This differs from the v1 RPC serializer for Documents in
 * that it preserves the updateTime, which is considered an output only value by the server.
 */
<<<<<<< HEAD
- (GCFSDocument *)encodedDocument:(const Document &)document {
  FSTSerializerBeta *remoteSerializer = self.remoteSerializer;

  GCFSDocument *proto = [GCFSDocument message];
  proto.name = [remoteSerializer encodedDocumentKey:document.key()];
  proto.fields = [remoteSerializer encodedFields:document.data()];
  proto.updateTime = [remoteSerializer encodedVersion:document.version()];
=======
- (GCFSDocument *)encodedDocument:(FSTDocument *)document {
  FSTSerializerBeta *remoteSerializer = self.remoteSerializer;

  GCFSDocument *proto = [GCFSDocument message];
  proto.name = [remoteSerializer encodedDocumentKey:document.key];
  proto.fields = [remoteSerializer encodedFields:document.data];
  proto.updateTime = [remoteSerializer encodedVersion:document.version];
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

  return proto;
}

/** Decodes a Document proto to the equivalent model. */
<<<<<<< HEAD
- (Document)decodedDocument:(GCFSDocument *)document
     withCommittedMutations:(BOOL)committedMutations {
=======
- (FSTDocument *)decodedDocument:(GCFSDocument *)document
          withCommittedMutations:(BOOL)committedMutations {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  FSTSerializerBeta *remoteSerializer = self.remoteSerializer;

  ObjectValue data = [remoteSerializer decodedFields:document.fields];
  DocumentKey key = [remoteSerializer decodedDocumentKey:document.name];
  SnapshotVersion version = [remoteSerializer decodedVersion:document.updateTime];
<<<<<<< HEAD
  DocumentState state =
      committedMutations ? DocumentState::kCommittedMutations : DocumentState::kSynced;
  return Document(std::move(data), std::move(key), version, state);
}

/** Encodes a NoDocument value to the equivalent proto. */
- (FSTPBNoDocument *)encodedDeletedDocument:(const NoDocument &)document {
  FSTSerializerBeta *remoteSerializer = self.remoteSerializer;

  FSTPBNoDocument *proto = [FSTPBNoDocument message];
  proto.name = [remoteSerializer encodedDocumentKey:document.key()];
  proto.readTime = [remoteSerializer encodedVersion:document.version()];
=======
  return [FSTDocument documentWithData:std::move(data)
                                   key:std::move(key)
                               version:version
                                 state:committedMutations ? DocumentState::kCommittedMutations
                                                          : DocumentState::kSynced];
}

/** Encodes a NoDocument value to the equivalent proto. */
- (FSTPBNoDocument *)encodedDeletedDocument:(FSTDeletedDocument *)document {
  FSTSerializerBeta *remoteSerializer = self.remoteSerializer;

  FSTPBNoDocument *proto = [FSTPBNoDocument message];
  proto.name = [remoteSerializer encodedDocumentKey:document.key];
  proto.readTime = [remoteSerializer encodedVersion:document.version];
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  return proto;
}

/** Decodes a NoDocument proto to the equivalent model. */
<<<<<<< HEAD
- (NoDocument)decodedDeletedDocument:(FSTPBNoDocument *)proto
              withCommittedMutations:(BOOL)committedMutations {
=======
- (FSTDeletedDocument *)decodedDeletedDocument:(FSTPBNoDocument *)proto
                        withCommittedMutations:(BOOL)committedMutations {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  FSTSerializerBeta *remoteSerializer = self.remoteSerializer;

  DocumentKey key = [remoteSerializer decodedDocumentKey:proto.name];
  SnapshotVersion version = [remoteSerializer decodedVersion:proto.readTime];
<<<<<<< HEAD
  return NoDocument(std::move(key), version, committedMutations);
}

/** Encodes an UnknownDocument value to the equivalent proto. */
- (FSTPBUnknownDocument *)encodedUnknownDocument:(const UnknownDocument &)document {
  FSTSerializerBeta *remoteSerializer = self.remoteSerializer;

  FSTPBUnknownDocument *proto = [FSTPBUnknownDocument message];
  proto.name = [remoteSerializer encodedDocumentKey:document.key()];
  proto.version = [remoteSerializer encodedVersion:document.version()];
=======
  return [FSTDeletedDocument documentWithKey:key
                                     version:version
                       hasCommittedMutations:committedMutations];
}

/** Encodes an UnknownDocument value to the equivalent proto. */
- (FSTPBUnknownDocument *)encodedUnknownDocument:(FSTUnknownDocument *)document {
  FSTSerializerBeta *remoteSerializer = self.remoteSerializer;

  FSTPBUnknownDocument *proto = [FSTPBUnknownDocument message];
  proto.name = [remoteSerializer encodedDocumentKey:document.key];
  proto.version = [remoteSerializer encodedVersion:document.version];
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  return proto;
}

/** Decodes an UnknownDocument proto to the equivalent model. */
<<<<<<< HEAD
- (UnknownDocument)decodedUnknownDocument:(FSTPBUnknownDocument *)proto {
=======
- (FSTUnknownDocument *)decodedUnknownDocument:(FSTPBUnknownDocument *)proto {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  FSTSerializerBeta *remoteSerializer = self.remoteSerializer;

  DocumentKey key = [remoteSerializer decodedDocumentKey:proto.name];
  SnapshotVersion version = [remoteSerializer decodedVersion:proto.version];
<<<<<<< HEAD
  return UnknownDocument(std::move(key), version);
}

- (FSTPBWriteBatch *)encodedMutationBatch:(const MutationBatch &)batch {
  FSTSerializerBeta *remoteSerializer = self.remoteSerializer;

  FSTPBWriteBatch *proto = [FSTPBWriteBatch message];
  proto.batchId = batch.batch_id();
  proto.localWriteTime = [remoteSerializer encodedTimestamp:batch.local_write_time()];

  NSMutableArray<GCFSWrite *> *baseWrites = proto.baseWritesArray;
  for (const Mutation &baseMutation : batch.base_mutations()) {
    [baseWrites addObject:[remoteSerializer encodedMutation:baseMutation]];
  }
  NSMutableArray<GCFSWrite *> *writes = proto.writesArray;
  for (const Mutation &mutation : batch.mutations()) {
=======
  return [FSTUnknownDocument documentWithKey:key version:version];
}

- (FSTPBWriteBatch *)encodedMutationBatch:(FSTMutationBatch *)batch {
  FSTSerializerBeta *remoteSerializer = self.remoteSerializer;

  FSTPBWriteBatch *proto = [FSTPBWriteBatch message];
  proto.batchId = batch.batchID;
  proto.localWriteTime = [remoteSerializer encodedTimestamp:batch.localWriteTime];

  NSMutableArray<GCFSWrite *> *baseWrites = proto.baseWritesArray;
  for (FSTMutation *baseMutation : [batch baseMutations]) {
    [baseWrites addObject:[remoteSerializer encodedMutation:baseMutation]];
  }
  NSMutableArray<GCFSWrite *> *writes = proto.writesArray;
  for (FSTMutation *mutation : [batch mutations]) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    [writes addObject:[remoteSerializer encodedMutation:mutation]];
  }
  return proto;
}

<<<<<<< HEAD
- (MutationBatch)decodedMutationBatch:(FSTPBWriteBatch *)batch {
=======
- (FSTMutationBatch *)decodedMutationBatch:(FSTPBWriteBatch *)batch {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  FSTSerializerBeta *remoteSerializer = self.remoteSerializer;

  int batchID = batch.batchId;

<<<<<<< HEAD
  std::vector<Mutation> baseMutations;
  for (GCFSWrite *write in batch.baseWritesArray) {
    baseMutations.push_back([remoteSerializer decodedMutation:write]);
  }
  std::vector<Mutation> mutations;
=======
  std::vector<FSTMutation *> baseMutations;
  for (GCFSWrite *write in batch.baseWritesArray) {
    baseMutations.push_back([remoteSerializer decodedMutation:write]);
  }
  std::vector<FSTMutation *> mutations;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  for (GCFSWrite *write in batch.writesArray) {
    mutations.push_back([remoteSerializer decodedMutation:write]);
  }

  Timestamp localWriteTime = [remoteSerializer decodedTimestamp:batch.localWriteTime];

<<<<<<< HEAD
  return MutationBatch(batchID, localWriteTime, std::move(baseMutations), std::move(mutations));
}

- (FSTPBTarget *)encodedQueryData:(const QueryData &)queryData {
  FSTSerializerBeta *remoteSerializer = self.remoteSerializer;

  HARD_ASSERT(queryData.purpose() == QueryPurpose::Listen,
              "only queries with purpose %s may be stored, got %s", QueryPurpose::Listen,
              queryData.purpose());

  FSTPBTarget *proto = [FSTPBTarget message];
  proto.targetId = queryData.target_id();
  proto.lastListenSequenceNumber = queryData.sequence_number();
  proto.snapshotVersion = [remoteSerializer encodedVersion:queryData.snapshot_version()];
  proto.resumeToken = MakeNullableNSData(queryData.resume_token());

  const Query &query = queryData.query();
  if (query.IsDocumentQuery()) {
=======
  return [[FSTMutationBatch alloc] initWithBatchID:batchID
                                    localWriteTime:localWriteTime
                                     baseMutations:std::move(baseMutations)
                                         mutations:std::move(mutations)];
}

- (FSTPBTarget *)encodedQueryData:(FSTQueryData *)queryData {
  FSTSerializerBeta *remoteSerializer = self.remoteSerializer;

  HARD_ASSERT(queryData.purpose == FSTQueryPurposeListen,
              "only queries with purpose %s may be stored, got %s", FSTQueryPurposeListen,
              queryData.purpose);

  FSTPBTarget *proto = [FSTPBTarget message];
  proto.targetId = queryData.targetID;
  proto.lastListenSequenceNumber = queryData.sequenceNumber;
  proto.snapshotVersion = [remoteSerializer encodedVersion:queryData.snapshotVersion];
  proto.resumeToken = queryData.resumeToken;

  FSTQuery *query = queryData.query;
  if ([query isDocumentQuery]) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    proto.documents = [remoteSerializer encodedDocumentsTarget:query];
  } else {
    proto.query = [remoteSerializer encodedQueryTarget:query];
  }

  return proto;
}

<<<<<<< HEAD
- (QueryData)decodedQueryData:(FSTPBTarget *)target {
=======
- (FSTQueryData *)decodedQueryData:(FSTPBTarget *)target {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  FSTSerializerBeta *remoteSerializer = self.remoteSerializer;

  TargetId targetID = target.targetId;
  ListenSequenceNumber sequenceNumber = target.lastListenSequenceNumber;
  SnapshotVersion version = [remoteSerializer decodedVersion:target.snapshotVersion];
<<<<<<< HEAD
  ByteString resumeToken = MakeByteString(target.resumeToken);

  Query query;
=======
  NSData *resumeToken = target.resumeToken;

  FSTQuery *query;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  switch (target.targetTypeOneOfCase) {
    case FSTPBTarget_TargetType_OneOfCase_Documents:
      query = [remoteSerializer decodedQueryFromDocumentsTarget:target.documents];
      break;

    case FSTPBTarget_TargetType_OneOfCase_Query:
      query = [remoteSerializer decodedQueryFromQueryTarget:target.query];
      break;

    default:
      HARD_FAIL("Unknown Target.targetType %s", target.targetTypeOneOfCase);
  }

<<<<<<< HEAD
  return QueryData(std::move(query), targetID, sequenceNumber, QueryPurpose::Listen, version,
                   std::move(resumeToken));
=======
  return [[FSTQueryData alloc] initWithQuery:query
                                    targetID:targetID
                        listenSequenceNumber:sequenceNumber
                                     purpose:FSTQueryPurposeListen
                             snapshotVersion:version
                                 resumeToken:resumeToken];
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
}

- (GPBTimestamp *)encodedVersion:(const SnapshotVersion &)version {
  return [self.remoteSerializer encodedVersion:version];
}

- (SnapshotVersion)decodedVersion:(GPBTimestamp *)version {
  return [self.remoteSerializer decodedVersion:version];
}

@end
