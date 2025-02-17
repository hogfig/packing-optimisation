#include "Genotype.hpp"
#include<iostream>
#include "../Geometries/IGeometry.hpp"
#include "../Geometries/CircleFactory.hpp"
#include "../Geometries/CircleData.hpp"
#include "GenotypeData.hpp"
#include <random>

template<typename Factory, typename GeometryData>
Genotype<Factory, GeometryData>::Genotype(GenotypeDataVector gc) : 
m_genotype_config(gc),
m_fitness_score{0},
m_normalized_fitness_score{0}
{
}

template<typename Factory, typename GeometryData>
Genotype<Factory, GeometryData>::Genotype(const Genotype &obj){
    //Copy all the geometries
    for(auto i : obj.m_geometries){
        m_geometries.push_back(m_geometry_factory.CreateObject(i->GetGeometryData()));
    }
    m_fitness_score = obj.m_fitness_score;
    m_genotype_config = obj.m_genotype_config;
    m_geometry_factory = obj.m_geometry_factory;
    m_normalized_fitness_score = obj.m_normalized_fitness_score;
}

template<typename Factory, typename GeometryData>
Genotype<Factory, GeometryData>::~Genotype(){

}

template<typename Factory, typename GeometryData>
void Genotype<Factory, GeometryData>::InitialiseGeometries(){

    m_geometries.erase(m_geometries.begin(),m_geometries.end());
    for(GenotypeData<GeometryData> genoData : m_genotype_config)
    {
        for(int i=0; i< genoData.GetNumberOfGeometries(); i++)
        {
            int x_min = genoData.GetRange().m_x_min;
            int x_max = genoData.GetRange().m_x_max;
            int y_min = genoData.GetRange().m_y_min;
            int y_max = genoData.GetRange().m_y_max;
            //generate random x nad y
            std::random_device rd; // obtain a random number from hardware
            std::mt19937 gen(rd()); // seed the generator
            std::uniform_int_distribution<> x_distr(x_min, x_max); // define the range
            std::uniform_int_distribution<> y_distr(y_min, y_max); // define the range
            //set random x,y
            Point random_center(x_distr(gen),y_distr(gen));
            auto GEOData = genoData.GetGeometryData();
            GEOData.SetCenterPoint(random_center);
            //create geometry object
            auto geometry_object = m_geometry_factory.CreateObject(GEOData);
            m_geometries.push_back(geometry_object);
        }
    }
}

template<typename Factory, typename GeometryData>
std::vector<std::shared_ptr<IGeometry<GeometryData>>> Genotype<Factory, GeometryData>::GetGeometries(){
    return m_geometries;
}

template<typename Factory, typename GeometryData>
std::vector<std::shared_ptr<IGeometry<GeometryData>>> Genotype<Factory, GeometryData>::GetGeometriesCoppy()
{
    std::vector<std::shared_ptr<IGeometry<GeometryData>>> coppiedVector;
    for(const auto& g : m_geometries)
    {
        auto shr = m_geometry_factory.CreateObject(g->GetGeometryData());
        coppiedVector.push_back(shr);
    }
    return coppiedVector;
}

template<typename Factory, typename GeometryData>
void Genotype<Factory, GeometryData>::SetGeometries(std::vector<std::shared_ptr<IGeometry<GeometryData>>> geometries){
    m_geometries = geometries;
}

template<typename Factory, typename GeometryData>
double Genotype<Factory, GeometryData>::GetFitnessScore(){
    return m_fitness_score;
}

template<typename Factory, typename GeometryData>
void Genotype<Factory, GeometryData>::SetFitnessScore(double score){
    m_fitness_score = score;
}

template<typename Factory, typename GeometryData>
double Genotype<Factory, GeometryData>::GetNormalizedFitnessScore(){
    return m_normalized_fitness_score;
}

template<typename Factory, typename GeometryData>
void Genotype<Factory, GeometryData>::SetNormalizedFitnessScore(double score){
    m_normalized_fitness_score = score;
}

template class Genotype<CircleFactory, CircleData>;