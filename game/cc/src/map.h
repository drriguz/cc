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
    virtual ~Map();

public:
    virtual void render(const Camera& camera);
    virtual Point projection(int col, int row);

protected:
    void loadMedia();
    void drawLayer(Tmx::Layer* layer, const Camera& camera);
    void drawTileLayer(Tmx::TileLayer* layer, const Camera& camera);
    void drawGrid(const cc::Camera& camera);
protected:
    std::string _path;
    Tmx::Map _map;
    std::vector<Texture*> _mapTilesets;
    bool _showGrid;
};
};
#endif