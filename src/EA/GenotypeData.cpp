#include "GenotypeData.hpp"
#include "../Geometries/CircleData.hpp"

template<typename GeometryData>
GenotypeData<GeometryData>::GenotypeData(int num_geometries, Range numeric_range, GeometryData geo_data):
m_geometries_number{num_geometries},
m_numeric_range{numeric_range},
m_geometry_data{geo_data}
{

}

template<typename GeometryData>
int GenotypeData<GeometryData>::GetNumberOfGeometries(){
    return m_geometries_number;
}

template<typename GeometryData>
Range GenotypeData<GeometryData>::GetRange(){
    return m_numeric_range;
}

template<typename GeometryData>
GeometryData GenotypeData<GeometryData>::GetGeometryData(){
    return m_geometry_data;
}

template<typename GeometryData>
void GenotypeData<GeometryData>::SetNumberOfGeometries(int n){
     m_geometries_number = n;
}

template<typename GeometryData>
void GenotypeData<GeometryData>::SetRange(Range r){
    m_numeric_range = r;
}

template<typename GeometryData>
void GenotypeData<GeometryData>::SetGeometryData(GeometryData gd){
    m_geometry_data = gd;
}

template class GenotypeData<CircleData>;