#include"IGeometry.hpp"

template<typename GeometryData>
void IGeometry<GeometryData>::SetCenterPoint(Point n_center){
    m_geometry_data.SetCenterPoint(n_center);
}

template<typename GeometryData>
Point IGeometry<GeometryData>::GetCenterPoint(){
    return m_geometry_data.GetCenterPoint();
}

template<typename GeometryData>
GeometryData IGeometry<GeometryData>::GetGeometryData(){
    return m_geometry_data;
}


template class IGeometry<CircleData>;