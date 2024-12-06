#include <SFML/Graphics.hpp>

class Entity {
    private:
    int x;
    int y;
    int prevX;
    int prevY;
    char symbol;
    sf::Color colour;

    public:
    Entity(int, int, char, sf::Color);
    int getX();
    int getPrevX();
    int getPrevY();
    int getY();
    sf::Color getColour();
    void setPos(int, int);
    void setPrevPos(int, int);
    char getSymbol();
    void setSymbol(char);
    void setColour(sf::Color);
};