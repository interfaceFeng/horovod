// Copyright 2018 Uber Technologies, Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// =============================================================================

#ifndef HOROVOD_HASHES_H
#define HOROVOD_HASHES_H

#include "common.h"
#include <functional>

namespace std {

template <typename T> struct hash<std::vector<T>> {
  typedef std::vector<T> argument_type;
  typedef std::size_t result_type;

  result_type operator()(argument_type const& in) const {
    size_t size = in.size();
    size_t seed = 0;
    for (size_t i = 0; i < size; i++)
      seed ^= std::hash<T>()(in[i]) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    return seed;
  }
};

template <typename U, typename V> struct hash<std::tuple<U, V>> {
  typedef std::tuple<U, V> argument_type;
  typedef std::size_t result_type;

  result_type operator()(argument_type const& in) const {
    size_t seed = 0;
    seed ^= std::hash<U>()(std::get<0>(in)) + 0x9e3779b9 + (seed << 6) +
            (seed >> 2);
    seed ^= std::hash<V>()(std::get<1>(in)) + 0x9e3779b9 + (seed << 6) +
            (seed >> 2);
    return seed;
  }
};

template <> struct hash<horovod::common::Framework> {
  std::size_t operator()(horovod::common::Framework const& in) const {
    return (std::size_t)in;
  }
};

} // namespace std

#endif // HOROVOD_HASHES_H