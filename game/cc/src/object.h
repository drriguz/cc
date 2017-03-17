#ifndef _CC_OBJECT_H_
#define _CC_OBJECT_H_

#include <string>
#include <vector>
#include <SDL2/SDL.h>

#include "point.h"
#include "camera.h"

namespace cc
{
class Object
{
public:
    Object(const std::string& name, SDL_Renderer* renderer);
    virtual ~Object();

public:
    static std::vector<Object*> objects;
    static std::vector<Object*> addedObjects;
    static void applyAdd();
    static void removeDead();
    static void removeAll();
    static void renderObjects(const Camera& camera);
    static void updateObjects(float deltaTime);

public:
    virtual void remove();
    virtual void update(float deltaTime);
    virtual void render(const Camera& camera) = 0;

public:
    virtual void move(const Point& amount);
    virtual void startMoving(const Point& direction);
    virtual void stopMoving();

protected:
    std::string _name;
    bool _dead;
    float _speed;
    Point _position;
    Point _direction;
    bool _moving;

    SDL_Renderer* _renderer;
};
};
#endif