 #include <gtest/gtest.h>
 #include "../../src/EA/EvolutionAlgorithm.hpp"
 #include "../../src/EA/GenotypeData.hpp"
 #include "../../src/Geometries/CircleFactory.hpp"
 #include "../../src/EA/Genotype.hpp"
 #include "../../src/Geometries/Logger.hpp"

 typedef std::vector<GenotypeData<CircleData>> GenotypeDataVector;

class EA_TestFixture : public testing::Test
 {
     public:
         void SetUp() override{
            R_0_10_0_10  = Range(0,10,0,10);
            
            CData.SetRadius(1);
            GenotypeData<CircleData> GData1 = GenotypeData<CircleData>(5, R_0_10_0_10, CData);
            
            GDataVector.push_back(GData1);

            m_Genotype = Genotype<CircleFactory, CircleData>(GDataVector);

            EA = EvolutionAlgorithm<CircleFactory,CircleData>(1000, GDataVector);
         }

     EvolutionAlgorithm<CircleFactory,CircleData> EA;
     CircleData CData;
     GenotypeDataVector GDataVector;
     Range R_0_10_0_10;
     Genotype<CircleFactory, CircleData> m_Genotype;
 };

 TEST_F(EA_TestFixture, SelectionTestSizeOfPopulation){
     auto originalPop = EA.GetPopulation();
     EA.Selection();
     auto selectedPop = EA.GetPopulation();

     ASSERT_EQ(selectedPop.size(),originalPop.size());
 }

TEST_F(EA_TestFixture, CrossoverTestSizeOfPopulation){
    // Logger<CircleData> my_log("/Users/robertjelic/Documents/C++/Ellipses/tests/EATests/CSV_Files/", "test_crossover.txt");
    // Logger<CircleData> my_fitness_log("/Users/robertjelic/Documents/C++/Ellipses/tests/EATests/CSV_Files/", "test_crossover_fitness.txt");
    // Logger<CircleData> highest_fitness_geometry("/Users/robertjelic/Documents/C++/Ellipses/tests/EATests/CSV_Files/", "highest_fitness_geometry.txt");

    // //  auto originalPop = EA.GetPopulation();
    // //  for(auto i : originalPop){
    // //     my_log.LogVectorData(i->GetGeometries());
    // //     my_log.InsertEmptyLine();
    // //  }
    // //  auto selectedPop = EA.GetPopulation();
    // //  for(auto i : selectedPop){
    // //     my_log.LogVectorData(i->GetGeometries(), "blue");
    // //     my_log.InsertEmptyLine();
    // //  }
    // //  for(auto i : selectedPop){
    // //     std::cout<< i->GetFitnessScore() << " ";
    // //  }
    // //  std::cout<<std::endl;
  
    // int temperatura{2};
    // EA.SetMutationProbability(0.6);
    // double highest_fitness = 0;
    // for(int i=0; i<10000; i++){
    // //mutacija metoda kaljenja
    //  if(i>1 && i%2==0 && temperatura<=20){
    //      EA.SetMutationProbability(1/temperatura);
    //      temperatura++;
    //  }

    //  EA.Selection();
    //  EA.Crossover();
    //  EA.Mutation();
    //  EA.SortPopulation();
    //  auto t_pop = EA.GetPopulation();
    //  // TODO!! SAVE GENOTYPE WITH MAX FITNESS SCORE
    //  auto fitness = t_pop[0]->GetFitnessScore();
    // //record highest fitness geometries
    //  if(fitness > highest_fitness){
    //     highest_fitness = fitness;
    //     highest_fitness_geometry.LogVectorData(t_pop[0]->GetGeometries());
    //     highest_fitness_geometry.InsertEmptyLine();
    //     highest_fitness_geometry.LogFitnessScore(fitness);
    //     highest_fitness_geometry.InsertEmptyLine();
    //  }

    //  my_fitness_log.LogFitnessScore(fitness);
    // }

    // EA.Selection();
    // EA.SortPopulation();
    // auto crossoverPop = EA.GetPopulation();

    // my_log.LogVectorData(crossoverPop[0]->GetGeometries());

    // //  for(auto i : crossoverPop){
    // //     my_log.LogVectorData(i->GetGeometries(), "red");
    // //     my_log.InsertEmptyLine();
    // //  }
 //    ASSERT_EQ(selectedPop.size(),originalPop.size());
 }