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

    EACircle(int populationSize, std::vector<GenotypeData<CircleData>> genotypeData);
    EACircle() = default;
    virtual ~EACircle() = default;
    void Crossover() override;
    void Mutation() override;

private:
    GenotypeVector crossoverWorker(GenotypeVector population);
    GenotypeVector mutationWorker(GenotypeVector population);

    uint m_numberOfThreads;
    std::shared_ptr<ThreadPool> m_TP;
};

