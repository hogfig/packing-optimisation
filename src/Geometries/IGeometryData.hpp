#pragma once
#include <iostream>
#include<fstream>

/**
 * @brief Structure defining a 2D point. Has members x and y. 
 */
struct Point
{
    /**
     * @brief Initialise Point object with 2D coordinates at P(0,0).
     */
    Point() : x{0}, y{0}
    {
    }

    /**
     * @brief Initialise Point object with given 2D coordinates.
     * 
     * @param x_ x coordinate.
     * @param y_ y coordinate.
     */
    Point(double x_, double y_) : x{x_}, y{y_}
    {
    }

    friend std::ostream& operator<<(std::ostream& os, Point p)
    {
        os << p.x <<','<< p.y;
        return os;
    }

    friend std::fstream& operator<<(std::fstream& os, Point p)
    {
        os << p.x <<','<< p.y;
        return os;
    }

    bool operator==(const Point& p) const{
        return x == p.x && y == p.y;
    }

    double x;
    double y;
};

/**
 * Interface for constructing geometry data. It contains the center point,
 * and all the methods needed for managing the center point of a geometry.
 * 
 * - m_center_point (x, y)
 */
class IGeometryData{
    public:
        virtual ~IGeometryData() = default;
        IGeometryData() = default;
        /**
         * @brief Construct the circle data object with provided data.
         * 
         * @param center_point Center point of the circle (x, y).
         * @param r_ Radius of circle.
         */
        IGeometryData(Point center_point);

        /**
         * @return Center point of circle.
         */
        Point GetCenterPoint();

        /**
         * @brief Set center point of circle.
         * 
         * @param center_point Center point of circle.
         */
        void SetCenterPoint(Point center_point);

    protected:
        Point m_center_point;
};