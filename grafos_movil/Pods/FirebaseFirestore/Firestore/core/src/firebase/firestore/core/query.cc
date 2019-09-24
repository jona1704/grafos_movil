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

#include "Firestore/core/src/firebase/firestore/core/query.h"

#include <algorithm>
<<<<<<< HEAD
<<<<<<< HEAD
#include <ostream>

#include "Firestore/core/src/firebase/firestore/core/field_filter.h"
#include "Firestore/core/src/firebase/firestore/core/operator.h"
=======

#include "Firestore/core/src/firebase/firestore/core/relation_filter.h"
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======

#include "Firestore/core/src/firebase/firestore/core/relation_filter.h"
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#include "Firestore/core/src/firebase/firestore/model/document_key.h"
#include "Firestore/core/src/firebase/firestore/model/field_path.h"
#include "Firestore/core/src/firebase/firestore/model/resource_path.h"
#include "Firestore/core/src/firebase/firestore/util/equality.h"
#include "Firestore/core/src/firebase/firestore/util/hard_assert.h"
<<<<<<< HEAD
<<<<<<< HEAD
#include "Firestore/core/src/firebase/firestore/util/hashing.h"
#include "absl/algorithm/container.h"
#include "absl/strings/str_cat.h"
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

namespace firebase {
namespace firestore {
namespace core {
<<<<<<< HEAD
<<<<<<< HEAD
=======
namespace {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
namespace {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

using Operator = Filter::Operator;
using Type = Filter::Type;

using model::Document;
<<<<<<< HEAD
<<<<<<< HEAD
using model::DocumentComparator;
using model::DocumentKey;
using model::FieldPath;
using model::ResourcePath;
using util::ComparisonResult;
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
using model::DocumentKey;
using model::FieldPath;
using model::ResourcePath;

template <typename T>
util::vector_of_ptr<T> AppendingTo(const util::vector_of_ptr<T>& vector,
                                   T&& value) {
  util::vector_of_ptr<T> updated = vector;
  updated.push_back(std::forward<T>(value));
  return updated;
}

}  // namespace
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

Query::Query(ResourcePath path, std::string collection_group)
    : path_(std::move(path)),
      collection_group_(
          std::make_shared<const std::string>(std::move(collection_group))) {
}

// MARK: - Accessors

bool Query::IsDocumentQuery() const {
  return DocumentKey::IsDocumentKey(path_) && !collection_group_ &&
         filters_.empty();
}

const FieldPath* Query::InequalityFilterField() const {
  for (const auto& filter : filters_) {
<<<<<<< HEAD
<<<<<<< HEAD
    if (filter.IsInequality()) {
      return &filter.field();
=======
    if (filter->IsInequality()) {
      return &filter->field();
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
    if (filter->IsInequality()) {
      return &filter->field();
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    }
  }
  return nullptr;
}

<<<<<<< HEAD
<<<<<<< HEAD
absl::optional<Operator> Query::FirstArrayOperator() const {
  for (const auto& filter : filters_) {
    if (filter.IsAFieldFilter()) {
      FieldFilter relation_filter(filter);
      if (IsArrayOperator(relation_filter.op())) {
        return relation_filter.op();
      }
    }
  }
  return absl::nullopt;
}

absl::optional<Operator> Query::FirstDisjunctiveOperator() const {
  for (const auto& filter : filters_) {
    if (filter.IsAFieldFilter()) {
      FieldFilter relation_filter(filter);
      if (IsDisjunctiveOperator(relation_filter.op())) {
        return relation_filter.op();
      }
    }
  }
  return absl::nullopt;
}

const OrderByList& Query::order_bys() const {
  if (memoized_order_bys_.empty()) {
    const FieldPath* inequality_field = InequalityFilterField();
    const FieldPath* first_order_by_field = FirstOrderByField();
    if (inequality_field && !first_order_by_field) {
      // In order to implicitly add key ordering, we must also add the
      // inequality filter field for it to be a valid query. Note that the
      // default inequality field and key ordering is ascending.
      if (inequality_field->IsKeyFieldPath()) {
        memoized_order_bys_ = {
            OrderBy(FieldPath::KeyFieldPath(), Direction::Ascending),
        };
      } else {
        memoized_order_bys_ = {
            OrderBy(*inequality_field, Direction::Ascending),
            OrderBy(FieldPath::KeyFieldPath(), Direction::Ascending),
        };
      }
    } else {
      HARD_ASSERT(
          !inequality_field || *inequality_field == *first_order_by_field,
          "First orderBy %s should match inequality field %s.",
          first_order_by_field->CanonicalString(),
          inequality_field->CanonicalString());

      OrderByList result = explicit_order_bys_;

      bool found_explicit_key_order = false;
      for (const OrderBy& order_by : explicit_order_bys_) {
        if (order_by.field().IsKeyFieldPath()) {
          found_explicit_key_order = true;
          break;
        }
      }

      if (!found_explicit_key_order) {
        // The direction of the implicit key ordering always matches the
        // direction of the last explicit sort order
        Direction last_direction = explicit_order_bys_.empty()
                                       ? Direction::Ascending
                                       : explicit_order_bys_.back().direction();
        result = result.emplace_back(FieldPath::KeyFieldPath(), last_direction);
      }

      memoized_order_bys_ = std::move(result);
    }
  }
  return memoized_order_bys_;
}

const FieldPath* Query::FirstOrderByField() const {
  if (explicit_order_bys_.empty()) {
    return nullptr;
  }

  return &explicit_order_bys_.front().field();
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
bool Query::HasArrayContainsFilter() const {
  for (const auto& filter : filters_) {
    if (filter->type() == Type::kRelationFilter) {
      const auto& relation_filter = static_cast<const RelationFilter&>(*filter);
      if (relation_filter.op() == Operator::ArrayContains) {
        return true;
      }
    }
  }
  return false;
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
}

// MARK: - Builder methods

<<<<<<< HEAD
<<<<<<< HEAD
Query Query::AddingFilter(Filter filter) const {
  HARD_ASSERT(!IsDocumentQuery(), "No filter is allowed for document query");

  const FieldPath* new_inequality_field = nullptr;
  if (filter.IsInequality()) {
    new_inequality_field = &filter.field();
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
Query Query::Filter(std::shared_ptr<core::Filter> filter) const {
  HARD_ASSERT(!IsDocumentQuery(), "No filter is allowed for document query");

  const FieldPath* new_inequality_field = nullptr;
  if (filter->IsInequality()) {
    new_inequality_field = &filter->field();
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  }
  const FieldPath* query_inequality_field = InequalityFilterField();
  HARD_ASSERT(!query_inequality_field || !new_inequality_field ||
                  *query_inequality_field == *new_inequality_field,
              "Query must only have one inequality field.");

  // TODO(rsgowman): ensure first orderby must match inequality field

<<<<<<< HEAD
<<<<<<< HEAD
  return Query(path_, collection_group_, filters_.push_back(std::move(filter)),
               explicit_order_bys_, limit_, start_at_, end_at_);
}

Query Query::AddingOrderBy(OrderBy order_by) const {
  HARD_ASSERT(!IsDocumentQuery(), "No ordering is allowed for document query");

  if (explicit_order_bys_.empty()) {
    const FieldPath* inequality = InequalityFilterField();
    HARD_ASSERT(inequality == nullptr || *inequality == order_by.field(),
                "First OrderBy must match inequality field.");
  }

  return Query(path_, collection_group_, filters_,
               explicit_order_bys_.push_back(std::move(order_by)), limit_,
               start_at_, end_at_);
}

Query Query::WithLimit(int32_t limit) const {
  return Query(path_, collection_group_, filters_, explicit_order_bys_, limit,
               start_at_, end_at_);
}

Query Query::StartingAt(Bound bound) const {
  return Query(path_, collection_group_, filters_, explicit_order_bys_, limit_,
               std::make_shared<Bound>(std::move(bound)), end_at_);
}

Query Query::EndingAt(Bound bound) const {
  return Query(path_, collection_group_, filters_, explicit_order_bys_, limit_,
               start_at_, std::make_shared<Bound>(std::move(bound)));
}

Query Query::AsCollectionQueryAtPath(ResourcePath path) const {
  return Query(path, /*collection_group=*/nullptr, filters_,
               explicit_order_bys_, limit_, start_at_, end_at_);
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  return Query(path_, collection_group_,
               AppendingTo(filters_, std::move(filter)));
}

Query Query::AsCollectionQueryAtPath(ResourcePath path) const {
  return Query(path, /*collection_group=*/nullptr, filters_);
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
}

// MARK: - Matching

bool Query::Matches(const Document& doc) const {
<<<<<<< HEAD
<<<<<<< HEAD
  return MatchesPathAndCollectionGroup(doc) && MatchesOrderBy(doc) &&
         MatchesFilters(doc) && MatchesBounds(doc);
}

bool Query::MatchesPathAndCollectionGroup(const Document& doc) const {
  const ResourcePath& doc_path = doc.key().path();
  if (collection_group_) {
    // NOTE: path_ is currently always empty since we don't expose Collection
    // Group queries rooted at a document path yet.
    return doc.key().HasCollectionId(*collection_group_) &&
           path_.IsPrefixOf(doc_path);
  } else if (DocumentKey::IsDocumentKey(path_)) {
    // Exact match for document queries.
    return path_ == doc_path;
  } else {
    // Shallow ancestor queries by default.
    return path_.IsImmediateParentOf(doc_path);
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  return MatchesPath(doc) && MatchesOrderBy(doc) && MatchesFilters(doc) &&
         MatchesBounds(doc);
}

bool Query::MatchesPath(const Document& doc) const {
  const ResourcePath& doc_path = doc.key().path();
  if (DocumentKey::IsDocumentKey(path_)) {
    return path_ == doc_path;
  } else {
    return path_.IsPrefixOf(doc_path) && path_.size() == doc_path.size() - 1;
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  }
}

bool Query::MatchesFilters(const Document& doc) const {
<<<<<<< HEAD
<<<<<<< HEAD
  for (const auto& filter : filters_) {
    if (!filter.Matches(doc)) return false;
  }
  return true;
}

bool Query::MatchesOrderBy(const Document& doc) const {
  for (const OrderBy& order_by : explicit_order_bys_) {
    const FieldPath& field_path = order_by.field();
    // order by key always matches
    if (field_path != FieldPath::KeyFieldPath() &&
        doc.field(field_path) == absl::nullopt) {
      return false;
    }
  }
  return true;
}

bool Query::MatchesBounds(const Document& doc) const {
  const OrderByList& ordering = order_bys();
  if (start_at_ && !start_at_->SortsBeforeDocument(ordering, doc)) {
    return false;
  }
  if (end_at_ && end_at_->SortsBeforeDocument(ordering, doc)) {
    return false;
  }
  return true;
}

model::DocumentComparator Query::Comparator() const {
  OrderByList ordering = order_bys();

  bool has_key_ordering = false;
  for (const OrderBy& order_by : ordering) {
    if (order_by.field() == FieldPath::KeyFieldPath()) {
      has_key_ordering = true;
      break;
    }
  }
  HARD_ASSERT(has_key_ordering,
              "QueryComparator needs to have a key ordering.");

  return DocumentComparator(
      [ordering](const Document& doc1, const Document& doc2) {
        for (const OrderBy& order_by : ordering) {
          ComparisonResult comp = order_by.Compare(doc1, doc2);
          if (!util::Same(comp)) return comp;
        }
        return ComparisonResult::Same;
      });
}

const std::string& Query::CanonicalId() const {
  if (!canonical_id_.empty()) return canonical_id_;

  std::string result;
  absl::StrAppend(&result, path_.CanonicalString());

  if (collection_group_) {
    absl::StrAppend(&result, "|cg:", *collection_group_);
  }

  // Add filters.
  absl::StrAppend(&result, "|f:");
  for (const auto& filter : filters_) {
    absl::StrAppend(&result, filter.CanonicalId());
  }

  // Add order by.
  absl::StrAppend(&result, "|ob:");
  for (const OrderBy& order_by : order_bys()) {
    absl::StrAppend(&result, order_by.CanonicalId());
  }

  // Add limit.
  if (limit_ != kNoLimit) {
    absl::StrAppend(&result, "|l:", limit_);
  }

  if (start_at_) {
    absl::StrAppend(&result, "|lb:", start_at_->CanonicalId());
  }

  if (end_at_) {
    absl::StrAppend(&result, "|ub:", end_at_->CanonicalId());
  }

  canonical_id_ = std::move(result);
  return canonical_id_;
}

size_t Query::Hash() const {
  return util::Hash(CanonicalId());
}

std::string Query::ToString() const {
  return absl::StrCat("Query(canonical_id=", CanonicalId(), ")");
}

std::ostream& operator<<(std::ostream& os, const Query& query) {
  return os << query.ToString();
}

bool operator==(const Query& lhs, const Query& rhs) {
  return lhs.path() == rhs.path() &&
         util::Equals(lhs.collection_group(), rhs.collection_group()) &&
         lhs.filters() == rhs.filters() && lhs.order_bys() == rhs.order_bys() &&
         lhs.limit() == rhs.limit() &&
         util::Equals(lhs.start_at(), rhs.start_at()) &&
         util::Equals(lhs.end_at(), rhs.end_at());
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  return std::all_of(filters_.begin(), filters_.end(),
                     [&](const std::shared_ptr<core::Filter>& filter) {
                       return filter->Matches(doc);
                     });
}

bool Query::MatchesOrderBy(const Document&) const {
  // TODO(rsgowman): Implement this correctly.
  return true;
}

bool Query::MatchesBounds(const Document&) const {
  // TODO(rsgowman): Implement this correctly.
  return true;
}

bool operator==(const Query& lhs, const Query& rhs) {
  return lhs.path() == rhs.path() &&
         util::Equals(lhs.collection_group(), rhs.collection_group()) &&
         lhs.filters() == rhs.filters();
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
}

}  // namespace core
}  // namespace firestore
}  // namespace firebase
