#ifndef VECTOR
#define VECTOR

#include <ostream>

namespace ds {

template <typename T>
class vector {
 public:
  vector() : size_(0), capacity_(0), elements_{NULL} {}

  vector(int size) : size_(size), capacity_(size), elements_{new T[size]} {}

  vector(int size, T val) : vector(size) {
    for (int i = 0; i < this->size_; i++) {
      this->elements_[i] = val;
    }
  }

  vector(std::initializer_list<T> init) : vector(init.size()) {
    int i = 0;
    for (const T& elem : init) {
      elements_[i++] = elem;
    }
  }

  // copy
  vector(const vector<T>& other)
      : size_(other.size_),
        capacity_(other.capacity_),
        elements_(new T[capacity_]) {
    for (int i = 0; i < size_; i++) {
      elements_[i] = other.elements_[i];
    }
  }

  // move
  vector(vector<T>&& other) {
    size_ = other.size_;
    capacity_ = other.capacity_;
    elements_ = other.elements_;
    other.elements_ = NULL;
  }

  ~vector() { delete[] elements_; }

  void push_back(T element) {
    if (size_ == capacity_) {
      reserve(2 * capacity_ + 1);
    }

    elements_[size_++] = element;
  }

  void pop_back() { --size_; }

  T& operator[](int index) { return elements_[index]; }

  bool operator==(const vector<T>& other) const {
    for (int i = 0; i < std::min(size_, other.size_); i++) {
      if (elements_[i] != other.elements_[i]) {
        return false;
      }
    }

    return size_ == other.size_;
  }

  friend std::ostream& operator<<(std::ostream& os, const vector<T>& v) {
    os << '[';
    for (int i = 0; i < v.size() - 1; i++) {
      os << v[i] << ',';
    }

    if (v.size()) {
      os << v.back();
    }
    os << ']';
    return os;
  }

  const T& operator[](int index) const { return elements_[index]; }

  const int size() const { return size_; }

  const bool empty() const { return size_ == 0; }

  T front() const { return elements_[0]; }

  T back() const { return elements_[size_ - 1]; }

  T* data() { return elements_; }

  vector& operator=(const vector& other) {
    if (this == &other) {
      return *this;
    }

    capacity_ = other.capacity_;
    size_ = other.size_;

    delete[] elements_;

    elements_ = new T[capacity_];
    for (int i = 0; i < capacity_; i++) {
      elements_[i] = other.elements_[i];
    }

    return *this;
  }

  vector& operator=(vector&& other) {
    if (this == &other) {
      return *this;
    }

    capacity_ = other.capacity_;
    size_ = other.size_;

    delete[] elements_;
    elements_ = other.elements_;

    other.elements_ = NULL;

    return *this;
  }

 private:
  void reserve(int capacity) {
    if (capacity <= capacity_) {
      return;
    }

    T* successor = new T[capacity];
    for (int i = 0; i < size_; i++) {
      successor[i] = std::move(elements_[i]);
    }

    std::swap(elements_, successor);
    delete[] successor;
    capacity_ = capacity;
  }

  int size_;
  int capacity_;
  T* elements_;
};

}  // namespace ds

#endif
