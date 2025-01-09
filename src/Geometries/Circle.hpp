#pragma once
#include "IGeometry.hpp"
#include "CircleData.hpp"

/**
 * Circle geometry object, containing all the data needed to describe a circle, 
 * and methods to manipulate one.
 */
class Circle: public IGeometry<CircleData>{
    public:
        Circle(CircleData circle_data);
        ~Circle();
        Circle(const Circle& c) = default;
        Circle(Circle&& c) = default;
        
        /**
         * @brief Check if 2 Circles are intersecting.
         * 
         * @param r_circle Pointer to Circle object
         * 
         * @return Success of operation. 
         */
        bool IsIntersect(IGeometry<CircleData> *r_circle) override;

        /**
         * @brief Move 2 circles when they are intersecting.
         * 
         * @param r_circle Pointer to Circle object.
         */
        void Move(IGeometry<CircleData> *r_circle) override;

};
