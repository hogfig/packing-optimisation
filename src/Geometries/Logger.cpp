#include"Logger.hpp"
#include "CircleData.hpp"
#include "IGeometry.hpp"

template<typename GeometryData>
Logger<GeometryData>::Logger(std::string directory, std::string filename) : 
m_directory(directory), 
m_text_file(filename), 
m_file(directory+filename)
{
}

template<typename GeometryData>
Logger<GeometryData>::~Logger(){
    m_file.close();
}

template<typename GeometryData>
void Logger<GeometryData>::LogObjectData(std::shared_ptr<IGeometry<GeometryData>> obj, std::string color){
    
    m_file << obj->GetGeometryData() << "," ;
    m_file<< color;
    m_file << std::endl;
}

template<typename GeometryData>
void Logger<GeometryData>::LogVectorData(std::vector<std::shared_ptr<IGeometry<GeometryData>>> v_obj, std::string color){
    for(auto &i : v_obj){
        LogObjectData(i, color);
    }
}

template<typename GeometryData>
void Logger<GeometryData>::InsertEmptyLine(){
    m_file << std::endl;
}

template<typename GeometryData>
void Logger<GeometryData>::LogDoubleValue(double d_value, std::string color){
    m_file << d_value << "," ;
    m_file<< color;
    m_file << std::endl;
}

template class Logger<CircleData>;