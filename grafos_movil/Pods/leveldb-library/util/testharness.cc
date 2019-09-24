// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#include "util/testharness.h"

<<<<<<< HEAD
=======
#include <string>
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

<<<<<<< HEAD
#include <string>
#include <vector>

#include "leveldb/env.h"

=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
namespace leveldb {
namespace test {

namespace {
struct Test {
  const char* base;
  const char* name;
  void (*func)();
};
std::vector<Test>* tests;
<<<<<<< HEAD
}  // namespace

bool RegisterTest(const char* base, const char* name, void (*func)()) {
  if (tests == nullptr) {
=======
}

bool RegisterTest(const char* base, const char* name, void (*func)()) {
  if (tests == NULL) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
    tests = new std::vector<Test>;
  }
  Test t;
  t.base = base;
  t.name = name;
  t.func = func;
  tests->push_back(t);
  return true;
}

int RunAllTests() {
  const char* matcher = getenv("LEVELDB_TESTS");

  int num = 0;
<<<<<<< HEAD
  if (tests != nullptr) {
    for (size_t i = 0; i < tests->size(); i++) {
      const Test& t = (*tests)[i];
      if (matcher != nullptr) {
        std::string name = t.base;
        name.push_back('.');
        name.append(t.name);
        if (strstr(name.c_str(), matcher) == nullptr) {
=======
  if (tests != NULL) {
    for (size_t i = 0; i < tests->size(); i++) {
      const Test& t = (*tests)[i];
      if (matcher != NULL) {
        std::string name = t.base;
        name.push_back('.');
        name.append(t.name);
        if (strstr(name.c_str(), matcher) == NULL) {
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
          continue;
        }
      }
      fprintf(stderr, "==== Test %s.%s\n", t.base, t.name);
      (*t.func)();
      ++num;
    }
  }
  fprintf(stderr, "==== PASSED %d tests\n", num);
  return 0;
}

std::string TmpDir() {
  std::string dir;
  Status s = Env::Default()->GetTestDirectory(&dir);
  ASSERT_TRUE(s.ok()) << s.ToString();
  return dir;
}

int RandomSeed() {
  const char* env = getenv("TEST_RANDOM_SEED");
<<<<<<< HEAD
  int result = (env != nullptr ? atoi(env) : 301);
=======
  int result = (env != NULL ? atoi(env) : 301);
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  if (result <= 0) {
    result = 301;
  }
  return result;
}

}  // namespace test
}  // namespace leveldb
