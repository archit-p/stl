#ifndef STL_QUEUE
#define STL_QUEUE

#include <utility>

namespace ds {

template <typename T>
class queue {
 public:
  /* constructors */
  queue() : start_{0}, end_{0}, capacity_{0}, elements_{NULL} {}

  // copy
  queue(queue<T>& other)
      : start_{other.start_},
        end_{other.end_},
        capacity_{other.capacity_},
        elements_{new T[capacity_]} {
    for (int i = 0; i < end_; i++) {
      elements_[i] = other.elements_[i];
    }
  }

  // move
  queue(queue<T>&& other)
      : start_{other.start_},
        end_{other.end_},
        capacity_{other.capacity_},
        elements_{other.elements_} {
    other.elements_ = NULL;
  }

  queue(const std::initializer_list<T>& init)
      : start_{0},
        end_{init.size()},
        capacity_{init.size()},
        elements_{new T[capacity_]} {
    int i = 0;
    for (const T& ele : init) {
      elements_[i++] = ele;
    }
  }

  /* destructors */
  ~queue() { delete[] elements_; }

  /* modifiers */
  void push(const T& val) {
    if (end_ == capacity_) {
      reserve(2 * capacity_ + 1);
    }

    elements_[end_++] = val;
  }

  void pop() {
    if (end_ == start_) {
      return;
    }

    ++start_;
  }

  /* accessors */
  T& front() { return elements_[start_]; }

  T& back() { return elements_[end_ - 1]; }

  int size() { return end_ - start_; }

  bool empty() { return end_ == start_; }

  /* operators */
  bool operator==(const queue<T>& other) const {
    if (end_ - start_ != other.end_ - other.start_) {
      return false;
    }

    for (int i = start_, j = other.start_; i < end_ && j < other.end_;
         i++, j++) {
      if (elements_[i] != other.elements_[j]) {
        return false;
      }
    }

    return true;
  }

 private:
  void reserve(int capacity) {
    if (capacity <= capacity_) {
      return;
    }

    // copy elements to start of new memory
    T* temp = new T[capacity];
    for (int i = start_, j = 0; i < end_; i++, j++) {
      temp[j] = std::move(elements_[i]);
    }

    std::swap(elements_, temp);
    delete[] temp;
    capacity_ = capacity;
    end_ = end_ - start_;
    start_ = 0;
  }

  size_t start_;
  size_t end_;
  size_t capacity_;
  T* elements_;
};

}  // namespace ds

#endif
