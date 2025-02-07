#include "EACircle.hpp"
#include <random>
#include <time.h>

EACircle::EACircle(int populationSize, std::vector<GenotypeData<CircleData>> genotypeData) :
IEvolutionAlgorithm<CircleFactory,CircleData>(populationSize, genotypeData,0.6,0.1,1),
m_numberOfThreads(4),
m_TP(std::make_shared<ThreadPool>(m_numberOfThreads))
{
    if(populationSize%2 != 0 || populationSize == 0){
        std::cout<<"Population number has to be a multiple of 2!"<<std::endl;
        exit(1);
    }
    m_population.GeneratePopulation();
}
EACircle::GenotypeVector EACircle::crossoverWorker(EACircle::GenotypeVector population)
{
    EACircle::GenotypeVector temp_population;

    for(int i=0; i<population.size()/2; i++){
        float r_num = (float)rand()/RAND_MAX;
        if(r_num < m_crossover_probability){
            //Crossover pair.
            CrossoverPairOfGenomes(population[2*i], population[(2*i)+1]);
            //Put new pair in temporary population.
            temp_population.push_back(std::make_shared<Genotype<CircleFactory,CircleData>>(*population[2*i]));
            temp_population.push_back(std::make_shared<Genotype<CircleFactory,CircleData>>(*population[(2*i)+1]));
        }else{
            temp_population.push_back(std::make_shared<Genotype<CircleFactory,CircleData>>(*population[2*i]));
            temp_population.push_back(std::make_shared<Genotype<CircleFactory,CircleData>>(*population[(2*i)+1]));
        }
    }
    return temp_population;
}

void EACircle::Crossover()
{
    EACircle::GenotypeVector population = m_population.GetPopulation();
    //Make random pairs.
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(population.begin(), population.end(),g);

    // Determine chunk size
    size_t chunkSize = population.size() / m_numberOfThreads;
    
    std::vector<std::future< EACircle::GenotypeVector >> futures;
    
    // Enqueue tasks
    for (int i = 0; i < m_numberOfThreads; ++i) {
        size_t start = i * chunkSize;
        size_t end = (i == m_numberOfThreads - 1) ? population.size() : start + chunkSize;
        
        // Create chunk
        EACircle::GenotypeVector chunk(population.begin() + start, population.begin() + end);
        
        // Submit chunk to thread pool for processing
        futures.push_back(m_TP->enqueue(std::bind(&EACircle::crossoverWorker, this, chunk)));
    }

    // Merge results
    EACircle::GenotypeVector temp_population;
    for (auto& future : futures) {
        EACircle::GenotypeVector chunkResult = future.get(); // Wait for result
        temp_population.insert(temp_population.end(), chunkResult.begin(), chunkResult.end());
    }

    //Set new population.
    m_population.SetPopulation(temp_population);
}

EACircle::GenotypeVector EACircle::mutationWorker(EACircle::GenotypeVector population)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    for(Genotype_Ptr genotype : population){
        float r_num = (float)rand()/RAND_MAX;
        if(r_num < m_mutation_probability){
            auto geometries = genotype->GetGeometries();
            //select one random geometry
            std::uniform_int_distribution<> geometry_distr(0,geometries.size()-1);
            auto random_geometry = geometries[geometry_distr(gen)];
            //move it's center point randomly by delta
            Point current_point = random_geometry->GetCenterPoint();
            //can be  -1, 0, 1
            std::uniform_int_distribution<> distr(-1, 1);
            current_point.x += distr(gen)*m_mutation_delta;
            current_point.y += distr(gen)*m_mutation_delta;

            random_geometry->SetCenterPoint(current_point);
            m_GH.RearangeGeometries(geometries);
            int i = 2;
        }
    }
    return population;
}

void EACircle::Mutation()
{
    EACircle::GenotypeVector population = m_population.GetPopulation();
    
    // Determine chunk size
    size_t chunkSize = population.size() / m_numberOfThreads;
    
    std::vector<std::future< EACircle::GenotypeVector >> futures;
    
    // Enqueue tasks
    for (int i = 0; i < m_numberOfThreads; ++i) {
        size_t start = i * chunkSize;
        size_t end = (i == m_numberOfThreads - 1) ? population.size() : start + chunkSize;
        
        // Create chunk
        EACircle::GenotypeVector chunk(population.begin() + start, population.begin() + end);
        
        // Submit chunk to thread pool for processing
        futures.push_back(m_TP->enqueue(std::bind(&EACircle::mutationWorker, this, chunk)));
    }

    // Merge results
    EACircle::GenotypeVector temp_population;
    for (auto& future : futures) {
        EACircle::GenotypeVector chunkResult = future.get(); // Wait for result
        temp_population.insert(temp_population.end(), chunkResult.begin(), chunkResult.end());
    }

    //Set new population.
    m_population.SetPopulation(temp_population);
    m_population.CalculateFitnessFunction();
}