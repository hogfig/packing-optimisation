#include "../src/EA/IEvolutionAlgorithm.hpp"
#include "../src/Geometries/CircleData.hpp"
#include "../src/Geometries/CircleFactory.hpp"
#include "ThreadPool.hpp"

class EACircle : public IEvolutionAlgorithm<CircleFactory, CircleData>
{
public:
    using Genotype_Ptr = std::shared_ptr<Genotype<CircleFactory, CircleData>>;
    using GenotypeVector = std::vector<Genotype_Ptr>;
    using GeometryVector = std::vector<std::shared_ptr<IGeometry<CircleData>>>;

    EACircle(int populationSize, std::vector<GenotypeData<CircleData>> genotypeData, int num_threads=4);
    EACircle() = default;
    virtual ~EACircle() = default;

    //Override inherited methods from IEvolutionAlgorithm
    void Crossover() override;
    void Mutation() override;

protected:

    /**
     * Perform a crossover of a pair of genomes. Include ellitism.
     * 
     * @param first A genotype ready for crossover.
     * @param second A genotype ready for crossover.
     */
    void CrossoverPairOfGenomes(Genotype_Ptr &first, Genotype_Ptr &second, int &elliteCount, int popSize);

private:

    /**
     * Check if a fitness score is ellite. To be ellite, the fitness score has to be in the range 
     * of 10% of the value of the current biggest fitness.
     */
    bool isFitnessEllite(double fitness);

    void CrossoverPairOfGenomesEllitism();

    GenotypeVector crossoverWorker(GenotypeVector population);
    GenotypeVector mutationWorker(GenotypeVector population);

    uint m_numberOfThreads;
    std::shared_ptr<ThreadPool> m_TP;
};

