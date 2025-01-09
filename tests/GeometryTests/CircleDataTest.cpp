#include <gtest/gtest.h>
#include "../../src/Geometries/CircleData.hpp"

TEST(CircleDataTest, PointConstructorTest) {
  Point p;
  EXPECT_EQ(p.x, 0);
  EXPECT_EQ(p.y, 0);

  Point p1(1,2);
  EXPECT_EQ(p1.x, 1);
  EXPECT_EQ(p1.y, 2);
}

TEST(CircleDataTest, PointEqualsOperatorTest) {
  Point p0(1,2);
  Point p1(1,2);
  Point p2(2,1);
  Point p3(5,2);

  EXPECT_TRUE(p0==p1);
  EXPECT_FALSE(p0==p2);
  EXPECT_FALSE(p1==p3);
}

TEST(CircleDataTest, CircleDataConstructorTest) {
  CircleData cd(Point(1,2),4);
  
  EXPECT_EQ(cd.GetCenterPoint().x,1);
  EXPECT_EQ(cd.GetCenterPoint().y,2);
  EXPECT_EQ(cd.GetRadius(),4);
}

TEST(CircleDataTest, CircleDataSetTest) {
  CircleData cd(Point(1,2),4);
  cd.SetCenterPoint(Point(2,1));
  EXPECT_EQ(cd.GetCenterPoint().x,2);
  EXPECT_EQ(cd.GetCenterPoint().y,1);
  cd.SetRadius(1);
  EXPECT_EQ(cd.GetRadius(),1);
}

TEST(CircleDataTest, CircleDataOperatorsTest) {
  CircleData cd1(Point(1,2),4);
  CircleData cd2(Point(1,2),4);

  EXPECT_TRUE(cd1==cd2);
  cd1 = CircleData(Point(1,2),5);
  EXPECT_FALSE(cd1==cd2);
}

