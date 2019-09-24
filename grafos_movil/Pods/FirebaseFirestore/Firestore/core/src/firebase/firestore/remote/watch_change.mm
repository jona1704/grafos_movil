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

#include "Firestore/core/src/firebase/firestore/remote/watch_change.h"

<<<<<<< HEAD
=======
#import "Firestore/Source/Model/FSTDocument.h"

#include "Firestore/core/src/firebase/firestore/objc/objc_compatibility.h"

>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
namespace firebase {
namespace firestore {
namespace remote {

bool operator==(const DocumentWatchChange& lhs,
                const DocumentWatchChange& rhs) {
  return lhs.updated_target_ids() == rhs.updated_target_ids() &&
         lhs.removed_target_ids() == rhs.removed_target_ids() &&
         lhs.document_key() == rhs.document_key() &&
<<<<<<< HEAD
         lhs.new_document() == rhs.new_document();
=======
         objc::Equals(lhs.new_document(), rhs.new_document());
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
}

bool operator==(const ExistenceFilterWatchChange& lhs,
                const ExistenceFilterWatchChange& rhs) {
  return lhs.filter() == rhs.filter() && lhs.target_id() == rhs.target_id();
}

bool operator==(const WatchTargetChange& lhs, const WatchTargetChange& rhs) {
  return lhs.state() == rhs.state() && lhs.target_ids() == rhs.target_ids() &&
<<<<<<< HEAD
         lhs.resume_token() == rhs.resume_token() && lhs.cause() == rhs.cause();
=======
         objc::Equals(lhs.resume_token(), rhs.resume_token()) &&
         lhs.cause() == rhs.cause();
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
}

}  // namespace remote
}  // namespace firestore
}  // namespace firebase
