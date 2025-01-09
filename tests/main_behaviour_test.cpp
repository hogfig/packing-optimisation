#include <iostream>
#include "../src/Geometries/Circle.hpp"
#include "../src/Geometries/IGeometry.hpp"
#include "../src/EA/Population.hpp"
#include "../src/Geometries/CircleFactory.hpp"
#include "../src/Geometries/Logger.hpp"
#include "../src/EA/Genotype.hpp"
#include "../src/EA/EvolutionAlgorithm.hpp"
#include "GeometryHelper.hpp"

void CalculateFitnesFunction(Genotype<CircleFactory> *gp)
{
    //Calculate the area of the square containing all geometries.
    double min_x{std::numeric_limits<double>::max()};
    double min_y{std::numeric_limits<double>::max()};
    double max_x{-std::numeric_limits<double>::max()};
    double max_y{-std::numeric_limits<double>::max()};
    double square_side{};

    for (auto geometry : gp->m_geometries)
    {
        auto point = geometry->GetCenterPoint();
        if (point.x < min_x)
        {
            min_x = point.x;
        }
        else if (point.x > max_x)
        {
            max_x = point.x;
        }
        else if (point.y < min_y)
        {
            min_y = point.y;
        }
        else if (point.y > max_y)
        {
            max_y = point.y;
        }
    }

    if (max_x - min_x > max_y - min_y)
    {
        square_side = max_x - min_x;
    }
    else
    {
        square_side = max_y - min_y;
    }

    gp->m_fitness_score = square_side * square_side;
}


int main()
{
    GeometryHelper gm;
    Logger my_log("/Users/robertjelic/Documents/C++/Ellipses/", "test_file.txt");
    GenotypeConfig gc(10,
                      {std::make_pair<Range, std::vector<double>>(Range(0, 15, 0, 15), {2})},
                      {10});
    
    EvolutionAlgorithm<CircleFactory> EA = EvolutionAlgorithm<CircleFactory>(10, gc);

    auto pop = EA.GetPopulation();

    for (auto& g : pop)
    {
        auto x = g->GetGeometries();
        gm.RearangeGeometries(x);
        my_log.LogVectorData(g->GetGeometries());
        my_log.InsertEmptyLine();
        CalculateFitnesFunction(g.get());
        std::cout << g->GetFitnessScore() << std::endl;
    }
    std::cout << std::endl;
   // EA.Selection();
   //TEST IF CROSSOVER WORKS !
    EA.Crossover();
    auto pop2 = EA.GetPopulation();

    for (auto& g : pop2)
    {
        auto x = g->GetGeometries();
        gm.RearangeGeometries(x);
        my_log.LogVectorData(g->GetGeometries());
        my_log.InsertEmptyLine();
        CalculateFitnesFunction(g.get());
        std::cout << g->GetFitnessScore() << std::endl;
    }

    return 0;
}