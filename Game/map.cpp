#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "map.h"

Room::Room(int x, int y) : centerX(x), centerY(y) {
}

int Room::getX() {
    return centerX;
}

int Room::getY() {
    return centerY;
}

void Room::setX(int x) {
    centerX = x;
}

void Room::setY(int y) {
    centerY = y;
}


Node::Node(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {
}

int Node::getHeight() {
    return height;
}

int Node::getWidth() {
    return width;
}

int Node::getX() {
    return x;
}

int Node::getY() {
    return y;
}

Room Node::createRoom(Map* map) {
    int roomWidth = rand() % (width - 4) + 4;
    int roomHeight = rand() % (height - 4) + 4;
    int roomX = x + rand() % (width - roomWidth);
    int roomY = y + rand() % (height - roomHeight);

    for (int y = roomY; y < roomY + roomHeight; ++y) {
        for (int x = roomX; x < roomX + roomWidth; ++x) {
            map->setTile(x, y, false, false, "floor");
        }
    }
    std::cout << "A room is made at (" << roomX << ", " << roomY << ") with width " 
        << roomWidth << " and height " << roomHeight << "\n";

    return Room(roomX, roomY);
}

bool Node::createChildren(Map* map, std::vector<Room>* rooms) {
    std::cout << "Creating children for Node at (" << x << ", " << y << ") with width " 
          << width << " and height " << height << "\n";
    if (width <= 10 && height <= 10) {
        return true;
    }

    bool splitHorizontally = (rand() % 2 == 0);
    if (width <= 10) {
        splitHorizontally = true;
    }
    else if (height <= 10) {
        splitHorizontally = false;
    }

    if (splitHorizontally) {
        int split = rand() % (height - 5 * 2) + 5;
        child1 = new Node(x, y, width, split);
        child2 = new Node(x, y + split, width, height - split);
    } 
    else {
        int split = rand() % (width - 5 * 2) + 5;
        child1 = new Node(x, y, split, height);
        child2 = new Node(x + split, y, width - split, height);
    }

    if (child1->createChildren(map, rooms)) {
        rooms->push_back(child1->createRoom(map));
        std::cout << "Room object created at (" << rooms->at(rooms->size() - 1).getX() << ", " << rooms->at(rooms->size() - 1).getY() << ")" << std::endl; 
    }

    if (child2->createChildren(map, rooms)) {
        rooms->push_back(child2->createRoom(map));
        std::cout << "Room object created at (" << rooms->at(rooms->size() - 1).getX() << ", " << rooms->at(rooms->size() - 1).getY() << ")" << std::endl; 
    }

    return false;
}

void Node::joinChildren(Map* map, std::vector<Room>* rooms) {
    
    for (int i = 1; i < rooms->size(); ++i) {
    // Create an "L"-shaped corridor
        std::cout << "Corridor number " << i << " created" << std::endl;
        for (int x = std::min(rooms->at(i).getX(), rooms->at(i-1).getX()); x <= std::max(rooms->at(i).getX(), rooms->at(i-1).getX()); ++x) {
            map->setTile(x, y, false, false, "floor");
        }
        for (int y = std::min(rooms->at(i).getY(), rooms->at(i-1).getY()); y <= std::max(rooms->at(i).getY(), rooms->at(i-1).getY()); ++y) {
            map->setTile(x, y, false, false, "floor");
        }
    }
}


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