#include <gtest/gtest.h>
#include "../../src/EA/GenotypeData.hpp"
#include "../../src/Geometries/CircleFactory.hpp"
#include "../../src/Geometries/Logger.hpp"
#include "../../src/EA/Genotype.hpp"
#include "../../src/Geometries/GeometryHelper.hpp"
#include "../../src/EA/Population.hpp"

typedef std::vector<GenotypeData<CircleData>> GenotypeDataVector;

class PopulationFixture : public testing::Test{
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

            m_Genotype = Genotype<CircleFactory, CircleData>(GDataVector);
        }
    
        Range R_0_10_0_10;
        Range R_10_20_10_20; 
        Range R_0_5_10_20;
        GeometryHelper<CircleData> GH;
        GenotypeDataVector GDataVector;
        Genotype<CircleFactory, CircleData> m_Genotype;
        CircleData CData;
        int n_geo{};
};

/**
 * Test used to check the behaviour/functionality of class.
 */
TEST_F(PopulationFixture, PopulationTest){
    Logger<CircleData> my_log("/Users/robertjelic/Documents/C++/Ellipses/tests/EATests/", "test_file_pop.txt");
    Population<CircleFactory, CircleData> pop(1, GDataVector);
    pop.GeneratePopulation();
    auto genotypes = pop.GetPopulation();
    my_log.LogVectorData(genotypes[0]->GetGeometries());
}

TEST_F(PopulationFixture, SortPopulationDescendingTest){
    Population<CircleFactory, CircleData> pop(5, GDataVector);
    pop.GeneratePopulation();
    auto genotypes = pop.GetPopulation();
    //calculate fitness
    pop.CalculateFitnessFunction();
    pop.SortPopulationDescending();
    genotypes = pop.GetPopulation();
    
    EXPECT_GT(genotypes[0]->GetFitnessScore(),genotypes[4]->GetFitnessScore());
}

TEST_F(PopulationFixture, GetPopulationNumberTest){
    Population<CircleFactory, CircleData> pop(5, GDataVector);
    EXPECT_EQ(5,pop.GetPopulationNumber());
}

TEST_F(PopulationFixture, ErasePopulationTest){
    Population<CircleFactory, CircleData> pop(5, GDataVector);
    pop.GeneratePopulation();
    auto fullGenomes = pop.GetPopulation();
    pop.ErasePopulation();
    auto emptyGenomes = pop.GetPopulation();

    EXPECT_EQ(fullGenomes.size(),5);
    EXPECT_EQ(emptyGenomes.size(),0);
}

TEST_F(PopulationFixture, SetPopulationTest){
    Population<CircleFactory, CircleData> pop(5, GDataVector);
    
    EXPECT_EQ(pop.GetPopulation().size(),0);

    std::vector<std::shared_ptr<Genotype<CircleFactory,CircleData>>> n_population;
    n_population.push_back(std::make_shared<Genotype<CircleFactory,CircleData>>(m_Genotype));
    pop.SetPopulation(n_population);

    EXPECT_EQ(pop.GetPopulation().size(),1);
}