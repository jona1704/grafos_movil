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

#ifndef FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_LOCAL_QUERY_DATA_H_
#define FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_LOCAL_QUERY_DATA_H_

<<<<<<< HEAD
<<<<<<< HEAD
#include <iosfwd>
#include <string>
=======
#include <cstdint>
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
#include <cstdint>
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#include <vector>

#include "Firestore/core/src/firebase/firestore/core/query.h"
#include "Firestore/core/src/firebase/firestore/model/snapshot_version.h"
#include "Firestore/core/src/firebase/firestore/model/types.h"
#include "Firestore/core/src/firebase/firestore/nanopb/byte_string.h"

namespace firebase {
namespace firestore {
namespace local {

/** An enumeration for the different purposes we have for queries. */
enum class QueryPurpose {
  /** A regular, normal query. */
<<<<<<< HEAD
<<<<<<< HEAD
  Listen,
=======
  kListen,
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  kListen,
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

  /**
   * The query was used to refill a query after an existence filter mismatch.
   */
<<<<<<< HEAD
<<<<<<< HEAD
  ExistenceFilterMismatch,

  /** The query was used to resolve a limbo document. */
  LimboResolution,
};

std::ostream& operator<<(std::ostream& os, QueryPurpose purpose);

=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  kExistenceFilterMismatch,

  /** The query was used to resolve a limbo document. */
  kLimboResolution,
};

<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
/**
 * An immutable set of metadata that the store will need to keep track of for
 * each query.
 */
class QueryData {
 public:
  /**
   * Creates a new QueryData with the given values.
   *
   * @param query The query being listened to.
   * @param target_id The target to which the query corresponds, assigned by the
   *     LocalStore for user queries or the SyncEngine for limbo queries.
   * @param purpose The purpose of the query.
   * @param snapshot_version The latest snapshot version seen for this target.
   * @param resume_token An opaque, server-assigned token that allows watching a
   *     query to be resumed after disconnecting without retransmitting all the
   *     data that matches the query. The resume token essentially identifies a
   *     point in time from which the server should resume sending results.
   */
<<<<<<< HEAD
<<<<<<< HEAD
  QueryData(core::Query query,
            model::TargetId target_id,
            model::ListenSequenceNumber sequence_number,
            QueryPurpose purpose,
            model::SnapshotVersion snapshot_version,
            nanopb::ByteString resume_token);
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  QueryData(core::Query&& query,
            model::TargetId target_id,
            model::ListenSequenceNumber sequence_number,
            QueryPurpose purpose,
            model::SnapshotVersion&& snapshot_version,
            nanopb::ByteString&& resume_token);
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

  /**
   * Convenience constructor for use when creating a QueryData for the first
   * time.
   */
<<<<<<< HEAD
<<<<<<< HEAD
  QueryData(core::Query query,
            int target_id,
            model::ListenSequenceNumber sequence_number,
            QueryPurpose purpose);

  /**
   * Creates an invalid QueryData. Prefer QueryData::Invalid() for readability.
   */
  QueryData() = default;
=======
  // TODO(rsgowman): Define once WatchStream::EmptyResumeToken exists.
  // QueryData(const core::Query& query, int target_id, QueryPurpose purpose);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  // TODO(rsgowman): Define once WatchStream::EmptyResumeToken exists.
  // QueryData(const core::Query& query, int target_id, QueryPurpose purpose);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

  /**
   * Constructs an invalid QueryData. Reading any properties of the returned
   * value is undefined.
   */
  static QueryData Invalid();

<<<<<<< HEAD
<<<<<<< HEAD
  /** The query being listened to. */
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  const core::Query& query() const {
    return query_;
  }

<<<<<<< HEAD
<<<<<<< HEAD
  /**
   * The TargetId to which the query corresponds, assigned by the FSTLocalStore
   * for user queries or the FSTSyncEngine for limbo queries.
   */
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  model::TargetId target_id() const {
    return target_id_;
  }

  model::ListenSequenceNumber sequence_number() const {
    return sequence_number_;
  }

<<<<<<< HEAD
<<<<<<< HEAD
  /** The purpose of the query. */
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  QueryPurpose purpose() const {
    return purpose_;
  }

<<<<<<< HEAD
<<<<<<< HEAD
  /** The latest snapshot version seen for this target. */
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  const model::SnapshotVersion& snapshot_version() const {
    return snapshot_version_;
  }

<<<<<<< HEAD
<<<<<<< HEAD
  /**
   * An opaque, server-assigned token that allows watching a query to be resumed
   * after disconnecting without retransmitting all the data that matches the
   * query. The resume token essentially identifies a point in time from which
   * the server should resume sending results.
   */
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  const nanopb::ByteString& resume_token() const {
    return resume_token_;
  }

<<<<<<< HEAD
<<<<<<< HEAD
  QueryData Copy(model::SnapshotVersion snapshot_version,
                 nanopb::ByteString resume_token,
                 model::ListenSequenceNumber sequence_number) const;

  friend bool operator==(const QueryData& lhs, const QueryData& rhs);

  size_t Hash() const;

  std::string ToString() const;

  friend std::ostream& operator<<(std::ostream& os, const QueryData& value);
=======
  QueryData Copy(model::SnapshotVersion&& snapshot_version,
                 nanopb::ByteString&& resume_token) const;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  QueryData Copy(model::SnapshotVersion&& snapshot_version,
                 nanopb::ByteString&& resume_token) const;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

 private:
  core::Query query_;
  model::TargetId target_id_;
  model::ListenSequenceNumber sequence_number_;
  QueryPurpose purpose_;
  model::SnapshotVersion snapshot_version_;
  nanopb::ByteString resume_token_;
};

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
inline bool operator==(const QueryData& lhs, const QueryData& rhs) {
  return lhs.query() == rhs.query() && lhs.target_id() == rhs.target_id() &&
         lhs.sequence_number() == rhs.sequence_number() &&
         lhs.purpose() == rhs.purpose() &&
         lhs.snapshot_version() == rhs.snapshot_version() &&
         lhs.resume_token() == rhs.resume_token();
}

<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
inline bool operator!=(const QueryData& lhs, const QueryData& rhs) {
  return !(lhs == rhs);
}

}  // namespace local
}  // namespace firestore
}  // namespace firebase

#endif  // FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_LOCAL_QUERY_DATA_H_
