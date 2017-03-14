#ifndef _CC_MAP_H_
#define _CC_MAP_H_

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <tmxparser/Tmx.h>

#include "object.h"
#include "texture.h"

namespace cc
{

class Map : public Object
{
public:
    Map(const std::string& path, SDL_Renderer* renderer);
    ~Map();

public:
    virtual void render(SDL_Renderer* renderer);

protected:
    //static void drawPolyLine(SDL_Renderer* renderer, float* points[], int pointCount, int x, int y);
    //static void drawPolygon(SDL_Renderer* renderer, float* points[], int pointCount, int x, int y);
    //void drawObjects(SDL_renderer* renderer);
    void loadMedia();
    void drawLayer(SDL_Renderer* renderer, Tmx::Layer* layer);
    void drawTileLayer(SDL_Renderer* renderer, Tmx::TileLayer* layer);
protected:
    std::string _path;
    Tmx::Map _map;
    std::vector<Texture*> _mapTilesets;
    
    SDL_Renderer* _renderer;
};
};
#endif