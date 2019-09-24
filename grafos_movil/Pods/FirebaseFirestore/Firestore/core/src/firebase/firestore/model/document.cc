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

#include "Firestore/core/src/firebase/firestore/model/document.h"

<<<<<<< HEAD
<<<<<<< HEAD
#include <ostream>
#include <sstream>
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#include <utility>

#include "Firestore/core/src/firebase/firestore/util/hard_assert.h"

namespace firebase {
namespace firestore {
namespace model {

<<<<<<< HEAD
<<<<<<< HEAD
static_assert(
    sizeof(MaybeDocument) == sizeof(Document),
    "Document may not have additional members (everything goes in Rep)");

class Document::Rep : public MaybeDocument::Rep {
 public:
  Rep(ObjectValue&& data,
      DocumentKey&& key,
      SnapshotVersion version,
      DocumentState document_state)
      : MaybeDocument::Rep(Type::Document, std::move(key), version),
        data_(std::move(data)),
        document_state_(document_state) {
  }

  Rep(ObjectValue&& data,
      DocumentKey&& key,
      SnapshotVersion version,
      DocumentState document_state,
      absl::any proto)
      : Rep(std::move(data), std::move(key), version, document_state) {
    proto_ = std::move(proto);
  }

  const ObjectValue& data() const {
    return data_;
  }

  DocumentState document_state() const {
    return document_state_;
  }

  bool has_local_mutations() const {
    return document_state_ == DocumentState::kLocalMutations;
  }

  bool has_committed_mutations() const {
    return document_state_ == DocumentState::kCommittedMutations;
  }

  bool has_pending_writes() const override {
    return has_local_mutations() || has_committed_mutations();
  }

  bool Equals(const MaybeDocument::Rep& other) const override {
    if (!MaybeDocument::Rep::Equals(other)) return false;

    const auto& other_rep = static_cast<const Rep&>(other);
    return document_state_ == other_rep.document_state_ &&
           data_ == other_rep.data_;
  }

  size_t Hash() const override {
    return util::Hash(MaybeDocument::Rep::Hash(), data_, document_state_);
  }

  std::string ToString() const override {
    return absl::StrCat(
        "Document(key=", key().ToString(), ", version=", version().ToString(),
        ", document_state=", document_state_, ", data=", data_.ToString(), ")");
  }

 private:
  friend class Document;

  ObjectValue data_;
  DocumentState document_state_;
  absl::any proto_;
};

Document::Document(ObjectValue data,
                   DocumentKey key,
                   SnapshotVersion version,
                   DocumentState document_state)
    : MaybeDocument(std::make_shared<Rep>(
          std::move(data), std::move(key), version, document_state)) {
}

Document::Document(ObjectValue data,
                   DocumentKey key,
                   SnapshotVersion version,
                   DocumentState document_state,
                   absl::any proto)
    : MaybeDocument(std::make_shared<Rep>(std::move(data),
                                          std::move(key),
                                          version,
                                          document_state,
                                          std::move(proto))) {
}

Document::Document(const MaybeDocument& document) : MaybeDocument(document) {
  HARD_ASSERT(type() == Type::Document);
}

const ObjectValue& Document::data() const {
  return doc_rep().data();
}

absl::optional<FieldValue> Document::field(const FieldPath& path) const {
  return data().Get(path);
}

DocumentState Document::document_state() const {
  return doc_rep().document_state_;
}

bool Document::has_local_mutations() const {
  return doc_rep().has_local_mutations();
}

bool Document::has_committed_mutations() const {
  return doc_rep().has_committed_mutations();
}

const absl::any& Document::proto() const {
  return doc_rep().proto_;
}

const Document::Rep& Document::doc_rep() const {
  return static_cast<const Rep&>(MaybeDocument::rep());
}

std::ostream& operator<<(std::ostream& os, DocumentState state) {
  switch (state) {
    case DocumentState::kCommittedMutations:
      return os << "kCommittedMutations";
    case DocumentState::kLocalMutations:
      return os << "kLocalMutations";
    case DocumentState::kSynced:
      return os << "kLocalSynced";
  }

  UNREACHABLE();
}

std::ostream& operator<<(std::ostream& os, const Document& doc) {
  return os << doc.doc_rep().ToString();
}

/** Compares against another Document. */
bool operator==(const Document& lhs, const Document& rhs) {
  return lhs.doc_rep().Equals(rhs.doc_rep());
=======
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
Document::Document(ObjectValue&& data,
                   DocumentKey key,
                   SnapshotVersion version,
                   DocumentState document_state)
    : MaybeDocument(std::move(key), std::move(version)),
      data_(std::move(data)),
      document_state_(document_state) {
  set_type(Type::Document);
}

bool Document::Equals(const MaybeDocument& other) const {
  if (other.type() != Type::Document) {
    return false;
  }
  auto& other_doc = static_cast<const Document&>(other);
  return MaybeDocument::Equals(other) &&
         document_state_ == other_doc.document_state_ &&
         data_ == other_doc.data_;
<<<<<<< HEAD
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
}

}  // namespace model
}  // namespace firestore
}  // namespace firebase
