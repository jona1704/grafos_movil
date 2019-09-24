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

#import <Foundation/Foundation.h>

#include <string>
#include <unordered_map>

<<<<<<< HEAD
#include "Firestore/core/src/firebase/firestore/api/settings.h"
#include "Firestore/core/src/firebase/firestore/local/query_cache.h"
#include "Firestore/core/src/firebase/firestore/local/query_data.h"
#include "Firestore/core/src/firebase/firestore/model/document_key.h"
#include "Firestore/core/src/firebase/firestore/model/types.h"

=======
#import "Firestore/Source/Local/FSTQueryData.h"

#include "Firestore/core/src/firebase/firestore/api/settings.h"
#include "Firestore/core/src/firebase/firestore/local/query_cache.h"
#include "Firestore/core/src/firebase/firestore/model/document_key.h"
#include "Firestore/core/src/firebase/firestore/model/types.h"

@class FSTLRUGarbageCollector;

namespace model = firebase::firestore::model;

extern const model::ListenSequenceNumber kFSTListenSequenceNumberInvalid;

>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
namespace firebase {
namespace firestore {
namespace local {

<<<<<<< HEAD
class LruGarbageCollector;
=======
struct LruParams {
  static LruParams Default() {
    return LruParams{100 * 1024 * 1024, 10, 1000};
  }

  static LruParams Disabled() {
    return LruParams{api::Settings::CacheSizeUnlimited, 0, 0};
  }

  static LruParams WithCacheSize(int64_t cacheSize) {
    LruParams params = Default();
    params.minBytesThreshold = cacheSize;
    return params;
  }

  int64_t minBytesThreshold;
  int percentileToCollect;
  int maximumSequenceNumbersToCollect;
};

struct LruResults {
  static LruResults DidNotRun() {
    return LruResults{/* didRun= */ false, 0, 0, 0};
  }

  bool didRun;
  int sequenceNumbersCollected;
  int targetsRemoved;
  int documentsRemoved;
};
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

}  // namespace local
}  // namespace firestore
}  // namespace firebase

namespace local = firebase::firestore::local;
<<<<<<< HEAD
namespace model = firebase::firestore::model;
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

/**
 * Persistence layers intending to use LRU Garbage collection should implement this protocol. This
 * protocol defines the operations that the LRU garbage collector needs from the persistence layer.
 */
@protocol FSTLRUDelegate

/**
 * Enumerates all the targets that the delegate is aware of. This is typically all of the targets in
 * an FSTQueryCache.
 */
- (void)enumerateTargetsUsingCallback:(const local::TargetCallback &)callback;

/**
 * Enumerates all of the outstanding mutations.
 */
- (void)enumerateMutationsUsingCallback:(const local::OrphanedDocumentCallback &)callback;

/**
 * Removes all unreferenced documents from the cache that have a sequence number less than or equal
 * to the given sequence number. Returns the number of documents removed.
 */
- (int)removeOrphanedDocumentsThroughSequenceNumber:(model::ListenSequenceNumber)sequenceNumber;

/**
 * Removes all targets that are not currently being listened to and have a sequence number less than
 * or equal to the given sequence number. Returns the number of targets removed.
 */
- (int)removeTargetsThroughSequenceNumber:(model::ListenSequenceNumber)sequenceNumber
                              liveQueries:
<<<<<<< HEAD
                                  (const std::unordered_map<model::TargetId, local::QueryData> &)
                                      liveQueries;

- (int64_t)byteSize;
=======
                                  (const std::unordered_map<model::TargetId, FSTQueryData *> &)
                                      liveQueries;

- (size_t)byteSize;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

/** Returns the number of targets and orphaned documents cached. */
- (size_t)sequenceNumberCount;

/** Access to the underlying LRU Garbage collector instance. */
<<<<<<< HEAD
- (local::LruGarbageCollector *)gc;
=======
@property(strong, nonatomic, readonly) FSTLRUGarbageCollector *gc;

@end

/**
 * FSTLRUGarbageCollector defines the LRU algorithm used to clean up old documents and targets. It
 * is persistence-agnostic, as long as proper delegate is provided.
 */
@interface FSTLRUGarbageCollector : NSObject

- (instancetype)initWithDelegate:(id<FSTLRUDelegate>)delegate
                          params:(local::LruParams)params NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;

/**
 * Given a target percentile, return the number of queries that make up that percentage of the
 * queries that are cached. For instance, if 20 queries are cached, and the percentile is 40, the
 * result will be 8.
 */
- (int)queryCountForPercentile:(NSUInteger)percentile;

/**
 * Given a number of queries n, return the nth sequence number in the cache.
 */
- (model::ListenSequenceNumber)sequenceNumberForQueryCount:(NSUInteger)queryCount;

/**
 * Removes queries that are not currently live (as indicated by presence in the liveQueries map) and
 * have a sequence number less than or equal to the given sequence number.
 */
- (int)removeQueriesUpThroughSequenceNumber:(model::ListenSequenceNumber)sequenceNumber
                                liveQueries:
                                    (const std::unordered_map<model::TargetId, FSTQueryData *> &)
                                        liveQueries;

/**
 * Removes all unreferenced documents from the cache that have a sequence number less than or equal
 * to the given sequence number. Returns the number of documents removed.
 */
- (int)removeOrphanedDocumentsThroughSequenceNumber:(model::ListenSequenceNumber)sequenceNumber;

- (size_t)byteSize;

- (local::LruResults)collectWithLiveTargets:
    (const std::unordered_map<model::TargetId, FSTQueryData *> &)liveTargets;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

@end
