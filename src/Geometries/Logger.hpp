#pragma once
#include<fstream>
#include"IGeometry.hpp"

 /**
  * Class created for logging geometry data. The data is written into a CSV file.The data written follows the next order:
  *  - center point
  *  - internal variables (eg. radius)
  *  - color
  */
template<typename GeometryData>
class Logger{
    public:
        /**
         * @brief Creates a Logger obejct and opens provided CSV file. 
         * If no such file within a given directory is found, a file is created.
         * 
         * @param directory Directory of file.
         * @param filename Name of file.
         */
        Logger(std::string directory, std::string filename);

        /**
         * @brief Closes opened std::ofstream file.
         */
        ~Logger();

        /**
         * @brief Streams geometry data to the CSV file.
         * 
         * @param geometry_data Geometry data.
         * @param color Color of geometry when being displayed, default is black.
         */
        void LogObjectData(std::shared_ptr<IGeometry<GeometryData>> geometry_data, std::string color="black");

        /**
         * @brief Streams vector of geometry data to the CSV file.
         * 
         * @param v_geometry_data Vector of geometry data.
         * @param color Color of all geometries in a vector when being displayed, default is black.
         */
        void LogVectorData(std::vector<std::shared_ptr<IGeometry<GeometryData>>> v_geometry_data, std::string color="black");

        /**
         * @brief Insert an empty line in the CSV file. Used for interpreting data when displaying with python code.
         */
        void InsertEmptyLine();

        void LogFitnessScore(double fitness_value, std::string color="black");

    private:
        std::string m_directory;
        std::string m_text_file;
        std::ofstream m_file;
};