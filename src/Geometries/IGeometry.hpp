#pragma once
#include <vector>
#include "CircleData.hpp"
#include<iostream>
#include<fstream>

/**
 * Geometry interface used to create different types of geometries.
 * Before creating a new geometry, it's importat to define the data a geometry will contain.
 * (eg. CircleData)
 */
template<typename GeometryData>
class IGeometry
{
public:
    virtual ~IGeometry() = default;
    /**
     * @brief Check if 2 geometries are intersecting.
     * 
     * @param geometry Pointer to Geometry object.
     * 
     * @return Success of operation. 
     */
    virtual bool IsIntersect(IGeometry *geometry) = 0;

    /**
     * @brief Move 2 geometries when they are intersecting.
     * 
     * @param geometry Pointer to Geometry object.

     */
    virtual void Move(IGeometry *geometry) = 0;

    /**
     * @brief Return center point of Geometry object.
     * 
     * @return Center point.
     */
    Point GetCenterPoint();
    
    /**
     * @brief Return Geometry data object.
     * 
     * @return Geometry data.
     */
    GeometryData GetGeometryData();
    
    /**
     * @brief Set center point of Geometry data.
     * 
     * @param n_center Center point.
     */
    void SetCenterPoint(Point n_center);

protected:
    GeometryData m_geometry_data;
};