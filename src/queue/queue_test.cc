#include "src/queue/queue.h"

#include "gmock/gmock-matchers.h"
#include "gtest/gtest.h"

namespace {

TEST(TestQueue, Constructors) {
  ds::queue<int> q1;
  EXPECT_EQ(q1.size(), 0);

  ds::queue<int> q2({1, 2, 3});

  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.size(), 3);

  ds::queue<int> q3 = q2;

  EXPECT_EQ(q3.front(), 1);
  EXPECT_EQ(q3.size(), 3);

  ds::queue<int> q4 = std::move(q3);
  EXPECT_EQ(q4.front(), 1);
  EXPECT_EQ(q4.size(), 3);
}

TEST(TestQueue, PushPop) {
  ds::queue<int> q({1, 2, 3});
  q.pop();
  q.pop();
  q.pop();
  EXPECT_EQ(q.size(), 0);

  q.push(4);
  q.push(5);
  q.push(6);

  EXPECT_EQ(q, ds::queue<int>({4, 5, 6}));
}

}  // namespace
