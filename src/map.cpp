#include "map.h"
#include "exceptions.h"
#include "logger.h"

cc::Map::Map(const std::string& path, SDL_Renderer* renderer)
    : cc::Object("", renderer)
    , _path(path)
    , _map(NULL)
    , _showGrid(false)
{
    this->_map = tmx_load(this->_path.c_str());
    if(!this->_map)
        throw cc::Exception("Failed to parse map:", this->_path.c_str());
    this->loadMedia();
}

cc::Map::~Map()
{
    for(std::vector<cc::Texture*>::iterator iter = this->_mapTilesets.begin(); iter < this->_mapTilesets.end();) {
        cc::Texture* temp = (*iter);
        this->_mapTilesets.erase(iter);
        delete temp;
        iter = this->_mapTilesets.begin();
    }
    if(this->_map)
        tmx_map_free(this->_map);
}

void cc::Map::loadMedia()
{
    tmx_tileset_list* ts_list = this->_map->ts_head;
    while(ts_list) {
        tmx_tileset* tileset = ts_list->tileset;
        cc::Texture* texture = new cc::Texture(this->_renderer);
        this->_mapTilesets.push_back(texture);
        if(tileset->image && !texture->loadFromFile(tileset->image->source))
            throw cc::Exception("Failed to load image:", tileset->image->source);
        ts_list = ts_list->next;
    }
}

void cc::Map::render(const cc::Camera& camera)
{
    tmx_layer* layer = this->_map->ly_head;
    while(layer) {
        if(layer->visible)
            this->drawLayer(layer, camera);
        layer = layer->next;
    }
    this->drawGrid(camera);
}

void cc::Map::drawLayer(tmx_layer* layer, const cc::Camera& camera)
{
    if(layer->type == L_LAYER)
        this->drawTileLayer(layer, camera);
}

void cc::Map::drawTileLayer(tmx_layer* layer, const cc::Camera& camera)
{
    SDL_Rect srcRect, destRect;
    int offset = (this->_map->tile_width / 2.0f) * (_map->height) / 2;

    for(unsigned int x = 0; x < _map->width; x++) {
        for(unsigned int y = 0; y < _map->height; y++) {
            unsigned int idx = x + y * _map->width;
            uint32_t gid = layer->content.gids[idx];
            if(gid == 0) continue;

            // Find the tileset for this gid
            tmx_tileset* tileset = NULL;
            unsigned int firstgid = 0;
            tmx_tileset_list* ts = this->_map->ts_head;
            while(ts) {
                if(gid >= ts->firstgid) {
                    tileset = ts->tileset;
                    firstgid = ts->firstgid;
                }
                ts = ts->next;
            }
            if(!tileset) continue;

            unsigned int local_gid = gid - firstgid;
            unsigned int columns = tileset->image ? (tileset->image->width / tileset->tile_width) : 1;
            unsigned int tileX = local_gid % columns;
            unsigned int tileY = local_gid / columns;

            srcRect.x = tileset->tile_width * tileX;
            srcRect.y = tileset->tile_height * tileY;
            srcRect.w = tileset->tile_width;
            srcRect.h = tileset->tile_height;

            Point p = this->projection(x, y);
            destRect.x = p.getX();
            destRect.y = p.getY();
            if(this->_map->orient == O_ISO)
                destRect.x += offset;

            destRect.x -= tileset->x_offset;
            destRect.y -= tileset->y_offset;

            camera.apply(srcRect, &destRect);

            cc::Texture* texture = this->_mapTilesets.at(0);
            texture->render(srcRect, destRect);
        }
    }
}

cc::Point cc::Map::projection(int x, int y)
{
    Point p;
    if(this->_map->orient == O_ISO) {
        p.setX((this->_map->tile_width / 2.0f) * (x - y));
        p.setY((this->_map->tile_height / 2.0f) * (x + y));
    }
    if(this->_map->orient == O_ORT) {
        p.setX(this->_map->tile_width * x);
        p.setY(this->_map->tile_height * y);
    }
    return p;
}

void cc::Map::drawGrid(const cc::Camera& camera)
{
    int mapOffset = (this->_map->tile_width / 2.0f) * (_map->height) / 2;
    float tileOffset = this->_map->tile_width / 2.0f;
    int offset = tileOffset;
    if(this->_map->orient == O_ISO)
        offset += mapOffset;
    SDL_SetRenderDrawColor(this->_renderer, 0x5E, 0x00, 0x00, 0x11);
    for(unsigned int x = 0; x <= this->_map->width; x++) {
        Point p1 = this->projection(x, 0);
        Point p2 = this->projection(x, _map->height);

        p1.setX(p1.getX() + offset);
        p2.setX(p2.getX() + offset);
        camera.apply(&p1);
        camera.apply(&p2);
        SDL_RenderDrawLine(this->_renderer, p1.getX(), p1.getY(), p2.getX(), p2.getY());
    }
    for(unsigned int y = 0; y <= _map->height; y++) {
        Point p1 = this->projection(0, y);
        Point p2 = this->projection(_map->width, y);

        p1.setX(p1.getX() + offset);
        p2.setX(p2.getX() + offset);
        camera.apply(&p1);
        camera.apply(&p2);
        SDL_RenderDrawLine(this->_renderer, p1.getX(), p1.getY(), p2.getX(), p2.getY());
    }
}
