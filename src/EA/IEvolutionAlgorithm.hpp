#pragma once
#include "Population.hpp"
#include "Genotype.hpp"
#include "GeometryHelper.hpp"
#include "ThreadPool.hpp"
/**
 * @note Before using the EvolutionAlgorithm class be sure to define the Genotype::CalculateFitnesFunction() friend function!
 */
template<typename Factory, typename GeometryData>
class IEvolutionAlgorithm{
    public:
        using Genotype_Ptr = std::shared_ptr<Genotype<Factory, GeometryData>>;
        using GenotypeVector = std::vector<Genotype_Ptr>;
        using GeometryVector = std::vector<std::shared_ptr<IGeometry<GeometryData>>>;
        /**
         * Constructor for the Evolution Algorithm base class parameters.
         * @param populationSize (int) Size of the population
         * @param genotypeData (std::vector<GenotypeData<GeometryData>>) Genotype data
         * @param mutation_probability (double) Mutation probability
         * @param crossover_probability (double) Crossover probability
         * @param mutation_delta (float) The maximum possible mutation delta for a parameter
         * 
         */
        IEvolutionAlgorithm(int populationSize, 
                            std::vector<GenotypeData<GeometryData>> genotypeData,
                            double mutation_probability,
                            double crossover_probability,
                            float mutation_delta);

        IEvolutionAlgorithm() = default;
        virtual ~IEvolutionAlgorithm() = default;

        /**
         * Perform the selection of the population based on fitness values.
         */
        virtual void Selection();

        /**
         * Perform the crossover of the population based on the crossover probability.
         */
        virtual void Crossover() = 0;

        /**
         * Perform the mutation of the population based on the mutation probability.
         */
        virtual void Mutation() = 0;

        /**
         * Sort the population, default in descending order.
         */
        virtual void SortPopulation();

        /**
         * @returns GenotypeVector The current population.
         */
        GenotypeVector GetPopulation();

        /**
         * @returns double The current best fitness score.
         */
        double GetBestFitnessScore();

        /**
         * @param double The crossover probability. Value between 0 and 1.
         */
        void SetCrossoverProbability(double p);

        /**
         * @param double The mutation probability. Value between 0 and 1.
         */
        void SetMutationProbability(double p);

        /**
         * @param float The mutation delta. Maximal value of mutation for parameters.
         */
        void SetMutationDelta(float d);
    protected:

        /**
         * Normalises fitness values of the population, so all values lay between 0 and 1.
         */
        virtual void NormaliseFitnesScore();

        Population<Factory, GeometryData> m_population;
        double m_mutation_probability{};
        double m_crossover_probability{}; 
        double m_current_best_fitness_score{};
        float m_mutation_delta{};
        GeometryHelper<GeometryData> m_GH;
};
