#pragma once
#include<vector>
#include<iostream>
#include "../Geometries/CircleFactory.hpp"
#include "../Geometries/GeometryHelper.hpp"
#include "Genotype.hpp"
#include "GenotypeData.hpp"

/**
 * @brief Population class is a container of genotypes.
 */
template<typename Factory, typename GeometryData>
class Population{
    typedef std::vector<std::shared_ptr<Genotype<Factory, GeometryData>>> GenotypeVector;
    typedef std::vector<GenotypeData<GeometryData>> GenotypeDataVector;
    public:
        /**
         * Creating the Population with the number N of individuals. 
         * Each individual has it's paremeters set according to the GenotypeDataVector.
         * 
         * @param N Number of individuals in a population object.
         * @param gdv Genotype data vector, describing the parameters for the population. 
         */
        Population(int N, GenotypeDataVector gdv);
        Population() = default;
        /**
         * Class destructor. 
         */
        ~Population();

        /**
         * Erases current population and generates a new population. Each genom get's random geometries in
         * the set ranges (set by the GenotypeDataVector). After creating geometries, they are rearanged in a way
         * they don't intersect with eachother. 
         */
        void GeneratePopulation();

        /**
         * @return Vector of genotypes.
         */
        GenotypeVector GetPopulation();

        /**
         * Sorting the population (m_genotypes) according to the fitness function score.
         * Sorted in descending order.
         */
        void SortPopulationDescending();
        
        void SortPopulationAscending();

        /**
         * Calculates fitness function of each individual in the population. 
         * Uses the friend function of Genotype, must be defined!
         */
        void CalculateFitnessFunction();

        /**
         * @returns int Population number.
         */
        int GetPopulationNumber();
        
        /**
         * Erases current population.
         */
        void ErasePopulation();

        /**
         * Function for setting a new population.
         * @param population The new population to be set. 
         */
        void SetPopulation(GenotypeVector population);
        
    protected:
        int m_population_number{};
        GenotypeVector m_genotypes;
        GenotypeDataVector m_genotype_config;
        GeometryHelper<GeometryData> GH;
};