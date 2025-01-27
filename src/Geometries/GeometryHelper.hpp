#pragma once
#include "IGeometry.hpp"

/**
 * A GeometryHelper class is a helper class designed for abstracting geometry operations.
 */
template<typename GeometryData>
class GeometryHelper{
    typedef std::vector<std::shared_ptr<IGeometry<GeometryData>>> IGeometry_Vector;
    public:
        GeometryHelper() = default;
        ~GeometryHelper() = default;

        /**
         * @brief Fucntion that rearanges geometries in such a way that they are not coliding with each other.
         * 
         * @param geometries vector of geometries to be rearanged. 
         */
        void RearangeGeometries(IGeometry_Vector &geometries);

        /**
         * @brief Alligns two groups of geometries in such a way that their center of mass is located a (0,0).
         * 
         * @param first Geometry vector
         * @param second Geometry vector
         * 
         * @note It's not two geometries but two geometry vectors. It's getting the center of mass of a respective 
         * geometry vector by getting the mean value of all center points. Finally shifting all geometries to the (0,0)
         * center of mass point.
         */
        void AllignGeometries(IGeometry_Vector first, IGeometry_Vector second);

    protected:

        /**
         * @brief Check for collisions and fill the pairs vector with pairs of colliding geometries.
         * 
         * @param geometries vector of geometries to be checked. 
         * @param pairs pairs of geometries that are colliding. 
         */
        void CollisionCheck(IGeometry_Vector &geometries, IGeometry_Vector &pairs);

        /**
         * @brief Fucntion that moves pairs of geometries so that they don't coliding with each other.
         * 
         * @param pairs pairs of geometries to be moved. 
         */
        void MoveObjects(IGeometry_Vector &pairs);
};