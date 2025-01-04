#include <SFML/Graphics.hpp>
#include <string>

class Item {
    private:
        const std::string name;
        const char sprite;
        const sf::Color colour;
        const std::string itemType;
        int x;
        int y;
    public:
        Item(std::string, char, sf::Color, std::string, int, int);
        std::string getName();
        char getSprite();
        sf::Color getColour();
        std::string getType();
        int getX();
        int getY();
        void setPos(int, int);
}; 