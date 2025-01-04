#include "item.h"

Item::Item(std::string name, char sprite, sf::Color colour, std::string type, int x, int y) : 
    name(name), sprite(sprite), colour(colour), itemType(type), x(x), y(y) {}

sf::Color Item::getColour() {
    return colour;
}

std::string Item::getName() {
    return name;
}

char Item::getSprite() {
    return sprite;
}

std::string Item::getType() {
    return itemType;
}

int Item::getX() {
    return x;
}

int Item::getY() {
    return y;
}

void Item::setPos(int new_x, int new_y) {
    x = new_x;
    y = new_y;
}