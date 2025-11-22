#include "src/list/list.h"

#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"

namespace {

ds::List<int> CreateSampleList(int size) {
  ds::List<int> l;
  for (int i = 0; i < size; i++) {
    l.push_back(i);
  }

  return l;
}

TEST(TestList, Constructors) {
  ds::List<int> l = CreateSampleList(3);

  std::cout << l << '\n';

  ds::List<int> l2 = l;
  std::cout << l2 << '\n';

  ds::List<int> l3 = std::move(l);
  std::cout << l3 << '\n';

  ds::List<int> l4;
  for (int i = 0; i < 3; i++) {
    l4.push_front(i);
  }

  EXPECT_EQ(l4, ds::List<int>({2, 1, 0}));
}

TEST(TestList, Limits) {
  ds::List<int> l = CreateSampleList(100000);
  EXPECT_EQ(l.size(), 100000);
  EXPECT_EQ(l.front(), 0);
  EXPECT_EQ(l.back(), 99999);
}

}  // namespace
