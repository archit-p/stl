#ifndef STL_LIST
#define STL_LIST

#include <iostream>
#include <memory>
#include <ostream>

namespace ds {

template <typename T>
class List {
 private:
  class Node;

 public:
  List() : start_{NULL}, end_{NULL}, size_{0} {}

  ~List() { clear(); }

  // copy
  List(const List& other) : List() {
    for (const T& element : other) {
      push_back(element);
    }
  }

  // move
  List(List&& other)
      : start_{other.start_}, end_{other.end_}, size_{other.size_} {
    std::cout << "Move constructor called\n";
    other.start_ = NULL;
    other.end_ = NULL;
  }

  List(std::initializer_list<T> init) : List() {
    for (const T& element : init) {
      push_back(element);
    }
  }

  List& operator=(const List& other) {
    if (this == &other) {
      return *this;
    }

    clear();

    for (const T& element : other) {
      push_back(element);
    }

    return *this;
  }

  // move assignment
  List& operator=(const List&& other) {
    std::cout << "Move assignment operator called\n";
    if (this == &other) {
      return *this;
    }

    start_ = other.start_;
    end_ = other.end_;
    size_ = other.size_;

    other.start_ = NULL;
    other.end_ = NULL;

    return *this;
  }

  bool operator==(const List& other) const {
    std::cout << "Equality check\n";
    auto l = this->begin();
    auto r = other.begin();
    for (; l != this->end() && r != other.end(); l++, r++) {
      if (*l != *r) return false;
    }

    return l == this->end() && r == other.end();
  }

  class Iterator {
   public:
    Iterator(Node* node) : curr_{node} {}

    Iterator& operator++() {
      curr_ = curr_->next_;
      return *this;
    }

    Iterator& operator++(int) {
      Iterator& temp = *this;
      curr_ = curr_->next_;
      return temp;
    }

    Iterator& operator--() { curr_ = curr_->prev_; }

    T& operator*() { return curr_->element_; }

    bool operator!=(const Iterator& other) const {
      return curr_ != other.curr_;
    }

    bool operator==(const Iterator& other) const {
      return curr_ == other.curr_;
    }

   private:
    Node* curr_;
  };

  void push_back(const T& val) {
    size_++;
    if (start_ == NULL) {
      start_ = new Node(val, NULL, NULL);
      end_ = start_;
      return;
    }

    end_->next_ = new Node(val, end_, NULL);
    end_ = end_->next_;
  }

  void push_front(const T& val) {
    size_++;
    if (start_ == NULL) {
      start_ = new Node(val, NULL, NULL);
      end_ = start_;
      return;
    }

    Node* temp = new Node(val, NULL, start_);
    start_ = temp;
  }

  friend std::ostream& operator<<(std::ostream& os, const List<T>& l) {
    os << '[';
    for (const T& i : l) {
      os << i << ',';
    }
    os << ']';
    return os;
  }

  void erase(const Iterator& it) {
    if (it.curr_ == NULL) {
      return;
    }

    Node* prev = it.curr_->prev_;
    Node* next = it.curr_->next_;
    prev->next_ = next;
    next->prev_ = prev;

    delete it.curr_;
  }

  Iterator begin() { return Iterator(start_); }

  const Iterator begin() const { return Iterator(start_); }

  Iterator end() { return Iterator(NULL); }

  const Iterator end() const { return Iterator(NULL); }

  T& front() { return start_->element_; }

  const T& front() const { return start_->element_; }

  T& back() { return end_->element_; }

  const T& back() const { return end_->element_; }

  size_t size() const { return size_; }

 private:
  void clear() {
    Node* curr = start_;
    while (curr != NULL) {
      Node* temp = curr->next_;
      delete curr;
      curr = temp;
    }

    start_ = NULL;
    end_ = NULL;
    size_ = 0;
  }

  class Node {
   public:
    Node() : prev_{NULL}, next_{NULL} {}

    Node(const T& element) : prev_{NULL}, next_{NULL}, element_{element} {}

    Node(const T& element, Node* prev, Node* next)
        : prev_{prev}, next_{next}, element_{element} {}

    Node* prev_;
    Node* next_;
    T element_;
  };

  Node* start_;
  Node* end_;
  size_t size_;
};

}  // namespace ds
#endif
