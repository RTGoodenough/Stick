/**
 * @file databuilder.hpp
 * @author Rolland Goodenough (goodenoughr@gmail.com)
 * @date 2023-03-27
 * 
 * @copyright Copyright 2023 Rolland Goodenough
 * 
 * This file is part of Stick which is released under the MIT License
 * See file LICENSE for the full License
 */

#ifndef STICK_DATABUILDER_HPP
#define STICK_DATABUILDER_HPP

typedef unsigned long size_t;
#include <memory>

namespace Stick {

template <typename T> struct DataInfo {
  size_t size;
  T*     data;
};

template <typename T> class DataBuilder {
 public:
  ~DataBuilder() {}

  DataBuilder(const DataBuilder&) = delete;
  DataBuilder(DataBuilder&&) = delete;
  DataBuilder& operator=(const DataBuilder&) = delete;
  DataBuilder& operator=(DataBuilder&&) = delete;

  DataBuilder() : sz(0), cap(1), data(reinterpret_cast<T*>(std::malloc(sizeof(T)))) {}

  DataBuilder(std::initializer_list<T> initList)
    : sz(initList.size()), cap(initList.size()), data(reinterpret_cast<T*>(std::malloc(initList.size() * sizeof(T)))) {
    for (size_t i = 0; i < sz; ++i) {
      data[i] = *(initList.begin() + i);
    }
  }

  void clean() {
    if (data != nullptr) {
      delete[] data;
    }
  }

  void add(const T& value) {
    if (sz == cap) {
      resize(cap * 2);
    }
    data[sz] = value;
    ++sz;
  }

  constexpr DataInfo<T> get() const { return {sz, data}; }
  constexpr size_t      size() const { return sz; }
  constexpr size_t      capacity() const { return cap; }

  constexpr T*       operator[](size_t index) { return data[index]; }
  constexpr const T* at(size_t index) const { return data[index]; }

 private:
  size_t sz;
  size_t cap;
  T*     data;

  void resize(size_t newCap) {
    if (newCap > cap) {
      T* temp = reinterpret_cast<T*>(std::malloc(2 * sizeof(T)));
      moveAll(data, temp);
      delete[] data;
      data = temp;
    }
    cap = newCap;
  }

  void moveAll(T* from, T* to) {
    for (size_t i = 0; i < sz; ++i) {
      to[i] = from[i];
    }
  }
};
}  // namespace Stick

#endif