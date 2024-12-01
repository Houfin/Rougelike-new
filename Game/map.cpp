#include <string>
#include <vector>
#include "map.h"

Tile::Tile(){}

Tile::Tile(bool blocksMove, bool blocksLight, std::string type) : blocksLight(blocksLight), blocksMove(blocksMove), type(type) {
}

bool Tile::getBlocksLight() {
    return blocksLight;
}

bool Tile::getBlocksMove() {
    return blocksMove;
}

std::string Tile::getType() {
    return type;
}

void Tile::setBlocksLight(bool new_blocksLight) {
    blocksLight = new_blocksLight;
}

void Tile::setBlocksMove(bool new_blocksMove) {
    blocksMove = new_blocksMove;
}

void Tile::setType(std::string new_type) {
    type = new_type;
}


Map::Map(int width, int height) : width(width), height(height), tiles(height, std::vector<Tile>(width)){
}

Tile& Map::getTile(int x, int y) {
    return tiles.at(y).at(x);
}

void Map::setTile(int x, int y, bool blocksMove, bool blocksLight, std::string type) {
    tiles.at(y).at(x) = Tile(blocksMove, blocksLight, type);
}

int Map::getHeight() {
    return height;
}

int Map::getWidth() {
    return width;
}

void Map::generateMap() {
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            setTile(i, j, false, false, "floor");
        }
    }
}