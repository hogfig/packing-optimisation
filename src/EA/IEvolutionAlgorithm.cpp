#include "IEvolutionAlgorithm.hpp"
#include <random>
#include <time.h>
#include "Genotype.hpp"
#include "CircleFactory.hpp"
#include "CircleData.hpp"
#include "GeometryHelper.hpp"

namespace{
    template<typename Factory, typename GeometryData>
    void calculateCumulativeFitness(std::vector<std::shared_ptr<Genotype<Factory,GeometryData>>> genotype_vecor, double &fitnessValue){
        for(auto genome : genotype_vecor){
            fitnessValue += genome->GetFitnessScore();
        }
        if(fitnessValue<=0){
            std::cout<<"Error calculating fitness scores"<<std::endl;
            exit(1);
        }
    }
};

template<typename Factory, typename GeometryData>
IEvolutionAlgorithm<Factory, GeometryData>::IEvolutionAlgorithm(
    int populationSize, 
    std::vector<GenotypeData<GeometryData>> genotypeData,
    double mutation_probability,
    double rossover_probability,
    float mutation_delta) :
    m_population{populationSize,genotypeData},
    m_crossover_probability{mutation_probability},
    m_mutation_probability{rossover_probability},
    m_mutation_delta{mutation_delta},
    m_current_best_fitness_score{0}
{
}

template<typename Factory, typename GeometryData>
void IEvolutionAlgorithm<Factory, GeometryData>::SortPopulation(){
    m_population.SortPopulationDescending();
}

template<typename Factory, typename GeometryData>
std::vector<std::shared_ptr<Genotype<Factory, GeometryData>>> IEvolutionAlgorithm<Factory, GeometryData>::GetPopulation(){
    return m_population.GetPopulation();
}
template<typename Factory, typename GeometryData>
double IEvolutionAlgorithm<Factory, GeometryData>::GetBestFitnessScore()
{
    return m_current_best_fitness_score;
}

template<typename Factory, typename GeometryData>
void IEvolutionAlgorithm<Factory, GeometryData>::SetCrossoverProbability(double p)
{
    m_crossover_probability = p;
}

template<typename Factory, typename GeometryData>
void IEvolutionAlgorithm<Factory, GeometryData>::SetMutationProbability(double p)
{
    m_mutation_probability = p;
}

template<typename Factory, typename GeometryData>
    void IEvolutionAlgorithm<Factory, GeometryData>::NormaliseFitnesScore(){
        auto genotypeVecor = m_population.GetPopulation();
        double cumulativeFitnessValue{0};
        double checkNormalisation{0};
        calculateCumulativeFitness(genotypeVecor, cumulativeFitnessValue);
        
        for(int i=0; i<genotypeVecor.size(); i++){
            double normalisedProbability = (double)genotypeVecor[i]->GetFitnessScore()/cumulativeFitnessValue;
            genotypeVecor[i]->SetNormalizedFitnessScore(normalisedProbability);
            checkNormalisation += normalisedProbability;
        }

        m_population.SetPopulation(genotypeVecor);
    }

//Selection based on game of rullet
template<typename Factory, typename GeometryData>
void IEvolutionAlgorithm<Factory, GeometryData>::Selection(){
    m_population.CalculateFitnessFunction();
    NormaliseFitnesScore();
    m_population.SortPopulationAscending();

    auto genotypeVecor = m_population.GetPopulation();

    m_current_best_fitness_score = genotypeVecor.back()->GetFitnessScore();

    std::vector<double> rulletVector{0.0};
    for(int i=0; i< genotypeVecor.size(); i++){
        rulletVector.push_back(genotypeVecor[i]->GetNormalizedFitnessScore() + rulletVector[i]);
    }

    std::vector<std::shared_ptr<Genotype<Factory,GeometryData>>> selectedPopulation;
    //used so we get a different random numbers on every iteration
    srand(time(0));
    for(int i=0; i<rulletVector.size()-1; i++){
        //Calculate random number
        double random_value = ((double)rand() / (RAND_MAX));
        auto lb = std::lower_bound(rulletVector.begin(), rulletVector.end(), random_value);
        auto dist = std::distance(rulletVector.begin(),lb);
        if(lb == rulletVector.end()){
            selectedPopulation.push_back(std::make_shared<Genotype<Factory,GeometryData>>(*genotypeVecor[genotypeVecor.size()-1]));
        }else{
            selectedPopulation.push_back(std::make_shared<Genotype<Factory,GeometryData>>(*genotypeVecor[std::distance(rulletVector.begin(),lb) - 1]));
        }
    }

    m_population.SetPopulation(selectedPopulation);
}

template<typename Factory, typename GeometryData>
void IEvolutionAlgorithm<Factory, GeometryData>::SetMutationDelta(float d)
{
    m_mutation_delta = d;
}

template class IEvolutionAlgorithm<CircleFactory, CircleData>;