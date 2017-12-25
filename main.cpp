#include <bits/stdc++.h>
#include <gtest/gtest.h>

using namespace std;

int add(int x, int y){
  return x+y;
}

TEST(AddTest, addDoesAddition){
  int x = 0, y = 1;
  EXPECT_EQ(1, add(x,y));
  EXPECT_EQ(0, add(-1,1));
}

int main(int argc, char** argv){
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
