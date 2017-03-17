#ifndef _CC_SPRITE_H_
#define _CC_SPRITE_H_

#include <string>
#include <SDL2/SDL.h>

#include "point.h"
#include "sprite_texture.h"
#include "camera.h"

namespace cc
{
class Sprite
{
public:
    Sprite(const std::string& name);
    ~Sprite();

public:
    void update(float deltaTime);
    void render(SDL_Renderer* renderer, const Camera& camera, const Point& position);

protected:
    SpriteTexture* _texture;    
    int _groupIndex;
    int _currentFrame;
    int _frameCount;
    float _frameInterval;
    float _frameTimeRemaining;
};
};
#endif