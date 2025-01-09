#include <gtest/gtest.h>
#include "../../src/Geometries/CircleFactory.hpp"
#include "../../src/Geometries/CircleData.hpp"
#include "../../src/Geometries/IGeometry.hpp"

class CircleFactoryFixture : public testing::Test{
    public:
        void SetUp() override{
            Point cp = Point(1,2);
            double radius = 2;
            circle_data = CircleData(cp, radius);
            
            circle1 = circle_factory.CreateObject(circle_data);
            
            circle_data.SetCenterPoint(Point(1,1));
            circle_data.SetRadius(2);
            
            circle2 = circle_factory.CreateObject(circle_data);
        }
    
        CircleData circle_data;
        CircleFactory circle_factory;
        std::shared_ptr<IGeometry<CircleData>> circle1;
        std::shared_ptr<IGeometry<CircleData>> circle2;
};

TEST_F(CircleFactoryFixture, CircleOperatorTest){
    EXPECT_FALSE(circle1 == circle2);
    EXPECT_TRUE(circle1->GetCenterPoint().x == circle2->GetCenterPoint().x);
}

TEST_F(CircleFactoryFixture, CircleIntersectionTest){
    EXPECT_TRUE(circle1->IsIntersect(circle2.get()));
    circle1->SetCenterPoint(Point(5,5));
    EXPECT_FALSE(circle1->IsIntersect(circle2.get()));
}

TEST_F(CircleFactoryFixture, CircleInsideCircleTest){
    circle1->SetCenterPoint(Point(1,1));
    circle1->GetGeometryData().SetRadius(1);
    circle2->SetCenterPoint(Point(1,1));
    circle1->GetGeometryData().SetRadius(3);

    EXPECT_TRUE(circle1->IsIntersect(circle2.get()));
}

TEST_F(CircleFactoryFixture, CircleMoveTest){
    circle1->SetCenterPoint(Point(1,1));
    circle1->GetGeometryData().SetRadius(1);
    circle2->SetCenterPoint(Point(1,1));
    circle1->GetGeometryData().SetRadius(3);
    EXPECT_TRUE(circle1->IsIntersect(circle2.get()));
    circle1->Move(circle2.get());
    EXPECT_FALSE(circle1->IsIntersect(circle2.get()));
}


TEST(CircleFactoryTest, MakeCircleTest){
    Point cp = Point(1,2);
    double radius = 4;
    CircleData circle_data(cp, radius);
    CircleFactory circle_factory;
    auto circle = circle_factory.CreateObject(circle_data);
    
    EXPECT_EQ(cp, circle->GetCenterPoint());
    EXPECT_EQ(radius, circle->GetGeometryData().GetRadius());
}
