#include <SFML/Graphics.hpp>

class Entity {
    private:
    int x;
    int y;
    char symbol;
    sf::Color colour;

    public:
    Entity(int, int, char, sf::Color);
    int getX();
    int getY();
    sf::Color getColour();
    void setPos(int, int);
    char getSymbol();
    void setSymbol(char);
    void setColour(sf::Color);
};