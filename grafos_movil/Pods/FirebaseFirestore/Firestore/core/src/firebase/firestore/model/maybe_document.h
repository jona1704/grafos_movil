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

#ifndef FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_MODEL_MAYBE_DOCUMENT_H_
#define FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_MODEL_MAYBE_DOCUMENT_H_

#include <functional>
<<<<<<< HEAD
<<<<<<< HEAD
#include <iosfwd>
#include <memory>
#include <string>
#include <utility>
=======
#include <memory>
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
#include <memory>
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

#include "Firestore/core/src/firebase/firestore/model/document_key.h"
#include "Firestore/core/src/firebase/firestore/model/snapshot_version.h"

namespace firebase {
namespace firestore {
namespace model {

/**
 * The result of a lookup for a given path may be an existing document or a
 * tombstone that marks the path deleted.
<<<<<<< HEAD
<<<<<<< HEAD
 *
 * Note: MaybeDocument and its subclasses are specially designed to avoid
 * slicing. You can assign a subclass of MaybeDocument to an instance of
 * MaybeDocument and the full value is preserved, unsliced. Each subclass
 * declares an explicit constructor that can recover the derived type. This
 * means that code like this will work:
 *
 *     Document doc(...);
 *     MaybeDocument maybe_doc = doc;
 *     Document recovered(maybe_doc);
 *
 * The final line results in an explicit check that will fail if the type of
 * the underlying data is not actually Type::Document.
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
 */
class MaybeDocument {
 public:
  /**
   * All the different kinds of documents, including MaybeDocument and its
   * subclasses. This is used to provide RTTI for documents. See the docstrings
   * of the subclasses for details.
   */
  enum class Type {
    // An unknown subclass of MaybeDocument. This should never happen.
    //
    // TODO(rsgowman): Since it's no longer possible to directly create
    // MaybeDocument's, we can likely remove this value entirely. But
    // investigate impact on the serializers first.
<<<<<<< HEAD
<<<<<<< HEAD
    Invalid,
=======
    Unknown,
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
    Unknown,
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

    Document,
    NoDocument,
    UnknownDocument,
  };

<<<<<<< HEAD
<<<<<<< HEAD
  MaybeDocument() = default;

  bool is_valid() const {
    return rep_ != nullptr;
=======
  MaybeDocument(DocumentKey key, SnapshotVersion version);

  virtual ~MaybeDocument() {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
  MaybeDocument(DocumentKey key, SnapshotVersion version);

  virtual ~MaybeDocument() {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  }

  /** The runtime type of this document. */
  Type type() const {
<<<<<<< HEAD
<<<<<<< HEAD
    return rep_ ? rep_->type() : Type::Invalid;
  }

  bool is_document() const {
    return type() == Type::Document;
  }

  bool is_no_document() const {
    return type() == Type::NoDocument;
  }

  bool is_unknown_document() const {
    return type() == Type::UnknownDocument;
=======
    return type_;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
    return type_;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  }

  /** The key for this document. */
  const DocumentKey& key() const {
<<<<<<< HEAD
<<<<<<< HEAD
    return rep_->key();
=======
    return key_;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
    return key_;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  }

  /**
   * Returns the version of this document if it exists or a version at which
   * this document was guaranteed to not exist.
   */
  const SnapshotVersion& version() const {
<<<<<<< HEAD
<<<<<<< HEAD
    return rep_->version();
=======
    return version_;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
    return version_;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  }

  /**
   * Whether this document has a local mutation applied that has not yet been
   * acknowledged by Watch.
   */
<<<<<<< HEAD
<<<<<<< HEAD
  bool has_pending_writes() const {
    return rep_->has_pending_writes();
  }

  size_t Hash() const {
    return rep_->Hash();
  }

  std::string ToString() const {
    return rep_->ToString();
  }

  friend std::ostream& operator<<(std::ostream& os, const MaybeDocument& doc);

 protected:
  class Rep {
   public:
    Rep(Type type, DocumentKey&& key, SnapshotVersion version)
        : type_(type), key_(std::move(key)), version_(version) {
    }

    virtual ~Rep() = default;

    Type type() const {
      return type_;
    }

    const DocumentKey& key() const {
      return key_;
    }

    const SnapshotVersion& version() const {
      return version_;
    }

    virtual bool has_pending_writes() const = 0;

    virtual bool Equals(const Rep& other) const;

    virtual size_t Hash() const;

    virtual std::string ToString() const = 0;

   private:
    Type type_ = Type::Invalid;
    DocumentKey key_;
    SnapshotVersion version_;
  };

  explicit MaybeDocument(std::shared_ptr<Rep> rep) : rep_(std::move(rep)) {
  }

  const Rep& rep() const {
    return *rep_;
  }
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  virtual bool HasPendingWrites() const = 0;

 protected:
  // Only allow subclass to set their types.
  void set_type(Type type) {
    type_ = type;
  }

  virtual bool Equals(const MaybeDocument& other) const;
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

  friend bool operator==(const MaybeDocument& lhs, const MaybeDocument& rhs);

 private:
<<<<<<< HEAD
<<<<<<< HEAD
  std::shared_ptr<const Rep> rep_;
};

=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  Type type_ = Type::Unknown;
  DocumentKey key_;
  SnapshotVersion version_;
};

inline bool operator==(const MaybeDocument& lhs, const MaybeDocument& rhs) {
  return lhs.Equals(rhs);
}

<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
inline bool operator!=(const MaybeDocument& lhs, const MaybeDocument& rhs) {
  return !(lhs == rhs);
}

/** Compares against another MaybeDocument by keys only. */
<<<<<<< HEAD
<<<<<<< HEAD
struct DocumentKeyComparator {
=======
struct DocumentKeyComparator : public std::less<MaybeDocument> {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
struct DocumentKeyComparator : public std::less<MaybeDocument> {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  bool operator()(const MaybeDocument& lhs, const MaybeDocument& rhs) const {
    return lhs.key() < rhs.key();
  }
};

}  // namespace model
}  // namespace firestore
}  // namespace firebase

#endif  // FIRESTORE_CORE_SRC_FIREBASE_FIRESTORE_MODEL_MAYBE_DOCUMENT_H_
