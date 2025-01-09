#pragma once
#include"IGeometry.hpp"
#include "CircleData.hpp"

class CircleFactory{
    public:
        CircleFactory() = default;
        ~CircleFactory() = default;
        /**
         * Create and return shared pointer of Circle object.
         * 
         * @param circle_data data describing the circle.
         * 
         * @return Shared pointer of the Circle object.
         */
        std::shared_ptr<IGeometry<CircleData>> CreateObject(CircleData circle_data);
};