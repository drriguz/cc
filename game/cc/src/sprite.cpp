#include "sprite.h"
#include "sprite_texture.h"
#include "exceptions.h"

std::map<std::string, cc::SpriteTexture*> cc::SpriteTexture::textures;

cc::Sprite::Sprite(const std::string& name)
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
}

void cc::Sprite::render(SDL_Renderer* renderer, const Camera& camera, const Point& position)
{
    SDL_Rect dest = {0, 0, 90, 90};
    SDL_Rect src = {0, 0, 90, 90};
    this->_texture->render(src, dest);
}
