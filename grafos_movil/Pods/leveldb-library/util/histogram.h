// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#ifndef STORAGE_LEVELDB_UTIL_HISTOGRAM_H_
#define STORAGE_LEVELDB_UTIL_HISTOGRAM_H_

#include <string>

namespace leveldb {

class Histogram {
 public:
<<<<<<< HEAD
  Histogram() {}
  ~Histogram() {}
=======
  Histogram() { }
  ~Histogram() { }
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

  void Clear();
  void Add(double value);
  void Merge(const Histogram& other);

  std::string ToString() const;

 private:
<<<<<<< HEAD
  enum { kNumBuckets = 154 };

  double Median() const;
  double Percentile(double p) const;
  double Average() const;
  double StandardDeviation() const;

  static const double kBucketLimit[kNumBuckets];

=======
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
  double min_;
  double max_;
  double num_;
  double sum_;
  double sum_squares_;

<<<<<<< HEAD
  double buckets_[kNumBuckets];
=======
  enum { kNumBuckets = 154 };
  static const double kBucketLimit[kNumBuckets];
  double buckets_[kNumBuckets];

  double Median() const;
  double Percentile(double p) const;
  double Average() const;
  double StandardDeviation() const;
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
};

}  // namespace leveldb

#endif  // STORAGE_LEVELDB_UTIL_HISTOGRAM_H_
