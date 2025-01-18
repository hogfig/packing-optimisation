#include "Circle.hpp"
#include<cmath>
#include<iostream>
#include <cmath>

Circle::Circle(CircleData circle_data)
{
   m_geometry_data = circle_data;
}

Circle::~Circle(){
    
}

// Check if 2 circles are intersecting.
bool Circle::IsIntersect(IGeometry<CircleData> *r_circle)
{
    //std::cout << std::fixed;
    double dx = r_circle->GetCenterPoint().x - m_geometry_data.GetCenterPoint().x;
    double dy = r_circle->GetCenterPoint().y - m_geometry_data.GetCenterPoint().y;

    double distance = std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));
    double sum_of_radiuses = m_geometry_data.GetRadius() + r_circle->GetGeometryData().GetRadius();
    
    //Comparing 2 doubles or floats has to incorporate precision.
    if ((sum_of_radiuses - distance) <  0.001)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Move the 2 intersecting circles in such a way they don't intersect any more.
void Circle::Move(IGeometry<CircleData> *r_circle)
{

        double dx = r_circle->GetCenterPoint().x - m_geometry_data.GetCenterPoint().x;
        double dy = r_circle->GetCenterPoint().y - m_geometry_data.GetCenterPoint().y;
        
        //A circle on top of another circle
        if(dx == 0 && dy ==0){
            r_circle->SetCenterPoint(Point(r_circle->GetCenterPoint().x + r_circle->GetGeometryData().GetRadius(), r_circle->GetCenterPoint().y));
            SetCenterPoint(Point(GetCenterPoint().x - GetGeometryData().GetRadius(), GetCenterPoint().y));
            return;
        }

        double hipotenusa = std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));
        double alfa = std::atan2(dy, dx); // in radians

        double new_hipotenusa = r_circle->GetGeometryData().GetRadius() + m_geometry_data.GetRadius();
        double y_displacement = (std::fabs(std::sin(alfa) * new_hipotenusa)-std::fabs(dy))/2;
        double x_displacement = (std::fabs(std::cos(alfa) * new_hipotenusa)-std::fabs(dx))/2;

        Point new_center_point_r(0, 0);
        Point new_center_point_l(0, 0);

        if (r_circle->GetCenterPoint().x > m_geometry_data.GetCenterPoint().x)
        {
            new_center_point_r.x = r_circle->GetCenterPoint().x + x_displacement;
            new_center_point_l.x = m_geometry_data.GetCenterPoint().x - x_displacement;
        }
        else
        {
            new_center_point_r.x = r_circle->GetCenterPoint().x - x_displacement;
            new_center_point_l.x = m_geometry_data.GetCenterPoint().x + x_displacement;
        }

        if (r_circle->GetCenterPoint().y > m_geometry_data.GetCenterPoint().y)
        {
            new_center_point_r.y = r_circle->GetCenterPoint().y + y_displacement;
            new_center_point_l.y = m_geometry_data.GetCenterPoint().y - y_displacement;
        }
        else
        {
            new_center_point_r.y = r_circle->GetCenterPoint().y - y_displacement;
            new_center_point_l.y = m_geometry_data.GetCenterPoint().y + y_displacement;
        }

        r_circle->SetCenterPoint(new_center_point_r);
        SetCenterPoint(new_center_point_l);
}