#include "EACircle.hpp"
#include <random>
#include <time.h>

EACircle::EACircle(int populationSize, std::vector<GenotypeData<CircleData>> genotypeData, int num_threads) :
IEvolutionAlgorithm<CircleFactory,CircleData>(populationSize, genotypeData,0.1,0.6,1),
m_numberOfThreads(num_threads),
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
    int elliteCount{0};
    for(int i=0; i<population.size()/2; i++){
        float r_num = (float)rand()/RAND_MAX;
        if(r_num < m_crossover_probability){
            //Crossover pair.
            CrossoverPairOfGenomes(population[2*i], population[(2*i)+1], elliteCount, population.size());
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

bool EACircle::isFitnessEllite(double fitness)
{
    if((m_current_best_fitness_score - fitness) <= 0)
    {
        return false;
    }

    if( (m_current_best_fitness_score - fitness) < 0.05*m_current_best_fitness_score)
    {
        //fitness is elite
        return true;
    }   
}

// Overwrite CrossoverPairOfGenomes to include Elitism, do it nicely :)
void EACircle::CrossoverPairOfGenomes(Genotype_Ptr &first, Genotype_Ptr &second, int &elliteCount, int popSize)
{
    auto first_geometries = first->GetGeometriesCoppy();
    auto second_geometries = second->GetGeometriesCoppy();
    //Ellitism
    double first_fitness = first->GetFitnessScore();
    bool isFirstEllite = false;
    double second_fitness = second->GetFitnessScore();
    bool isSecondEllite = false;
    double biggest_fitess{};
    //Provjeri ako neki od genotipa spadaju u elite
    //Nakon krizanja provjeri ako elitni genotip ima vecu sposobnost od djece
    // Uzmi elitni genotip i najbolje dijete ili samo decu

    isFirstEllite = isFitnessEllite(first_fitness);
    if(isFirstEllite) biggest_fitess = first_fitness;

    isSecondEllite = isFitnessEllite(second_fitness);
    if(isSecondEllite) biggest_fitess = second_fitness;

    if(isFirstEllite && isSecondEllite)
    {
        if(first_fitness >= second_fitness)
        {
            biggest_fitess = first_fitness;
            isSecondEllite = false;
        }else{
            biggest_fitess = second_fitness;
            isFirstEllite = false;
        }
    }

    m_GH.AllignGeometries(first_geometries,second_geometries);
    int point_of_coppy = first_geometries.size()/2;

    second_geometries.insert(second_geometries.end(),first_geometries.begin(),first_geometries.begin()+point_of_coppy);
    first_geometries.insert(first_geometries.end(),second_geometries.begin(), second_geometries.begin()+point_of_coppy);

    second_geometries.erase(second_geometries.begin(), second_geometries.begin()+point_of_coppy);
    first_geometries.erase(first_geometries.begin(),first_geometries.begin()+point_of_coppy);

    m_GH.RearangeGeometries(first_geometries);
    m_GH.RearangeGeometries(second_geometries);

    bool enoughElliteMembers{false};//= elliteCount>0 ? (elliteCount/(float)popSize) >= 0.05 : false;
    if(elliteCount>0)
    {
        float ratio = elliteCount/(float)popSize;
        enoughElliteMembers = ratio >= 0.01 ? true : false;
    }
    
    if( !isFirstEllite && !isSecondEllite || enoughElliteMembers)
    {
        first->SetGeometries(first_geometries);
        second->SetGeometries(second_geometries);
        return;
    }

    auto first_child = std::make_shared<Genotype<CircleFactory,CircleData>>();
    auto second_child = std::make_shared<Genotype<CircleFactory,CircleData>>();

    first_child->SetGeometries(first_geometries);
    second_child->SetGeometries(second_geometries);
    CalculateFitnesFunction(first_child);
    CalculateFitnesFunction(second_child);
    
    auto first_child_fitness = first_child->GetFitnessScore();
    auto second_child_fitness = second_child->GetFitnessScore();
    if(first_child_fitness >= second_child_fitness)
    {
        first->SetGeometries(first_geometries);
        if(second_child_fitness>=biggest_fitess)
        {
            second->SetGeometries(second_geometries);
            return;
        }
    }else{
        first->SetGeometries(second_geometries);
        if(first_child_fitness>=biggest_fitess)
        {
            second->SetGeometries(first_geometries);
            return;
        }
    }

    if(isFirstEllite){
        elliteCount++;
        second->SetGeometries(first->GetGeometries());
    }else if(isSecondEllite)
    {
        elliteCount++;
        second->SetGeometries(second->GetGeometries());
    }
}