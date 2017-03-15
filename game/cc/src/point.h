#ifndef _CC_POINT_H_
#define _CC_POINT_H_

namespace cc
{
class Point
{
public:
    Point(float x = 0.0f, float y = 0.0f)
        : _x(x)
        , _y(y)
    {
    }
    ~Point(){};

public:
    float getX() const
    {
        return this->_x;
    };
    float getY() const
    {
        return this->_y;
    }
    void setX(float x)
    {
        this->_x = x;
    }
    void setY(float y)
    {
        this->_y = y;
    }
    
    Point operator +(const Point& v){
        Point p;
        p._x = _x + v._x;
        p._y = _y + v._y;
        return p;
    }

protected:
    float _x;
    float _y;
};
};
#endif