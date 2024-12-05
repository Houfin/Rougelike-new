#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "map.h"

Room::Room() {};

Room::Room(int startX, int startY, int endX, int endY, int doorX, int doorY) : startX(startX), startY(startY), endX(endX), endY(endY), doorX(doorX), doorY(doorY){
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

int Room::getDoorX() {
    return doorX;
}

int Room::getDoorY() {
    return doorY;
}

void Room::setStart(int x, int y) {
    startX = x;
    startY = y;
}

void Room::setEnd(int x, int y) {
    endX = x;
    endY = y;
}

void Room::setDoor(int x, int y) {
    doorX = x;
    doorY = y;
}

int Room::getCorridorDirection() {
    return corridorDirection;
}

void Room::setCorridorDirection(int corridorDirection) {
    corridorDirection = corridorDirection;
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

Room BSPNode::createRoom(Map* map) {
    int roomWidth = rand() % (width - 6) + 4;
    int roomHeight = rand() % (height - 6) + 4;
    int roomX = x + rand() % (width - roomWidth);
    int roomY = y + rand() % (height - roomHeight);
    int doorX, doorY;
    Room room = Room(roomX, roomY, roomX + roomWidth, roomY + roomHeight, 0, 0);
    //Generate the X and Y values of the door to the room
    if (abs(roomX - map->getWidth() / 2) < abs(roomY - map->getHeight() / 2)) {
        if (roomY > map->getHeight() / 2) {
            doorY = roomY - 1;
            doorX = roomX - 1 + rand() % (roomWidth - 2) + 1;
            room.setCorridorDirection(1);
        }
        else {
            doorY = roomY + roomHeight;
            doorX = roomX - 1 + rand() % (roomWidth - 2) + 1;
            room.setCorridorDirection(1);
        }
    }
    else {
        if (roomX > map->getWidth() / 2) {
            doorX = roomX - 1;
            doorY = roomY - 1 + rand() % (roomHeight - 2) + 1;
            room.setCorridorDirection(0);
        }
        else {
            doorX = roomX + roomWidth;
            doorY = roomY - 1 + rand() % (roomHeight - 2) + 1;
            room.setCorridorDirection(0);
        }
    }
    
    room.setDoor(doorX, doorY);

    for (int y = roomY; y < roomY + roomHeight; ++y) {
        for (int x = roomX; x < roomX + roomWidth; ++x) {
            map->setTile(x, y, false, false, "floor", '.', true);
        }
    }

    std::cout << "A room is made at (" << roomX << ", " << roomY << ") with width " 
        << roomWidth << " and height " << roomHeight << "\n";

    return room;
}

bool BSPNode::createChildren(Map* map, std::vector<Room>* rooms) {
    std::cout << "Creating children for BSPNode at (" << x << ", " << y << ") with width " 
          << width << " and height " << height << "\n";
    if (width <= 30 && height <= 30) {
        return true;
    }

    bool splitHorizontally = (rand() % 2 == 0);
    if (width <= 30) {
        splitHorizontally = true;
    }
    else if (height <= 30) {
        splitHorizontally = false;
    }

    if (splitHorizontally) {
        int split = rand() % (height - 8 * 2) + 8;
        child1 = new BSPNode(x, y, width, split);
        child2 = new BSPNode(x, y + split, width, height - split);
    } 
    else {
        int split = rand() % (width - 8 * 2) + 8;
        child1 = new BSPNode(x, y, split, height);
        child2 = new BSPNode(x + split, y, width - split, height);
    }

    if (child1->createChildren(map, rooms)) {
        rooms->push_back(child1->createRoom(map));
    }

    if (child2->createChildren(map, rooms)) {
        rooms->push_back(child2->createRoom(map));
    }

    return false;
}

void BSPNode::joinChildren(Map* map, std::vector<Room>* rooms) {
    
    for (int i = 1; i < rooms->size(); ++i) {
        //Set start position and end position
        int door1X = rooms->at(i-1).getDoorX();
        int door1Y = rooms->at(i-1).getDoorY();
        int door2X = rooms->at(i).getDoorX();
        int door2Y = rooms->at(i).getDoorY();
        int direction = rooms->at(i).getCorridorDirection();
        int currentX = door1X;
        int currentY = door1Y;
        int counter = 0;
        
        while (currentX != door2X || currentY != door2Y) {
            if (rand() % 2 == 0) {
                while (currentX != door2X) {
                    currentX += (currentX < door2X) ? 1 : -1;
                    counter += 1;

                    if (abs(currentX - door1X) > 6) {
                        currentY += (rand() % 6 == 0) ? 1 : 0;
                        counter += 1;
                    }
                    if (map->getTile(currentX, currentY).getRoom() == true) {
                        break;
                    }
                    map->setTile(currentX, currentY, false, false, "floor", '.', true);
                    if (rand() % 3 == 0) {
                        break;
                    }
                }
            } 
            else {
                while (currentY != door2Y) {
                    currentY += (currentY < door2Y) ? 1 : -1;
                    counter += 1;

                    if (abs(currentY - door1Y) > 6) {
                        counter += 1;
                        currentX += (rand() % 6 == 0) ? 1 : 0;
                    }
                    if (map->getTile(currentX, currentY).getRoom() == true) {
                        break;
                    }

                    map->setTile(currentX, currentY, false, false, "floor", '.', true);
                    if (rand() % 3 == 0) {
                        break;
                    }
                }
            }
            if (map->getTile(currentX, currentY).getRoom() == true && counter > 6) {
                    break;
            }
        }

        map->setTile(door2X, door2Y, false, true, "door", '+', true);
        map->setTile(door1X, door1Y, false, true, "door", '+', true);
    }
}


Tile::Tile(){}

Tile::Tile(bool blocksMove, bool blocksLight, std::string type, char symbol, bool corridorAllowed) : blocksLight(blocksLight), blocksMove(blocksMove), type(type), symbol(symbol), room(room) {
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

char Tile::getSymbol() {
    return symbol;
}

bool Tile::getRoom() {
    return room;
}

void Tile::setSymbol(char new_symbol) {
    symbol = new_symbol;
}

void Tile::setRoom(bool new_room) {
    room = new_room;
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

void Map::setTile(int x, int y, bool blocksMove, bool blocksLight, std::string type, char symbol, bool room) {
    tiles.at(y).at(x) = Tile(blocksMove, blocksLight, type, symbol, room);
}

int Map::getHeight() {
    return height;
}

int Map::getWidth() {
    return width;
}