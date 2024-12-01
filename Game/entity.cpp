#include "entity.h"

Entity::Entity(int x, int y, char symbol, sf::Color colour) : x(x), y(y), symbol(symbol), colour(colour) {
}

int Entity::getX() {
    return x;
}

int Entity::getY() {
    return y;
}

char Entity::getSymbol() {
    return symbol;
}

sf::Color Entity::getColour() {
    return colour;
}

void Entity::setPos(int new_x, int new_y) {
    x = new_x; 
    y = new_y;
}

void Entity::setSymbol(char new_symbol) {
    symbol = new_symbol;
}

void Entity::setColour(sf::Color new_colour) {
    colour = new_colour;
}