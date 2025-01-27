#pragma once
#include "GenotypeData.hpp"
#include "../Geometries/IGeometry.hpp"

/**
 * @brief A Genotype class would be a placeholder of all geometries and a fitness function related to 
 * the position of those geometries.
 */
template<typename Factory, typename GeometryData>
class Genotype{
    public:
        typedef std::vector<GenotypeData<GeometryData>> GenotypeDataVector;
        typedef std::vector<std::shared_ptr<IGeometry<GeometryData>>> IGeometryVector;
        Genotype() = default;
        Genotype(GenotypeDataVector genotype_data_v);
        Genotype(const Genotype &obj);
        ~Genotype();

        /**
         * @brief Initialises geometries with random x and y coordinates in the range defined
         * in the GenotypeDataVector. 
         * 
         * @note If you have to initialise another random atribute of a geometry such as
         * angle, you can do that in the Factory class of the geometry. 
         * 
         */
        void InitialiseGeometries();

        /**
         * @returns IGeometryVector vector of all geometries in a Genotype.
         */
        IGeometryVector GetGeometries();

        /**
         * @brief Sets the m_geometries attribute.
         * 
         * @param geometries vector of geometries.
         */
        void SetGeometries(IGeometryVector geometries);

        /**
         * @returns double Fitness score of the genotype.
         */
        double GetFitnessScore();

        /**
         * @returns double Normalized fitness score of the genotype. Value between 0 and 1.
         */
        double GetNormalizedFitnessScore();

        /**
         * @param score Fitness score of the genotype.
         */
        void SetFitnessScore(double score);

        /**
         * @param score Normalized fitness score of the genotype. Value between 0 and 1.
         */
        void SetNormalizedFitnessScore(double score);

        /**
         * @brief A friend function that needs to be implemented! Specific for each optimisation
         * problem. 
         */
        friend void CalculateFitnesFunction(std::shared_ptr<Genotype<Factory, GeometryData>> g);

    private:
        GenotypeDataVector m_genotype_config;
        Factory m_geometry_factory{};
        IGeometryVector m_geometries;
        double m_fitness_score{};
        double m_normalized_fitness_score{};
};