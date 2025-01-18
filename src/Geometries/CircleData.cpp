#include "CircleData.hpp"
#include<fstream>

CircleData::CircleData(Point center_point, double r_) : 
IGeometryData{center_point}, 
m_radius{r_} {

}

CircleData& CircleData::operator=(const CircleData& circle_data){

    this->m_center_point = circle_data.m_center_point;
    this->m_radius = circle_data.m_radius;

    return *this;
}

bool CircleData::operator==(const CircleData& circle_data) const{
    bool isCenterPoint = this->m_center_point == circle_data.m_center_point;
    bool isRadius = this->m_radius == circle_data.m_radius;

    return isCenterPoint && isRadius;
}

std::ostream& operator<<(std::ostream& os, CircleData cd){
    os << cd.m_center_point <<','<< cd.m_radius;
    return os;
}

std::ofstream& operator<<(std::ofstream& os, CircleData cd){
    os << cd.m_center_point <<','<< cd.m_radius;
    return os;
}

double CircleData::GetRadius(){
    return m_radius;
}

void CircleData::SetRadius(double radius){
    m_radius = radius;
}