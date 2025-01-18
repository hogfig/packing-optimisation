#include "EACircle.hpp"

EACircle::EACircle(int populationSize, std::vector<GenotypeData<CircleData>> genotypeData) :
IEvolutionAlgorithm<CircleFactory,CircleData>(populationSize, genotypeData,0.6,0.1,1)
{
    if(populationSize%2 != 0 || populationSize == 0){
        std::cout<<"Population number has to be a multiple of 2!"<<std::endl;
        exit(1);
    }
    m_population.GeneratePopulation();
}