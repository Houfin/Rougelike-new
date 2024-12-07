#include "entity.h"

static const int fovMultipliers[4][8] = {
    {1, 0, 0, -1, -1, 0, 0, 1},
    {0, 1, -1, 0, 0, -1, 1, 0},
    {0, 1, 1, 0, 0, -1, -1, 0},
    {1, 0, 0, 1, -1, 0, 0, -1}
};

Entity::Entity(int x, int y, char symbol, sf::Color colour, int light) : x(x), y(y), symbol(symbol), colour(colour), prevX(0), prevY(0), light(light) {
}

int Entity::getX() {
    return x;
}

int Entity::getY() {
    return y;
}

int Entity::getPrevX() {
    return prevX;
}

int Entity::getPrevY() {
    return prevY;
}

char Entity::getSymbol() {
    return symbol;
}

sf::Color Entity::getColour() {
    return colour;
}

int Entity::getLight() {
    return light;
}

void Entity::setLight(int new_light) {
    light = new_light;
}

void Entity::setPos(int new_x, int new_y) {
    x = new_x; 
    y = new_y;
}

void Entity::setPrevPos(int new_x, int new_y) {
    prevX = new_x; 
    prevY = new_y;
}

void Entity::setSymbol(char new_symbol) {
    symbol = new_symbol;
}

void Entity::setColour(sf::Color new_colour) {
    colour = new_colour;
}

void Entity::move(Map* map, int xChange, int yChange, bool repeat) {
    do {
        if (x + xChange < 0 || x + xChange > (map->getWidth() - 1) 
            || x + yChange < 0 || y + yChange > (map->getHeight() - 1)) {
            break;
        }
        Tile tile = map->getTile(getX() + xChange, getY() + yChange);
        if (tile.getBlocksMove()) {
            break;
        }
        setPos(x + xChange, y + yChange);
        calculateFov(map);
    } while (repeat == true);
}

bool Entity::traverseStairs(Map* map) {
    if (map->getTile(x, y).getType() == "stairs") {
        std::pair<int, int> location = map->generateDungeon();
        setPos(location.first, location.second);
        calculateFov(map);
        return true;
    }
    return false;
}

void Entity::calculateFov(Map* map) {
    for (int i = 0; i < map->getWidth(); ++i) {
        for (int j = 0; j < map->getHeight(); ++j) {
            map->getTile(i, j).setVisible(false);
        }
    }
    for (int i = 0; i < 8; i++) {
        recursiveFov(map, 1, 1.0, 0.0, fovMultipliers[0][i],
                fovMultipliers[1][i], fovMultipliers[2][i], fovMultipliers[3][i]);
    }
}

void Entity::recursiveFov(Map* map, int row, float startSlope, float endSlope, int xx, int xy, int yx, int yy) {
    if (startSlope < endSlope) {
        return;
    }
    float nextStartSlope = startSlope;
    for (int i = row; i <= 2 * light; ++i) {
        bool blocked = false;
        for (int dx = -i, dy = -i; dx <= 0; dx++) {
            float lSlope = (dx - 0.5) / (dy + 0.5);
            float rSlope = (dx + 0.5) / (dy - 0.5);
            if (startSlope < rSlope) {
                continue;
            }
            else if (endSlope > lSlope) {
                break;
            }

            int sax = dx * xx + dy * xy;
            int say = dx * yx + dy * yy;
            if ((sax < 0 && (int)std::abs(sax) > x) ||
                (say < 0 && (int)std::abs(say) > y)) {
                    continue;
            }
            int ax = x + sax;
            int ay = y + say;
            if (ax >= map->getWidth() || ay >= map->getHeight()) {
                continue;
            }
            int light2 = light * light;
            if ((int)(dx*dx+dy*dy) < light2 || map->getTile(ax, ay).getLit() == true) {
                map->getTile(ax, ay).setVisible(true);
                map->getTile(ax, ay).setSeen();
            }
            if (blocked == true) {
                if (map->getTile(ax, ay).getBlocksLight() == true) {
                    nextStartSlope = rSlope;
                    continue;
                }
                else {
                    blocked = false;
                    startSlope = nextStartSlope;
                }
            }
            else if (map->getTile(ax, ay).getBlocksLight() == true) {
                blocked = true;
                nextStartSlope = rSlope;
                recursiveFov(map, i+1, startSlope, lSlope, xx, xy, yx, yy);
            }
        }
        if (blocked) {
            break;
        }
    }
}