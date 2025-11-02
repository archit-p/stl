#include "src/vector/vector.h"

#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"

namespace {

TEST(TextVector, Constructors) {
  // default
  ds::vector<int> v1;
  EXPECT_EQ(v1.size(), 0);

  // size
  ds::vector<int> v2(3);
  EXPECT_EQ(v2.size(), 3);

  v2[0] = 1;
  v2[1] = 2;
  v2[2] = 3;

  // initializer list
  EXPECT_EQ(v2, ds::vector<int>({1, 2, 3}));

  // default values
  ds::vector<int> v3(3, 0);
  EXPECT_EQ(v3, ds::vector<int>({0, 0, 0}));

  // copy
  ds::vector<int> v4 = v3;
  EXPECT_EQ(v4, ds::vector<int>({0, 0, 0}));

  // move
  ds::vector<int> v5 = std::move(v4);
  EXPECT_EQ(v5, ds::vector<int>({0, 0, 0}));
}

TEST(TestVector, PushBack) {
  ds::vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);

  EXPECT_EQ(v, ds::vector<int>({1, 2, 3}));
}

TEST(TestVector, PopBack) {
  ds::vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.pop_back();

  EXPECT_EQ(v, ds::vector<int>({1}));
}

TEST(TestVector, Front) {
  ds::vector<int> v({1, 2, 3});
  EXPECT_EQ(v.front(), 1);
}

TEST(TestVector, Back) {
  ds::vector<int> v({1, 2, 3});
  EXPECT_EQ(v.back(), 3);
}

TEST(TestVector, Output) {
  ds::vector<int> v({1, 2, 3});
  std::stringstream ss;
  ss << v;
  EXPECT_EQ(ss.str(), "[1,2,3]");
}

}  // namespace
