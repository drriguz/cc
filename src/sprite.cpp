#include "sprite.h"
#include "sprite_texture.h"
#include "exceptions.h"
#include "logger.h"

std::map<std::string, cc::SpriteTexture*> cc::SpriteTexture::textures;

cc::Sprite::Sprite(const std::string& name, int groupIndex, int frameCount, float frameDuration)
    : _name(name)
    , _texture(NULL)
    , _groupIndex(groupIndex)
    , _currentFrame(0)
    , _frameCount(frameCount)
    , _frameInterval(frameDuration)
    , _frameTimeRemaining(frameDuration)
{
    this->_texture = cc::SpriteTexture::textures[name];
    if(this->_texture == NULL)
        throw cc::Exception("Texture not found:", name.c_str());
}

cc::Sprite::~Sprite()
{
}

void cc::Sprite::update(float deltaTime)
{
    this->_frameTimeRemaining -= deltaTime;
    if(this->_frameTimeRemaining <= 0) {
        ++_currentFrame;
        _currentFrame %= _frameCount;
        _frameTimeRemaining = _frameInterval;
    }
}

void cc::Sprite::render(SDL_Renderer* renderer, const Camera& camera, const Point& position, bool animate)
{
    SDL_Rect dest = {
        (int)position.getX(), (int)position.getY(), this->_texture->getTileWidth(), this->_texture->getTileHeight()
    };

    int frame = animate ? this->_currentFrame : 0;
    SDL_Rect src = { this->_texture->getTileWidth() * frame,
                     this->_texture->getTileHeight() * this->_groupIndex,
                     this->_texture->getTileWidth(),
                     this->_texture->getTileHeight() };
    camera.apply(src, &dest);
    this->_texture->render(src, dest);
}
