#include "player.h"
#include "logger.h"

cc::Player::Player(const std::string& name, SDL_Renderer* renderer)
    : cc::Object(name, renderer)
    , _movingLeftSprite(Sprite(name))
{
}

cc::Player::~Player()
{
}

void cc::Player::render(const Camera& camera)
{
    this->_movingLeftSprite.render(this->_renderer, camera, cc::Point(0, 0));
}
