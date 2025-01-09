#pragma once
#include "GenotypeData.hpp"
#include "../Geometries/IGeometry.hpp"

template<typename Factory, typename GeometryData>
class Genotype{
    public:
        typedef std::vector<GenotypeData<GeometryData>> GenotypeDataVector;
        typedef std::vector<std::shared_ptr<IGeometry<GeometryData>>> IGeometryVector;
        Genotype() = default;
        Genotype(GenotypeDataVector genotype_data_v);
        Genotype(const Genotype &obj);
        ~Genotype();
        void InitialiseGeometries();
        IGeometryVector GetGeometries();
        void SetGeometries(IGeometryVector geometries);
        double GetFitnessScore();
        double GetNormalizedFitnessScore();
        void SetFitnessScore(double score);
        void SetNormalizedFitnessScore(double score);
        friend void CalculateFitnesFunction(std::shared_ptr<Genotype<Factory, GeometryData>> g);
    private:
        GenotypeDataVector m_genotype_config;
        Factory m_geometry_factory{};
        IGeometryVector m_geometries;
        double m_fitness_score{};
        double m_normalized_fitness_score{};
};