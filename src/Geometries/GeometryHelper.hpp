#pragma once
#include "IGeometry.hpp"


template<typename GeometryData>
class GeometryHelper{
    typedef std::vector<std::shared_ptr<IGeometry<GeometryData>>> IGeometry_Vector;
    public:
        GeometryHelper() = default;
        ~GeometryHelper() = default;
        void RearangeGeometries(IGeometry_Vector &geometries);
        void MoveObjects(IGeometry_Vector &geometries, IGeometry_Vector &pairs);
        void CollisionCheck(IGeometry_Vector &geometries, IGeometry_Vector &pairs);
        void AllignGeometries(IGeometry_Vector first, IGeometry_Vector second);
};