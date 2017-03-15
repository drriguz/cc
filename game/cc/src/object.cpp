#include "object.h"

std::vector<cc::Object*> cc::Object::objects;
std::vector<cc::Object*> cc::Object::addedObjects;

cc::Object::Object(const std::string& name, SDL_Renderer* renderer)
    : _name(name)
    , _dead(false)
    , _speed(0)
    , _position(cc::Point())
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
    for(std::vector<cc::Object*>::iterator iter = objects.begin(); iter != objects.end(); ++iter)
        (*iter)->update(deltaTime);
    applyAdd();
    removeDead();
}
