#pragma once
#include <iostream>
#include<fstream>
#include "IGeometryData.hpp"
/**
 * Contains all data needed to describe a circle.
 * - m_center_point (x, y)
 * - m_radius
 */
class CircleData : public IGeometryData{
    public:
        CircleData() = default;
        ~CircleData() = default;

        /**
         * @brief Construct the circle data object with provided data.
         * 
         * @param center_point Center point of the circle (x, y).
         * @param r_ Radius of circle.
         */
        CircleData(Point center_point, double r_);

        /**
         * @return Radius of circle.
         */
        double GetRadius();

        /**
         * @brief Set radius of circle.
         * 
         * @param radius Radius of circle.
         */
        void SetRadius(double radius);

        CircleData& operator=(const CircleData& circle_data);
        bool operator==(const CircleData& obj) const;
        friend std::ostream& operator<<(std::ostream& os, const CircleData cd);
        friend std::ofstream& operator<<(std::ofstream& os, const CircleData cd);

    private:
        double m_radius;
};