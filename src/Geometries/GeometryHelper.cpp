#include "GeometryHelper.hpp"
#include "IGeometry.hpp"
#include "CircleData.hpp"

namespace{
    template<typename GeometryData>
    Point findCenterOfMass(std::vector<std::shared_ptr<IGeometry<GeometryData>>> geometries)
    {
        Point cp;
        double x_sum{0};
        double y_sum{0};
        for(const auto &geometry : geometries)
        {
            auto centerPoint = geometry->GetCenterPoint();
            x_sum += centerPoint.x;
            y_sum += centerPoint.y;
        }

        cp.x = x_sum / geometries.size();
        cp.y = y_sum / geometries.size();

        return cp;
    }
};

template<typename GeometryData>
void GeometryHelper<GeometryData>::RearangeGeometries(IGeometry_Vector &geometries){
    IGeometry_Vector pairs;
    do
    {
        CollisionCheck(geometries, pairs);
        MoveObjects(geometries, pairs);
        pairs.erase(pairs.begin(), pairs.end());
        CollisionCheck(geometries, pairs);
    } while (pairs.size() != 0);
}

template<typename GeometryData>
void GeometryHelper<GeometryData>::MoveObjects(IGeometry_Vector &geometries, IGeometry_Vector &pairs)
{
    if (pairs.size() > 0)
    {
        for (int i = 0; i < pairs.size() - 1; i++)
        {
            if (pairs[i]->IsIntersect(pairs[i + 1].get()))
            {
                pairs[i]->Move(pairs[i + 1].get());
            }
        }
    }
}

template<typename GeometryData>
void GeometryHelper<GeometryData>::CollisionCheck(IGeometry_Vector&geometries, IGeometry_Vector &pairs)
{
    // check for collisions and make collision pairs
    for (int i = 0; i < geometries.size(); i++)
    {
        for (int j = i + 1; j < geometries.size(); j++)
        {
            if (geometries[i]->IsIntersect(geometries[j].get()))
            {
                pairs.push_back(geometries[i]);
                pairs.push_back(geometries[j]);
            }
        }
    }
}

template<typename GeometryData>
void GeometryHelper<GeometryData>::AllignGeometries(IGeometry_Vector first_geometries, IGeometry_Vector second_geometries)
{
    Point anchorPoint = Point(0,0);
    Point firstGeometryCP = findCenterOfMass(first_geometries);
    double dx = anchorPoint.x - firstGeometryCP.x ;
    double dy = anchorPoint.y - firstGeometryCP.y ;
    for(auto& geometry : first_geometries){
        auto center = geometry->GetCenterPoint();
        geometry->SetCenterPoint(Point(center.x + dx, center.y + dy));
    }

    Point secondGeometryCP = findCenterOfMass(second_geometries);
    dx = anchorPoint.x - secondGeometryCP.x ;
    dy = anchorPoint.y - secondGeometryCP.y ;
    for(auto& geometry : second_geometries){
        auto center = geometry->GetCenterPoint();
        geometry->SetCenterPoint(Point(center.x + dx, center.y + dy));
    }
}

template class GeometryHelper<CircleData>;