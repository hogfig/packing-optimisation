#include <iostream>
#include <iomanip>
#include "../src/EA/GenotypeData.hpp"
#include "../src/Geometries/CircleFactory.hpp"
#include "../src/EA/Genotype.hpp"
#include "../src/Geometries/Logger.hpp"
#include "EACircle.hpp"

using GenotypeDataVector = std::vector<GenotypeData<CircleData>>;

void CalculateFitnesFunction(std::shared_ptr<Genotype<CircleFactory, CircleData>> gp)
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
        if (point.x > max_x)
        {
            max_x = point.x;
        }
        if (point.y < min_y)
        {
            min_y = point.y;
        }
        if (point.y > max_y)
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

    gp->m_fitness_score = 1/(square_side * square_side);
    int ttt= 0;
}

int main()
{
    Range R_0_10_0_10  = Range(0,10,0,10);
    CircleData CData;
    GenotypeDataVector GDataVector;
    Genotype<CircleFactory, CircleData> m_Genotype;
    EACircle EA;
    int populationNumber = 2000;
    int geometryNumber = 12;
    int numberOfIterations = 20000;

    CData.SetRadius(1);
    GenotypeData<CircleData> GData1 = GenotypeData<CircleData>(geometryNumber, R_0_10_0_10, CData);
    GDataVector.push_back(GData1);
    m_Genotype = Genotype<CircleFactory, CircleData>(GDataVector);
    EA = EACircle(populationNumber, GDataVector);

    std::string filePath = "/Users/robertjelic/Documents/C++/Ellipses/app/CSV_Files/";
    Logger<CircleData> bestScoreLog( filePath, "best_score.txt");
    Logger<CircleData> fitnessScoreLog( filePath, "fitness_scores.txt");
    
    double highest_fitness = 0;
    int temperatura = 2;
    EA.SetMutationDelta(3);
    EA.SetCrossoverProbability(0.80);
    for(int i=0; i<numberOfIterations; i++){
    //mutacija metoda kaljenja
     if(i>1 && i%1000==0 && temperatura<=10){
         EA.SetMutationProbability(1/temperatura);
        //  if(i==70){
        //     EA.SetMutationDelta(2);
        //  }
         temperatura++;
     }

     EA.Selection();
     EA.Crossover();
     EA.Mutation();
     EA.SortPopulation();
     auto t_pop = EA.GetPopulation();
     auto fitness = t_pop[0]->GetFitnessScore();
     if(i%10 ==0){
        std::cout << std::setw(21) << std::left <<  "Maximum fitness" << std::setw(21) << "Current fitness" << "Loading" << std::endl;
        std::cout << std::setw(21) << std::left << highest_fitness << std::setw(21) << fitness << 100*(i/static_cast<float>(numberOfIterations))<<"%" << std::endl;
     }
    //record highest fitness geometries
     if(fitness > highest_fitness){
        highest_fitness = fitness;
        bestScoreLog.LogVectorData(t_pop[0]->GetGeometries());
        bestScoreLog.InsertEmptyLine();
     }

     fitnessScoreLog.LogDoubleValue(highest_fitness);
    }


    return 0;
}
