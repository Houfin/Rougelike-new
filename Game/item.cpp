#include "item.h"
#include <fstream>
#include <sstream>

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

Item getItemFromFile(int level) {
    std::ifstream ItemFile("./itemLists/CellarItems.csv");;

    std::string line;
    std::vector<std::string> row, lines;
    while (std::getline(ItemFile, line)) {
        lines.push_back(line);
    }
    
    int randomIndex = rand() % lines.size();
    line = lines[randomIndex];

    std::stringstream s(line);
    std::string value;

    row.clear();
    while (std::getline(s, value, ',')) {
        row.push_back(value);
    }

    ItemFile.close();

    return Item( (std::string) row[0], (char) row[1], (sf::Color(row[2]), (std::string) row[3], 0, 0);
} 