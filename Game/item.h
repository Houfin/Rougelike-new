#include <SFML/Graphics.hpp>
#include <string>

class Item {
    private:
    std::string name;
    std::string sprite;
    sf::Color colour;
    std::string itemType;
    int x = 0;
    int y = 0;
    
    public:
    Item(std::string, std::string, sf::Color, std::string);
    std::string getName();
    std::string getSprite();
    sf::Color getColour();
    std::string getType();
    int getX();
    int getY();
    void setPos(int, int);
}; 