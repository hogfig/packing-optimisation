#pragma once
#include "Population.hpp"
#include "Genotype.hpp"
#include "GeometryHelper.hpp"
/**
 * @note Before using the EvolutionAlgorithm class be sure to define the Genotype::CalculateFitnesFunction() frined function!
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

        virtual void Selection();
        virtual void Crossover();
        virtual void Mutation();

        GenotypeVector GetPopulation();
        void SortPopulation();
        void SetCrossoverProbability(double p);
        void SetMutationProbability(double p);
        void SetMutationDelta(float d);
    protected:
        void NormaliseFitnesScore();
        void CrossoverPairOfGenomes(Genotype_Ptr &first, Genotype_Ptr &second);

        Population<Factory, GeometryData> m_population;
        double m_mutation_probability{}; //default 0.2
        double m_crossover_probability{}; //default 0.5
        float m_mutation_delta{};
        GeometryHelper<GeometryData> m_GH;
};
