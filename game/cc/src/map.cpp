#include "map.h"
#include "exceptions.h"
#include "logger.h"

cc::Map::Map(const std::string& path, SDL_Renderer* renderer)
    : cc::Object("")
    , _path(path)
    , _renderer(renderer)
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

void cc::Map::render(SDL_Renderer* renderer)
{
    std::vector<Tmx::Layer*> layers = this->_map.GetLayers();
    for(std::vector<Tmx::Layer*>::iterator iter = layers.begin(); iter != layers.end(); ++iter) {
        Tmx::Layer* layer = (*iter);
        if(layer->IsVisible())
            this->drawLayer(renderer, layer);
    }
}
void cc::Map::drawLayer(SDL_Renderer* renderer, Tmx::Layer* layer)
{
    if(layer->GetLayerType() == Tmx::LayerType::TMX_LAYERTYPE_TILE)
        this->drawTileLayer(renderer, (Tmx::TileLayer*)layer);
}
void cc::Map::drawTileLayer(SDL_Renderer* renderer, Tmx::TileLayer* layer)
{
    SDL_Rect srcRect;
    for(int x = 0; x < layer->GetWidth(); x++) {
        for(int y = 0; y < layer->GetHeight(); y++) {
            Tmx::MapTile tile = layer->GetTile(x, y);

            if(tile.gid != 0) {
                cc::Texture* texture = this->_mapTilesets.at(tile.tilesetId);
                const Tmx::Tileset* tileset = this->_map.GetTileset(tile.tilesetId);
                int tileIndex = tile.gid - tileset->GetFirstGid();
                int xxx = tileset->GetTileCount();
                int tileX = tileIndex % tileset->GetColumns(), tileY = tileIndex / tileset->GetColumns();
                srcRect.x = tileset->GetTileWidth() * tileX;
                srcRect.y = tileset->GetTileHeight() * tileY;
                srcRect.w = tileset->GetTileWidth();
                srcRect.h = tileset->GetTileHeight();
                int destX = this->_map.GetTileWidth() * x;
                int destY = this->_map.GetTileHeight() * y;
                texture->render(destX, destY, &srcRect);
            }
        }
    }
}
