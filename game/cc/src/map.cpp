#include "map.h"
#include "exceptions.h"
#include "logger.h"

cc::Map::Map(const std::string& path, SDL_Renderer* renderer)
    : cc::Object("", renderer)
    , _path(path)
    , _showGrid(false)
{
    this->_map.ParseFile(this->_path);
    if(this->_map.HasError())
        throw cc::Exception("Failed to parse map:", this->_map.GetErrorText().c_str());
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
}

void cc::Map::loadMedia()
{
    std::vector<Tmx::Tileset*> tilesets = this->_map.GetTilesets();
    for(unsigned int i = 0; i < tilesets.size(); i++) {
        Tmx::Tileset* tileset = tilesets.at(i);
        cc::Texture* texture = new cc::Texture(this->_renderer);
        this->_mapTilesets.push_back(texture);
        if(!texture->loadFromFile(tileset->GetImage()->GetSource()))
            throw cc::Exception("Failed to load image:", tileset->GetImage()->GetSource().c_str());
    }
}

void cc::Map::render(const cc::Camera& camera)
{
    std::vector<Tmx::Layer*> layers = this->_map.GetLayers();
    for(std::vector<Tmx::Layer*>::iterator iter = layers.begin(); iter != layers.end(); ++iter) {
        Tmx::Layer* layer = (*iter);
        if(layer->IsVisible())
            this->drawLayer(layer, camera);
    }
    this->drawGrid(camera);
}
void cc::Map::drawLayer(Tmx::Layer* layer, const cc::Camera& camera)
{
    if(layer->GetLayerType() == Tmx::LayerType::TMX_LAYERTYPE_TILE)
        this->drawTileLayer((Tmx::TileLayer*)layer, camera);
}
void cc::Map::drawTileLayer(Tmx::TileLayer* layer, const cc::Camera& camera)
{
    SDL_Rect srcRect, destRect;
    int offset = (this->_map.GetTileWidth() / 2.0f) * (_map.GetHeight()) / 2;
    for(int x = 0; x < layer->GetWidth(); x++) {
        for(int y = 0; y < layer->GetHeight(); y++) {
            Tmx::MapTile tile = layer->GetTile(x, y);

            if(tile.gid != 0) {
                cc::Texture* texture = this->_mapTilesets.at(tile.tilesetId);
                const Tmx::Tileset* tileset = this->_map.GetTileset(tile.tilesetId);
                int tileIndex = tile.gid - tileset->GetFirstGid();
                // TODO: if map version < 0.15 then GetColumns() returns 0
                int tileX = tileIndex % tileset->GetColumns(), tileY = tileIndex / tileset->GetColumns();
                srcRect.x = tileset->GetTileWidth() * tileX;
                srcRect.y = tileset->GetTileHeight() * tileY;
                srcRect.w = tileset->GetTileWidth();
                srcRect.h = tileset->GetTileHeight();
                Point p = this->projection(x, y);
                destRect.x = p.getX();
                destRect.y = p.getY();
                if(this->_map.GetOrientation() == Tmx::MapOrientation::TMX_MO_ISOMETRIC)
                    destRect.x += offset;

                destRect.x -= tileset->GetTileOffset()->GetX();
                destRect.y -= tileset->GetTileOffset()->GetY();

                camera.apply(srcRect, &destRect);

                texture->render(srcRect, destRect);
            }
        }
    }
}
cc::Point cc::Map::projection(int x, int y)
{
    Point p;
    if(this->_map.GetOrientation() == Tmx::MapOrientation::TMX_MO_ISOMETRIC) {
        // isometric
        // x = (tile_width /2)*(i-j)
        // y = (tile_height/2)*(i+j)
        // i = 0.5*(y/(tile_height/2)+x/(tile_width/2))
        // j = 0.5*(y/(tile_height/2)-x/(tile_width/2))

        p.setX((this->_map.GetTileWidth() / 2.0f) * (x - y));
        p.setY((this->_map.GetTileHeight() / 2.0f) * (x + y));
    }
    if(this->_map.GetOrientation() == Tmx::MapOrientation::TMX_MO_ORTHOGONAL) {
        p.setX(this->_map.GetTileWidth() * x);
        p.setY(this->_map.GetTileHeight() * y);
    }
    return p;
}
void cc::Map::drawGrid(const cc::Camera& camera)
{
    int mapOffset = (this->_map.GetTileWidth() / 2.0f) * (_map.GetHeight()) / 2;
    float tileOffset = this->_map.GetTileWidth() / 2.0f;
    int offset = tileOffset;
    if(this->_map.GetOrientation() == Tmx::MapOrientation::TMX_MO_ISOMETRIC)
        offset += mapOffset;
    SDL_SetRenderDrawColor(this->_renderer, 0x5E, 0x00, 0x00, 0x11);
    for(int x = 0; x <= this->_map.GetWidth(); x++) {
        Point p1 = this->projection(x, 0);
        Point p2 = this->projection(x, _map.GetHeight());

        p1.setX(p1.getX() + offset);
        p2.setX(p2.getX() + offset);
        camera.apply(&p1);
        camera.apply(&p2);
        SDL_RenderDrawLine(this->_renderer, p1.getX(), p1.getY(), p2.getX(), p2.getY());
    }
    for(int y = 0; y <= _map.GetHeight(); y++) {
        Point p1 = this->projection(0, y);
        Point p2 = this->projection(_map.GetWidth(), y);

        p1.setX(p1.getX() + offset);
        p2.setX(p2.getX() + offset);
        camera.apply(&p1);
        camera.apply(&p2);
        SDL_RenderDrawLine(this->_renderer, p1.getX(), p1.getY(), p2.getX(), p2.getY());
    }
}
