#include "point.h"

cc::Point::Point(float x, float y)
    : _x(x)
    , _y(y)
{
}

cc::Point::~Point()
{
}

float cc::Point::getX()
{
    return this->_x;
}

float cc::Point::getY()
{
    return this->_y;
}
