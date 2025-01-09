#include "CircleFactory.hpp"
#include"Circle.hpp"
#include"IGeometry.hpp"

std::shared_ptr<IGeometry<CircleData>> CircleFactory::CreateObject(CircleData circle_data)
{
    return std::make_shared<Circle>(Circle(circle_data));
}
