#include "IGeometryData.hpp"

IGeometryData::IGeometryData(Point center_point) : m_center_point{center_point} 
{
}

Point IGeometryData::GetCenterPoint(){
    return m_center_point;
}

void IGeometryData::SetCenterPoint(Point center_point){
    m_center_point = center_point;
}