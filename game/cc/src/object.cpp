#include "object.h"

std::vector<cc::Object*> cc::Object::objects;
std::vector<cc::Object*> cc::Object::addedObjects;

cc::Object::Object(const std::string& name, SDL_Renderer* renderer)
    : _name(name)
    , _dead(false)
    , _speed(0)
    , _position(cc::Point())
    , _direction(cc::Point(0, 0))
    , _moving(false)
    , _renderer(renderer)
{
    cc::Object::objects.push_back(this);
}

cc::Object::~Object()
{
}

void cc::Object::applyAdd()
{
    for(std::vector<cc::Object*>::iterator iter = addedObjects.begin(); iter != addedObjects.end(); ++iter)
        objects.push_back((*iter));
    addedObjects.clear();
}

void cc::Object::removeDead()
{
    for(std::vector<cc::Object*>::iterator iter = objects.begin(); iter != objects.end();) {
        cc::Object* temp = (*iter);
        if(temp->_dead) {
            objects.erase(iter);
            delete temp;
            temp = NULL;
            iter = objects.begin();

        } else
            ++iter;
    }
}

void cc::Object::removeAll()
{
    for(std::vector<cc::Object*>::iterator iter = objects.begin(); iter != objects.end();) {
        cc::Object* temp = (*iter);
        objects.erase(iter);
        delete temp;
        temp = NULL;
        iter = objects.begin();
    }
}

void cc::Object::renderObjects(const cc::Camera& camera)
{
    for(std::vector<cc::Object*>::iterator iter = objects.begin(); iter != objects.end(); ++iter)
        (*iter)->render(camera);
}

void cc::Object::remove()
{
    this->_dead = true;
}

void cc::Object::update(float deltaTime)
{
    this->_direction.normalize();
}
void cc::Object::startMoving(const Point& direction)
{
    this->_direction = direction;
    this->_moving = true;
}

void cc::Object::stopMoving()
{
    this->_moving = false;
}
void cc::Object::updateObjects(float deltaTime)
{
    for(std::vector<cc::Object*>::iterator iter = objects.begin(); iter != objects.end(); ++iter)
        (*iter)->update(deltaTime);
    applyAdd();
    removeDead();
}

void cc::Object::move(const Point& amount)
{
    this->_position += amount;
}
cc::Direction cc::Object::getDirection() const
{
    float x = this->_direction.getX(), y = this->_direction.getY();
    if(x < 0 && y == 0)
        return cc::Direction::LEFT;
    if(x < 0 && y > 0)
        return cc::Direction::LEFT_DOWN;
    if(x < 0 && y < 0)
        return cc::Direction::LEFT_UP;
    if(x > 0 && y == 0)
        return cc::Direction::RIGHT;
    if(x > 0 && y > 0)
        return cc::Direction::RIGHT_DOWN;
    if(x > 0 && y < 0)
        return cc::Direction::RIGHT_UP;
    if(x == 0 && y > 0)
        return cc::Direction::DOWN;
    if(x == 0 && y < 0)
        return cc::Direction::UP;
    return cc::Direction::LEFT;
}
