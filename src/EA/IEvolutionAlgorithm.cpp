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
    m_mutation_delta{mutation_delta}
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
void IEvolutionAlgorithm<Factory, GeometryData>::CrossoverPairOfGenomes(std::shared_ptr<Genotype<Factory,GeometryData>> &first, std::shared_ptr<Genotype<Factory,GeometryData>> &second){
    auto first_geometries = first->GetGeometries();
    auto second_geometries = second->GetGeometries();
    m_GH.AllignGeometries(first_geometries,second_geometries);
    int point_of_coppy = first_geometries.size()/2;

    second_geometries.insert(second_geometries.end(),first_geometries.begin(),first_geometries.begin()+point_of_coppy);
    first_geometries.insert(first_geometries.end(),second_geometries.begin(), second_geometries.begin()+point_of_coppy);

    second_geometries.erase(second_geometries.begin(), second_geometries.begin()+point_of_coppy);
    first_geometries.erase(first_geometries.begin(),first_geometries.begin()+point_of_coppy);

    m_GH.RearangeGeometries(first_geometries);
    m_GH.RearangeGeometries(second_geometries);

    first->SetGeometries(first_geometries);
    second->SetGeometries(second_geometries);
}

template<typename Factory, typename GeometryData>
void IEvolutionAlgorithm<Factory, GeometryData>::Crossover(){
    std::vector<std::shared_ptr<Genotype<Factory,GeometryData>>> temp_population;
    std::vector<std::shared_ptr<Genotype<Factory,GeometryData>>> population = m_population.GetPopulation();
    //Make random pairs.
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(population.begin(), population.end(),g);
    
    //For each pair check if crossover will take place.
    srand( (unsigned)time( NULL ) );
    for(int i=0; i<population.size()/2; i++){
        float r_num = (float)rand()/RAND_MAX;
        if(r_num < m_crossover_probability){
            //Crossover pair.
            CrossoverPairOfGenomes(population[2*i], population[(2*i)+1]);
            //Put new pair in temporary population.
            temp_population.push_back(std::make_shared<Genotype<Factory,GeometryData>>(*population[2*i]));
            temp_population.push_back(std::make_shared<Genotype<Factory,GeometryData>>(*population[(2*i)+1]));
        }else{
            temp_population.push_back(std::make_shared<Genotype<Factory,GeometryData>>(*population[2*i]));
            temp_population.push_back(std::make_shared<Genotype<Factory,GeometryData>>(*population[(2*i)+1]));
        }
    }
    //Set new population.
    m_population.SetPopulation(temp_population);
    //Update the fitness function
 //   m_population.CalculateFitnessFunction();
   // NormaliseFitnesScore();
}

template<typename Factory, typename GeometryData>
void IEvolutionAlgorithm<Factory, GeometryData>::Mutation(){
    std::vector<std::shared_ptr<Genotype<Factory,GeometryData>>> population = m_population.GetPopulation();
    std::random_device rd;
    std::mt19937 gen(rd());
    
    for(std::shared_ptr<Genotype<Factory,GeometryData>> genotype : population){
        float r_num = (float)rand()/RAND_MAX;
        if(r_num < m_mutation_probability){
            auto geometries = genotype->GetGeometries();
            //select one random geometry
            std::uniform_int_distribution<> geometry_distr(0,geometries.size()-1);
            auto random_geometry = geometries[geometry_distr(gen)];
            //move it's center point randomly by delta
            Point current_point = random_geometry->GetCenterPoint();
            //can be  -1, 0, 1
            std::uniform_int_distribution<> distr(-1, 1);
            current_point.x += distr(gen)*m_mutation_delta;
            current_point.y += distr(gen)*m_mutation_delta;

            random_geometry->SetCenterPoint(current_point);
            m_GH.RearangeGeometries(geometries);
            int i = 2;
        }
    }
    m_population.CalculateFitnessFunction();
}

template<typename Factory, typename GeometryData>
void IEvolutionAlgorithm<Factory, GeometryData>::SetMutationDelta(float d)
{
    m_mutation_delta = d;
}

template class IEvolutionAlgorithm<CircleFactory, CircleData>;