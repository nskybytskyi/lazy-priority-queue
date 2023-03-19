#include <gtest/gtest.h>

#include <cassert>
#include <deque>
#include <functional>
#include <string>
#include <vector>

#include "lib.hpp"

TEST(InterfaceTest, BasicAssertions) {
  lazy_priority_queue<int> queue;
  EXPECT_EQ(queue.size(), 0);
  EXPECT_TRUE(queue.empty());

  queue.push(1);
  EXPECT_EQ(queue.size(), 1);
  ASSERT_FALSE(queue.empty());
  EXPECT_EQ(queue.top(), 1);

  queue.push(3);
  EXPECT_EQ(queue.size(), 2);
  ASSERT_FALSE(queue.empty());
  EXPECT_EQ(queue.top(), 3);

  queue.push(2);
  EXPECT_EQ(queue.size(), 3);
  ASSERT_FALSE(queue.empty());
  EXPECT_EQ(queue.top(), 3);

  queue.erase(2);
  EXPECT_EQ(queue.size(), 2);
  ASSERT_FALSE(queue.empty());
  EXPECT_EQ(queue.top(), 3);

  queue.pop();
  EXPECT_EQ(queue.size(), 1);
  ASSERT_FALSE(queue.empty());
  EXPECT_EQ(queue.top(), 1);

  queue.pop();
  EXPECT_TRUE(queue.empty());
  EXPECT_EQ(queue.size(), 0);
}

TEST(InterfaceTest, ProxiedContainers) {
  lazy_priority_queue<bool> queue;
  EXPECT_TRUE(queue.empty());
  EXPECT_EQ(queue.size(), 0);

  queue.push(false);
  EXPECT_EQ(queue.size(), 1);
  ASSERT_FALSE(queue.empty());
  EXPECT_FALSE(queue.top());

  queue.push(true);
  EXPECT_EQ(queue.size(), 2);
  ASSERT_FALSE(queue.empty());
  EXPECT_TRUE(queue.top());

  queue.push(false);
  EXPECT_EQ(queue.size(), 3);
  ASSERT_FALSE(queue.empty());
  EXPECT_TRUE(queue.top());

  queue.erase(false);
  ASSERT_FALSE(queue.empty());
  EXPECT_EQ(queue.size(), 2);
  EXPECT_TRUE(queue.top());

  queue.pop();
  ASSERT_FALSE(queue.empty());
  EXPECT_EQ(queue.size(), 1);
  EXPECT_FALSE(queue.top());

  queue.pop();
  EXPECT_TRUE(queue.empty());
  EXPECT_EQ(queue.size(), 0);
}

TEST(InterfaceTest, ValueType) {
  lazy_priority_queue<std::string> queue;
  EXPECT_TRUE(queue.empty());
  EXPECT_EQ(queue.size(), 0);

  queue.push("hello");
  EXPECT_EQ(queue.size(), 1);
  ASSERT_FALSE(queue.empty());
  EXPECT_EQ(queue.top(), "hello");

  queue.push("world");
  EXPECT_EQ(queue.size(), 2);
  ASSERT_FALSE(queue.empty());
  EXPECT_EQ(queue.top(), "world");

  queue.push("nicky");
  EXPECT_EQ(queue.size(), 3);
  ASSERT_FALSE(queue.empty());
  EXPECT_EQ(queue.top(), "world");

  queue.erase("nicky");
  EXPECT_EQ(queue.size(), 2);
  ASSERT_FALSE(queue.empty());
  EXPECT_EQ(queue.top(), "world");

  queue.pop();
  EXPECT_EQ(queue.size(), 1);
  ASSERT_FALSE(queue.empty());
  EXPECT_EQ(queue.top(), "hello");

  queue.pop();
  EXPECT_TRUE(queue.empty());
  EXPECT_EQ(queue.size(), 0);
}

TEST(InterfaceTest, Container) {
  lazy_priority_queue<int, std::deque<int>> queue;
  EXPECT_TRUE(queue.empty());
  EXPECT_EQ(queue.size(), 0);

  queue.push(1);
  EXPECT_EQ(queue.size(), 1);
  ASSERT_FALSE(queue.empty());
  EXPECT_EQ(queue.top(), 1);

  queue.push(3);
  EXPECT_EQ(queue.size(), 2);
  ASSERT_FALSE(queue.empty());
  EXPECT_EQ(queue.top(), 3);

  queue.push(2);
  EXPECT_EQ(queue.size(), 3);
  ASSERT_FALSE(queue.empty());
  EXPECT_EQ(queue.top(), 3);

  queue.erase(2);
  EXPECT_EQ(queue.size(), 2);
  ASSERT_FALSE(queue.empty());
  EXPECT_EQ(queue.top(), 3);

  queue.pop();
  EXPECT_EQ(queue.size(), 1);
  ASSERT_FALSE(queue.empty());
  EXPECT_EQ(queue.top(), 1);

  queue.pop();
  EXPECT_TRUE(queue.empty());
  EXPECT_EQ(queue.size(), 0);
}

TEST(InterfaceTest, Compare) {
  lazy_priority_queue<int, std::vector<int>, std::greater<int>> queue;
  EXPECT_TRUE(queue.empty());
  EXPECT_EQ(queue.size(), 0);

  queue.push(3);
  EXPECT_EQ(queue.size(), 1);
  ASSERT_FALSE(queue.empty());
  EXPECT_EQ(queue.top(), 3);

  queue.push(1);
  EXPECT_EQ(queue.size(), 2);
  ASSERT_FALSE(queue.empty());
  EXPECT_EQ(queue.top(), 1);

  queue.push(2);
  EXPECT_EQ(queue.size(), 3);
  ASSERT_FALSE(queue.empty());
  EXPECT_EQ(queue.top(), 1);

  queue.erase(2);
  EXPECT_EQ(queue.size(), 2);
  ASSERT_FALSE(queue.empty());
  EXPECT_EQ(queue.top(), 1);

  queue.pop();
  EXPECT_EQ(queue.size(), 1);
  ASSERT_FALSE(queue.empty());
  EXPECT_EQ(queue.top(), 3);

  queue.pop();
  EXPECT_TRUE(queue.empty());
  EXPECT_EQ(queue.size(), 0);
}