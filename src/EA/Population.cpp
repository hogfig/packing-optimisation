#include "Population.hpp"
#include "Genotype.hpp"
#include "../Geometries/CircleFactory.hpp"
#include "../Geometries/CircleData.hpp"


template<typename Factory, typename GeometryData>
Population<Factory,GeometryData>::Population(int N, std::vector<GenotypeData<GeometryData>> gdv) : 
m_population_number(N), 
m_genotype_config(gdv)
{
}

template<typename Factory, typename GeometryData>
Population<Factory,GeometryData>::~Population(){
    ErasePopulation();
}

template<typename Factory, typename GeometryData>
void Population<Factory,GeometryData>::GeneratePopulation(){
    ErasePopulation();
    for(int i=0; i<m_population_number; i++){
        Genotype<Factory,GeometryData> genome = Genotype<Factory,GeometryData>(m_genotype_config);
        genome.InitialiseGeometries();
        auto geo = genome.GetGeometries();
        GH.RearangeGeometries(geo);
        m_genotypes.push_back(std::make_shared<Genotype<Factory,GeometryData>>(genome));
    }
}

template<typename Factory, typename GeometryData>
std::vector<std::shared_ptr<Genotype<Factory,GeometryData>>> Population<Factory,GeometryData>::GetPopulation(){
    return m_genotypes;
}

template<typename Factory, typename GeometryData>
void Population<Factory,GeometryData>::SortPopulationDescending(){
    sort(m_genotypes.begin(), m_genotypes.end(), [](std::shared_ptr<Genotype<Factory,GeometryData>> lhv, std::shared_ptr<Genotype<Factory,GeometryData>> rsv){
        return lhv->GetFitnessScore() > rsv->GetFitnessScore();
    });
}

template<typename Factory, typename GeometryData>
void Population<Factory,GeometryData>::SortPopulationAscending(){
    sort(m_genotypes.begin(), m_genotypes.end(), [](std::shared_ptr<Genotype<Factory,GeometryData>> lhv, std::shared_ptr<Genotype<Factory,GeometryData>> rsv){
        return lhv->GetFitnessScore() < rsv->GetFitnessScore();
    });
}

template<typename Factory, typename GeometryData>
void Population<Factory,GeometryData>::CalculateFitnessFunction(){
    for(auto genome : m_genotypes){
        CalculateFitnesFunction(genome);
    }
}

template<typename Factory, typename GeometryData>
int Population<Factory,GeometryData>::GetPopulationNumber(){
    return m_population_number;
}

template<typename Factory, typename GeometryData>
void Population<Factory,GeometryData>::ErasePopulation(){
    m_genotypes.erase(m_genotypes.begin(),m_genotypes.end());
}

template<typename Factory, typename GeometryData>
void Population<Factory,GeometryData>::SetPopulation(std::vector<std::shared_ptr<Genotype<Factory,GeometryData>>> population){
    m_genotypes = population;
}

template class Population<CircleFactory, CircleData>;