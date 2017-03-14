#ifndef _CC_POINT_H_
#define _CC_POINT_H_

namespace cc
{
class Point
{
public:
    Point(float x = 0.0f, float y = 0.0f);
    ~Point();

public:
    float getX();
    float getY();

protected:
    float _x;
    float _y;
};
};
#endif