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

#ifndef FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_CORE_FILTER_H_
#define FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_CORE_FILTER_H_

#include <iosfwd>
#include <memory>
#include <string>

<<<<<<< HEAD
<<<<<<< HEAD
#include "Firestore/core/src/firebase/firestore/immutable/append_only_list.h"
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#include "Firestore/core/src/firebase/firestore/model/document.h"
#include "Firestore/core/src/firebase/firestore/model/field_path.h"
#include "Firestore/core/src/firebase/firestore/model/field_value.h"

namespace firebase {
namespace firestore {
namespace core {

/** Interface used for all query filters. All filters are immutable. */
class Filter {
 public:
  /**
   * Operator is a value relation operator that can be used to filter documents.
   * It is similar to NSPredicateOperatorType, but only has operators supported
   * by Firestore.
   */
  enum class Operator {
    LessThan,
    LessThanOrEqual,
    Equal,
    GreaterThanOrEqual,
    GreaterThan,
    ArrayContains,
<<<<<<< HEAD
<<<<<<< HEAD
    In,
    ArrayContainsAny,
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  };

  // For lack of RTTI, all subclasses must identify themselves so that
  // comparisons properly take type into account.
  enum class Type {
<<<<<<< HEAD
<<<<<<< HEAD
    kArrayContainsAnyFilter,
    kArrayContainsFilter,
    kFieldFilter,
    kInFilter,
    kKeyFieldFilter,
    kKeyFieldInFilter,
  };

  Type type() const {
    return rep_->type();
  }

  /**
   * Returns true if this instance is FieldFilter or any derived class.
   * Equivalent to `instanceof FieldFilter` on other platforms.
   *
   * Note this is different than checking `type() == Type::kFieldFilter` which
   * is only true if the type is exactly FieldFilter.
   */
  bool IsAFieldFilter() const {
    return rep_->IsAFieldFilter();
  }

  bool IsInequality() const {
    return rep_->IsInequality();
  }

  /** Returns the field the Filter operates over. */
  const model::FieldPath& field() const {
    return rep_->field();
  }

  /** Returns true if a document matches the filter. */
  bool Matches(const model::Document& doc) const {
    return rep_->Matches(doc);
  }

  /** A unique ID identifying the filter; used when serializing queries. */
  std::string CanonicalId() const {
    return rep_->CanonicalId();
  }

  /** A debug description of the Filter. */
  std::string ToString() const {
    return rep_->ToString();
  }

  size_t Hash() const {
    return rep_->Hash();
  }

  friend bool operator==(const Filter& lhs, const Filter& rhs);

 protected:
  class Rep {
   public:
    virtual ~Rep() = default;

    virtual Type type() const = 0;

    virtual bool IsAFieldFilter() const {
      return false;
    }

    virtual bool IsInequality() const {
      return false;
    }

    /** Returns the field the Filter operates over. */
    virtual const model::FieldPath& field() const = 0;

    /** Returns true if a document matches the filter. */
    virtual bool Matches(const model::Document& doc) const = 0;

    /** A unique ID identifying the filter; used when serializing queries. */
    virtual std::string CanonicalId() const = 0;

    virtual bool Equals(const Rep& other) const = 0;

    virtual size_t Hash() const = 0;

    /** A debug description of the Filter. */
    virtual std::string ToString() const = 0;
  };

  explicit Filter(std::shared_ptr<const Rep> rep) : rep_(rep) {
  }

  const Rep& rep() const {
    return *rep_;
  }

 private:
  std::shared_ptr<const Rep> rep_;
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    kRelationFilter,
    kNanFilter,
    kNullFilter,
  };

  /**
   * Creates a Filter instance for the provided path, operator, and value.
   *
   * Note that if the relational operator is Equal and the value is NullValue or
   * NaN, then this will return the appropriate NullFilter or NanFilter class
   * instead of a RelationFilter.
   */
  static std::shared_ptr<Filter> Create(model::FieldPath path,
                                        Operator op,
                                        model::FieldValue value_rhs);

  virtual ~Filter() = default;

  virtual Type type() const = 0;

  /** Returns the field the Filter operates over. */
  virtual const model::FieldPath& field() const = 0;

  /** Returns true if a document matches the filter. */
  virtual bool Matches(const model::Document& doc) const = 0;

  /** A unique ID identifying the filter; used when serializing queries. */
  virtual std::string CanonicalId() const = 0;

  /** A debug description of the Filter. */
  virtual std::string ToString() const = 0;

  virtual size_t Hash() const = 0;

  virtual bool IsInequality() const {
    return false;
  }

  friend bool operator==(const Filter& lhs, const Filter& rhs) {
    return lhs.Equals(rhs);
  }

 private:
  virtual bool Equals(const Filter& other) const = 0;
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
};

inline bool operator!=(const Filter& lhs, const Filter& rhs) {
  return !(lhs == rhs);
}

<<<<<<< HEAD
<<<<<<< HEAD
/** A list of Filters, as used in Queries and elsewhere. */
using FilterList = immutable::AppendOnlyList<Filter>;

=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
std::ostream& operator<<(std::ostream& os, const Filter& filter);

}  // namespace core
}  // namespace firestore
}  // namespace firebase

#endif  // FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_CORE_FILTER_H_
