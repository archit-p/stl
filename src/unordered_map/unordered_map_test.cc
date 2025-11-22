#include "src/unordered_map/unordered_map.h"

#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"

namespace {

TEST(TestUnorderedMap, Constructors) {
  ds::unordered_map<int, int> m;
  for (int i = 0; i < 100000; i++) {
    m[i * 100000] = i;
  }

  EXPECT_EQ(m.contains(0), true);
  EXPECT_EQ(m.size(), 100000);
}

}  // namespace
