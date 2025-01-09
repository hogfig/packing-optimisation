#include <gtest/gtest.h>
#include "../../src/EA/GenotypeData.hpp"
#include "../../src/Geometries/CircleFactory.hpp"
#include "../../src/Geometries/Logger.hpp"
#include "../../src/EA/Genotype.hpp"
#include "../../src/Geometries/GeometryHelper.hpp"
#include <iostream>

void CalculateFitnesFunction(std::shared_ptr<Genotype<CircleFactory, CircleData>> gp)
{
    //Calculate the area of the square containing all geometries.
    double min_x{std::numeric_limits<double>::max()};
    double min_y{std::numeric_limits<double>::max()};
    double max_x{-std::numeric_limits<double>::max()};
    double max_y{-std::numeric_limits<double>::max()};
    double square_side{};

    for (auto geometry : gp->m_geometries)
    {
        auto point = geometry->GetCenterPoint();
        if (point.x < min_x)
        {
            min_x = point.x;
        }
        if (point.x > max_x)
        {
            max_x = point.x;
        }
        if (point.y < min_y)
        {
            min_y = point.y;
        }
        if (point.y > max_y)
        {
            max_y = point.y;
        }
    }

    if (max_x - min_x > max_y - min_y)
    {
        square_side = max_x - min_x;
    }
    else
    {
        square_side = max_y - min_y;
    }

    gp->m_fitness_score = 1/(square_side * square_side);
}

class GenotypeFixture : public testing::Test{
    public:
        void SetUp() override{
            n_geo = 5;
            R_0_10_0_10  = Range(0,10,0,10);
            R_10_20_10_20 = Range(10,20,10,20);
            R_0_5_10_20 = Range(0,5,10,20);

            CData.SetRadius(1);
            GenotypeData<CircleData> GData1 = GenotypeData<CircleData>(3, R_0_10_0_10, CData);
            CData.SetRadius(2);
            GenotypeData<CircleData> GData2 = GenotypeData<CircleData>(4, R_10_20_10_20, CData);
            CData.SetRadius(3);
            GenotypeData<CircleData> GData3 = GenotypeData<CircleData>(5, R_0_5_10_20, CData);
            
            GDataVector.push_back(GData1);
            GDataVector.push_back(GData2);
            GDataVector.push_back(GData3);

            m_Genotype = std::make_shared<Genotype<CircleFactory, CircleData>>( Genotype<CircleFactory, CircleData>(GDataVector));
        }
    
        Range R_0_10_0_10;
        Range R_10_20_10_20; 
        Range R_0_5_10_20;
        GeometryHelper<CircleData> GH;
        std::vector<GenotypeData<CircleData>> GDataVector;
        std::shared_ptr<Genotype<CircleFactory, CircleData>> m_Genotype;
        CircleData CData;
        int n_geo{};
};

TEST_F(GenotypeFixture, GenotypeTest){
    Logger<CircleData> my_log("/Users/robertjelic/Documents/C++/Ellipses/tests/EATests/", "test_file.txt");
    m_Genotype->InitialiseGeometries();
    auto geo = m_Genotype->GetGeometries();
    GH.RearangeGeometries(geo);
    CalculateFitnesFunction(m_Genotype);

    my_log.LogVectorData(m_Genotype->GetGeometries());

    EXPECT_TRUE(true);
}

TEST(GenotypeData, FitnessFunction){
    /*
    -6.87275,13.8151,1,black
    -6.85382,15.8192,1,black
    -4.87277,13.8129,1,black
    -4.85382,15.8128,1,black
    */

   /*
   107.221,-5.08152,1,black
    107.206,-3.08192,1,black
    105.221,-5.07265,1,black
    105.206,-1.07277,1,black
   */
    std::vector<std::tuple<double,double>> data = {{-96.4462,2.46557}
                                                    ,{-102.125,3.56938}
                                                    ,{-100.227,2.9427}
                                                    ,{-98.2601,1.30658}};
    CircleData CData;
    CData.SetRadius(1);
    Range R_0_10_0_10  = Range(0,10,0,10);
    GenotypeData<CircleData> GData = GenotypeData<CircleData>(4, R_0_10_0_10, CData);
    std::vector<GenotypeData<CircleData>> GenotypeDatavector;
    GenotypeDatavector.push_back(GData);
    std::shared_ptr<Genotype<CircleFactory, CircleData>> genotype;
    genotype = std::make_shared<Genotype<CircleFactory, CircleData>>(Genotype<CircleFactory, CircleData>(GenotypeDatavector));
    genotype->InitialiseGeometries();

    auto geo = genotype->GetGeometries();
    for(int i = 0; i<4; i++)
    {
        Point p = geo[i]->GetCenterPoint();
        p.x = std::get<0>(data[i]);
        p.y = std::get<1>(data[i]);
        geo[i]->SetCenterPoint(p);
    }

    for(auto& g : genotype->GetGeometries())
    {
        std::cout << g->GetCenterPoint() << std::endl;
    }
    CalculateFitnesFunction(genotype);
    std::cout << genotype->GetFitnessScore() << std::endl;
}