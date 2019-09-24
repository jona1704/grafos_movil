// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

<<<<<<< HEAD
<<<<<<< HEAD
#include "util/hash.h"

#include <string.h>

#include "util/coding.h"
=======
#include <string.h>
#include "util/coding.h"
#include "util/hash.h"
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
#include <string.h>
#include "util/coding.h"
#include "util/hash.h"
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254

// The FALLTHROUGH_INTENDED macro can be used to annotate implicit fall-through
// between switch labels. The real definition should be provided externally.
// This one is a fallback version for unsupported compilers.
#ifndef FALLTHROUGH_INTENDED
<<<<<<< HEAD
<<<<<<< HEAD
#define FALLTHROUGH_INTENDED \
  do {                       \
  } while (0)
=======
#define FALLTHROUGH_INTENDED do { } while (0)
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======
#define FALLTHROUGH_INTENDED do { } while (0)
>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
#endif

namespace leveldb {

uint32_t Hash(const char* data, size_t n, uint32_t seed) {
  // Similar to murmur hash
  const uint32_t m = 0xc6a4a793;
  const uint32_t r = 24;
  const char* limit = data + n;
  uint32_t h = seed ^ (n * m);

  // Pick up four bytes at a time
  while (data + 4 <= limit) {
    uint32_t w = DecodeFixed32(data);
    data += 4;
    h += w;
    h *= m;
    h ^= (h >> 16);
  }

  // Pick up remaining bytes
  switch (limit - data) {
    case 3:
      h += static_cast<unsigned char>(data[2]) << 16;
      FALLTHROUGH_INTENDED;
    case 2:
      h += static_cast<unsigned char>(data[1]) << 8;
      FALLTHROUGH_INTENDED;
    case 1:
      h += static_cast<unsigned char>(data[0]);
      h *= m;
      h ^= (h >> r);
      break;
  }
  return h;
}

<<<<<<< HEAD
<<<<<<< HEAD
=======

>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
=======

>>>>>>> 8990fd99b9c866a4e223da4e70190964eb1a9254
}  // namespace leveldb
