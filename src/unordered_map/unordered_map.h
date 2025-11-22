#ifndef STL_UNORDERED_MAP
#define STL_UNORDERED_MAP

#include <functional>
#include <iostream>
#include <list>

#include "src/list/list.h"
#include "src/vector/vector.h"

namespace ds {

template <typename K, typename V>
class unordered_map {
  using ElementType = std::pair<K, V>;
  using ListType = ds::List<ElementType>;
  using VectorType = ds::vector<ListType>;

 public:
  unordered_map() : size_{0}, nodes_{VectorType()} {}

  V& operator[](const K& key) {
    if (size_ >= 0.7 * nodes_.size()) {
      rehash();
    }

    size_t index = get_index(key);
    for (ElementType& element : nodes_[index]) {
      if (element.first == key) {
        return element.second;
      }
    }

    nodes_[index].push_back(ElementType({key, V{}}));
    ++size_;

    return nodes_[index].back().second;
  }

  bool contains(const K& key) {
    size_t index = get_index(key);
    for (const ElementType& element : nodes_[index]) {
      if (element.first == key) {
        return true;
      }
    }

    return false;
  }

  size_t size() { return size_; }

  class Iterator {
   private:
    size_t index_;
    typename ds::List<std::pair<K, V>>::Iterator it;
  };

  Iterator begin() { return Iterator(); }

  const Iterator begin() const { return Iterator(); }

  Iterator end() { return Iterator(); }

  const Iterator end() const { return Iterator(); }

 private:
  size_t get_index(const K& key) { return hash_(key) % nodes_.size(); }

  void rehash() {
    VectorType temp = VectorType(2 * nodes_.size() + 1);
    for (int i = 0; i < nodes_.size(); ++i) {
      const ListType& node = nodes_[i];
      for (const ElementType& element : node) {
        size_t ti = hash_(element.first) % temp.size();
        temp[ti].push_back(element);
      }
    }

    nodes_ = std::move(temp);
  }

  size_t size_;
  std::hash<K> hash_;
  VectorType nodes_;
};
}  // namespace ds

#endif
