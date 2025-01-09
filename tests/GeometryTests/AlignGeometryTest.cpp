#include <gtest/gtest.h>
#include "../../src/Geometries/CircleFactory.hpp"
#include "../../src/Geometries/CircleData.hpp"
#include "../../src/Geometries/IGeometry.hpp"
#include "../../src/Geometries/GeometryHelper.hpp"
#include "../../src/Geometries/Logger.hpp"

class AlignGeometriesFixture : public testing::Test{
    public:
        using GeometryVector = std::vector<std::shared_ptr<IGeometry<CircleData>>>;

        void SetUp() override{
            Point cp = Point(0,0);
            double radius = 1;
            m_circle_data = CircleData(cp, radius);
            
            m_geometries_down.push_back(m_circle_factory.CreateObject(m_circle_data));
            m_circle_data.SetCenterPoint(Point(1,-1));
            m_geometries_down.push_back(m_circle_factory.CreateObject(m_circle_data));
            m_circle_data.SetCenterPoint(Point(1,1));
            m_geometries_down.push_back(m_circle_factory.CreateObject(m_circle_data));

            m_circle_data.SetCenterPoint(Point(3,5));
            m_geometries_up.push_back(m_circle_factory.CreateObject(m_circle_data));
            m_circle_data.SetCenterPoint(Point(5,4));
            m_geometries_up.push_back(m_circle_factory.CreateObject(m_circle_data));
            m_circle_data.SetCenterPoint(Point(4,14));
            m_geometries_up.push_back(m_circle_factory.CreateObject(m_circle_data));
            
        }
    
        CircleData m_circle_data;
        CircleFactory m_circle_factory;
        GeometryVector m_geometries_down;
        GeometryVector m_geometries_up;
        GeometryHelper<CircleData> m_GH;
};


TEST_F(AlignGeometriesFixture, AlignGeometriesTest)
{
    Logger<CircleData> my_log("/Users/robertjelic/Documents/C++/Ellipses/tests/GeometryTests/CSV_Files/", "AlignGeometries.txt");
    my_log.LogVectorData(m_geometries_down);
    my_log.InsertEmptyLine();
    my_log.LogVectorData(m_geometries_up);
    my_log.InsertEmptyLine();

    m_GH.AllignGeometries(m_geometries_up,m_geometries_down);
    my_log.LogVectorData(m_geometries_down,"blue");
    my_log.InsertEmptyLine();
    my_log.LogVectorData(m_geometries_up,"red");
}