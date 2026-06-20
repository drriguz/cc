#include "player.h"
#include "logger.h"

cc::Player::Player(const std::string& name, SDL_Renderer* renderer)
    : cc::Object(name, renderer, 120.0f)
    , _movingLeftSprite(cc::Sprite(name, 1, 4, 0.2f))
    , _movingRightSprite(cc::Sprite(name, 2, 4, 0.2f))
    , _movingUpSprite(cc::Sprite(name, 3, 4, 0.2f))
    , _movingDownSprite(cc::Sprite(name, 0, 4, 0.2f))
{
}

cc::Player::~Player()
{
}

void cc::Player::render(const Camera& camera)
{
    cc::Sprite* sprite = this->getCurrentSprite();
    if(sprite != NULL)
        sprite->render(this->_renderer, camera, this->_position, this->_moving);
}
void cc::Player::update(float deltaTime)
{
    cc::Object::update(deltaTime);
    cc::Sprite* sprite = this->getCurrentSprite();
    if(sprite != NULL)
        sprite->update(deltaTime);
}
cc::Sprite* cc::Player::getCurrentSprite()
{
    cc::Direction d = this->getDirection();
    switch(d) {
    case UP:
    case LEFT_UP:
    case RIGHT_UP:
        return &this->_movingUpSprite;
    case DOWN:
    case LEFT_DOWN:
    case RIGHT_DOWN:
        return &this->_movingDownSprite;
    case LEFT:
        return &this->_movingLeftSprite;
    case RIGHT:
        return &this->_movingRightSprite;
    default:
        return &this->_movingDownSprite;
    }
}
