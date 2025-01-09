#pragma once
#include "Population.hpp"
#include "Genotype.hpp"
#include "GeometryHelper.hpp"
/**
 * @note Before using the EvolutionAlgorithm class be sure to define the Genotype::CalculateFitnesFunction() frined function!
 */
template<typename Factory, typename GeometryData>
class EvolutionAlgorithm{
    public:
        using Genotype_Ptr = std::shared_ptr<Genotype<Factory, GeometryData>>;
        using GenotypeVector = std::vector<Genotype_Ptr>;
        using GeometryVector = std::vector<std::shared_ptr<IGeometry<GeometryData>>>;

        EvolutionAlgorithm() = default;
        /**
         * @param populationSize The number of a population.
         * @param genotypeData The parameters describing the Genotype of the population.
         */
        EvolutionAlgorithm(int populationSize, std::vector<GenotypeData<GeometryData>> genotypeData);
        ~EvolutionAlgorithm() = default;;
        void Selection();
        void Crossover();
        void Mutation();

        GenotypeVector GetPopulation();
        void SortPopulation();
        void SetCrossoverProbability(double p);
        void SetMutationProbability(double p);
        void SetMutatuinDelta(float d);
    protected:
        void NormaliseFitnesScore();
    private:
        void CrossoverPairOfGenomes(Genotype_Ptr &first, Genotype_Ptr &second);

        Population<Factory, GeometryData> m_population;
        double m_mutation_probability{}; //default 0.2
        double m_crossover_probability{}; //default 0.5
        float m_mutation_delta{};
        GeometryHelper<GeometryData> m_GH;
};
