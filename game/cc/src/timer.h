#ifndef _CC_TIMER_H_
#define _CC_TIMER_H_

#include <SDL2/SDL.h>

namespace cc
{
class Timer
{
public:
    Timer()
        : _lastTime(0.0f)
    {
    }
    ~Timer()
    {
    }

public:
    float getCurrentMillis()
    {
        return SDL_GetTicks();
    }
    float getDeltaTime()
    {
        float now = getCurrentMillis();
        float delta = now - this->_lastTime;
        this->_lastTime = now;
        return delta;
    }

protected:
    float _lastTime;
};
};

#endif