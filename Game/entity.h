#include <SFML/Graphics.hpp>
#include "map.h"

class Entity {
    private:
    int x;
    int y;
    int prevX;
    int prevY;
    char symbol;
    sf::Color colour;
    int light;

    public:
    Entity(int, int, char, sf::Color, int);
    int getX();
    int getPrevX();
    int getPrevY();
    int getY();
    int getLight();
    sf::Color getColour();
    void setPos(int, int);
    void setPrevPos(int, int);
    void setLight(int);
    char getSymbol();
    void setSymbol(char);
    void setColour(sf::Color);
    void move(Map*, int, int, bool);
    bool traverseStairs(Map*);
    void calculateFov(Map*);
    void recursiveFov(Map*, int, float, float, int, int, int, int);
};