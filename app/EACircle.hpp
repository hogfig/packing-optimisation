#include "../src/EA/IEvolutionAlgorithm.hpp"
#include "../src/Geometries/CircleData.hpp"
#include "../src/Geometries/CircleFactory.hpp"

class EACircle : public IEvolutionAlgorithm<CircleFactory, CircleData>
{
public:
    EACircle(int populationSize, std::vector<GenotypeData<CircleData>> genotypeData);
    EACircle() = default;
    virtual ~EACircle() = default;
};

