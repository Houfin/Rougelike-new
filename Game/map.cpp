#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "map.h"

Room::Room() {};

Room::Room(int startX, int startY, int endX, int endY) : startX(startX), startY(startY), endX(endX), endY(endY) {
}

bool Room::getStairs() {
    return stairs;
}

void Room::setStairs(bool new_stairs) {
    stairs = new_stairs;
}

int Room::getStartX() {
    return startX;
}

int Room::getStartY() {
    return startY;
}

int Room::getEndX() {
    return endX;
}

int Room::getEndY() {
    return endY;
}

void Room::setStart(int x, int y) {
    startX = x;
    startY = y;
}

void Room::setEnd(int x, int y) {
    endX = x;
    endY = y;
}


BSPNode::BSPNode(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {
}

int BSPNode::getHeight() {
    return height;
}

int BSPNode::getWidth() {
    return width;
}

int BSPNode::getX() {
    return x;
}

int BSPNode::getY() {
    return y;
}

Room BSPNode::createRoom(Map* map, int roomNumber) {
    int roomWidth = rand() % (width - 8) + 4;
    int roomHeight = rand() % (height - 8) + 4;
    int roomX = x + (width - roomWidth) / 2;
    int roomY = y + (height - roomHeight) / 2;
    bool lit = rand() % 6; 
    Room room = Room(roomX, roomY, roomX + roomWidth, roomY + roomHeight);

    for (int y = roomY; y < roomY + roomHeight; ++y) {
        for (int x = roomX; x < roomX + roomWidth; ++x) {
            map->setTile(x, y, false, false, "floor", ".");
            if (lit == true) {
                map->getTile(x, y).setLit(lit);
            }
        }
    }

    for (int y = roomY - 1; y <= roomY + roomHeight; ++y) {
        for (int x = roomX - 1; x <= roomX + roomWidth; ++x) {
            // Check if it"s a border but not inside the room
            if (x == roomX - 1 || x == roomX + roomWidth || y == roomY - 1 || y == roomY + roomHeight) {
                map->setTile(x, y, true, true, "room wall", "#");
            }
        }
    }

    return room;
}

bool BSPNode::createChildren(Map* map, std::vector<Room>* rooms, bool splitHorizontally) {
    if (width <= 18 && height <= 18) {
        return true;
    }

    if (width <= 18) {
        splitHorizontally = true;
    }
    else if (height <= 18) {
        splitHorizontally = false;
    }

    if (splitHorizontally) {
        int split = rand() % (height - 9 * 2) + 9;
        child1 = new BSPNode(x, y, width, split);
        child2 = new BSPNode(x, y + split, width, height - split);
    } 
    else {
        int split = rand() % (width - 9 * 2) + 9;
        child1 = new BSPNode(x, y, split, height);
        child2 = new BSPNode(x + split, y, width - split, height);
    }

    if (child1->createChildren(map, rooms, !splitHorizontally) && rand() % 6 != 0) {
        rooms->push_back(child1->createRoom(map, rooms->size()));
    }

    if (child2->createChildren(map, rooms, !splitHorizontally) && rand() % 6 != 0) {
        rooms->push_back(child2->createRoom(map, rooms->size()));
    }

    joinChildren(map);

    return false;
}

void BSPNode::joinChildren(Map* map) {
    int currentX = child1->getX() + child1->getWidth() / 2;
    int currentY = child1->getY() + child1->getHeight() / 2;
    int endX = child2->getX() + child2->getWidth() / 2;
    int endY = child2->getY() + child2->getHeight() / 2;
    bool prevdoor = false; 
    int prevX = -1;
    int prevY = -1;

    while (currentX != endX || currentY != endY) {
        if (map->getTile(currentX, currentY).getType() == "room wall" or map->getTile(currentX, currentY).getType() == "door") {
            if (prevdoor == false) {
                map->setTile(currentX, currentY, false, false, "door", "+");
                prevdoor = true;
            }
            prevX = currentX;
            prevY = currentY;
        }
        else {
            if (prevdoor == true && map->getTile(currentX, currentY).getType() == "wall") {
                if (map->getTile(currentX, currentY).getType() != "floor") {
                    map->setTile(prevX, prevY, false, false, "door", "+");
                    prevdoor = false;
                }
            }
            map->setTile(currentX, currentY, false, false, "floor", ".");
        }
        if (currentX != endX) {
            currentX += (endX > currentX) ? 1 : -1;
        }

        if (currentY != endY) {
            currentY += (endY > currentY) ? 1 : -1;
        }
    }
}


Tile::Tile(){}

Tile::Tile(bool blocksMove, bool blocksLight, std::string type, std::string symbol) : blocksLight(blocksLight), blocksMove(blocksMove), type(type), symbol(symbol) {
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

std::string Tile::getSymbol() {
    return symbol;
}

bool Tile::getVisible() {
    return visible;
}

bool Tile::getLit() {
    return lit;
}

bool Tile::getSeen() {
    return seen;
}

void Tile::setSeen() {
    seen = true;
}

void Tile::setVisible(bool new_visible) {
    visible = new_visible;
}

void Tile::setLit(bool new_lit) {
    lit = new_lit;
}

void Tile::setSymbol(std::string new_symbol) {
    symbol = new_symbol;
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

std::pair<int, int> Map::generateDungeon() {

    // Every tile at the start is a wall.  
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            setTile(i, j, true, true, "wall", "#");
        }
    }

    BSPNode parent = BSPNode(1, 1, width - 1, height - 1);
    std::vector<Room> rooms;
    parent.createChildren(this, &rooms, (height > width));
    parent.joinChildren(this);

    makeStairs(&rooms);
    level += 1;
    std::pair<int, int> playerLoc;
    Room playerStart = rooms.at(rand() % rooms.size());
    playerLoc = {playerStart.getStartX() + (playerStart.getEndX() - playerStart.getStartX()) / 2, playerStart.getStartY() + (playerStart.getEndY() - playerStart.getStartY()) / 2};
    return playerLoc;
}

int Map::getLevel() {
    return level;
}

void Map::makeStairs(std::vector<Room>* rooms) {
    Room stairsRoom = rooms->at(rand() % rooms->size());
    stairsRoom.setStairs(true);
    setTile(stairsRoom.getStartX() + rand() % (stairsRoom.getEndX() - 
        stairsRoom.getStartX()), stairsRoom.getStartY() + rand() % (stairsRoom.getEndY() - stairsRoom.getStartY()),
            false, false, "stairs", ">");

    while (rand() % 2 != 0) {
        stairsRoom = rooms->at(rand() % rooms->size());
        if (stairsRoom.getStairs() == false) {
            stairsRoom.setStairs(true);
            setTile(stairsRoom.getStartX() + rand() % (stairsRoom.getEndX() - 
                    stairsRoom.getStartX()), stairsRoom.getStartY() + rand() % (stairsRoom.getEndY() - stairsRoom.getStartY()),
                        false, false, "stairs", ">");
        }
    }
}


Tile& Map::getTile(int x, int y) {
    return tiles.at(y).at(x);
}

void Map::setTile(int x, int y, bool blocksMove, bool blocksLight, std::string type, std::string symbol) {
    bool lit = getTile(x, y).getLit();
    tiles.at(y).at(x) = Tile(blocksMove, blocksLight, type, symbol);
    tiles.at(y).at(x).setLit(lit);
}

int Map::getHeight() {
    return height;
}

int Map::getWidth() {
    return width;
}