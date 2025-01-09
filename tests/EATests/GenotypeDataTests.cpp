#include <gtest/gtest.h>
#include "../../src/EA/GenotypeData.hpp"
#include "../../src/Geometries/CircleData.cpp"

class GenotypeDataFixture : public testing::Test{
    public:
        void SetUp() override{
            n_geo = 5;
            R_0_10_0_10  = Range(0,10,0,10);
            R_10_20_10_20 = Range(10,20,10,20);
            R_0_5_10_20 = Range(0,50,10,20);

            CData.SetRadius(1);
            GData = GenotypeData<CircleData>(n_geo, R_0_10_0_10, CData);
        }
    
        Range R_0_10_0_10;
        Range R_10_20_10_20; 
        Range R_0_5_10_20;
        GenotypeData<CircleData> GData;
        CircleData CData;
        int n_geo{};
};

TEST_F(GenotypeDataFixture, GetFunctionTests){
    EXPECT_EQ(GData.GetGeometryData(), CData);
    EXPECT_EQ(GData.GetNumberOfGeometries(), n_geo);
    EXPECT_EQ(GData.GetRange(), R_0_10_0_10);
}

TEST_F(GenotypeDataFixture, SetFunctionTests){
    GData.SetNumberOfGeometries(2);
    EXPECT_EQ(GData.GetNumberOfGeometries(), 2);

    GData.SetGeometryData(CircleData(Point(), 3));
    EXPECT_EQ(GData.GetGeometryData(), CircleData(Point(), 3));
    
    GData.SetRange(R_10_20_10_20);
    EXPECT_EQ(GData.GetRange(), R_10_20_10_20);
}

TEST_F(GenotypeDataFixture, SettingCenterPointToGEODataOfGENOData){
    Point p = Point(12,15);
    auto gd = GData.GetGeometryData();
    gd.SetCenterPoint(p);
    EXPECT_EQ(gd.GetCenterPoint(), p);
}