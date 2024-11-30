#include <SFML/Graphics.hpp>
#include <iostream> 
#include <stdio.h>

void moveEntity(sf::Text* entity, int xChange, int yChange) {
    float tileWidth = entity->getLocalBounds().width;
    float tileHeight = entity->getLocalBounds().height;
    if (entity->getPosition().x + xChange < 0 || entity->getPosition().x + xChange > 80*tileWidth || entity->getPosition().y + yChange < 0 || entity->getPosition().y + yChange > 50 * tileHeight) {
        return;
    }
    entity->setPosition(entity->getPosition().x + xChange, entity->getPosition().y + yChange);
}

int main() {

    //Loads a font from a file
    sf::Font font;
    if (!font.loadFromFile("./Inconsolata-Regular.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return -1;
    }

    //Creates the player sprite
    sf::Text playerText;
    playerText.setFont(font);
    playerText.setString("@");
    playerText.setCharacterSize(24);
    playerText.setFillColor(sf::Color::White);

    sf::FloatRect textbounds = playerText.getLocalBounds();
    float tileWidth = textbounds.width;
    float tileHeight = textbounds.height;


    // Creates a window
    sf::RenderWindow window(sf::VideoMode(tileWidth*82, tileHeight*52), "CPP Rougelike");

    if (!window.isOpen()) {
        std::cerr << "Window couldn't be opened!" << std::endl;
        return -1;  // Exit if the window fails to open
    }

    playerText.setPosition(tileWidth*40, tileHeight*25);

    // Game loop
    while (window.isOpen()) {
        // Event handling
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) //red x in the corner is pressed
                window.close();

            //Check for all relevant keypress events
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Numpad8) {
                    moveEntity(&playerText, 0, -tileHeight);
                }
                if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Numpad2) {
                    moveEntity(&playerText, 0, tileHeight);
                }
                if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Numpad4) {
                    moveEntity(&playerText, -tileWidth, 0);
                }
                if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Numpad6) {
                    moveEntity(&playerText, tileWidth, 0);
                }
                if (event.key.code == sf::Keyboard::Numpad7) {
                    moveEntity(&playerText, -tileWidth, -tileHeight);
                }
                if (event.key.code == sf::Keyboard::Numpad9) {
                    moveEntity(&playerText, tileWidth, -tileHeight);
                }
                if (event.key.code == sf::Keyboard::Numpad1) {
                    moveEntity(&playerText, -tileWidth, tileHeight);
                }
                if (event.key.code == sf::Keyboard::Numpad3) {
                    moveEntity(&playerText, tileWidth, tileHeight);
                }
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }

        // Clear the window with a black color
        window.clear(sf::Color::Black);

        window.draw(playerText);

        // Display the contents of the window
        window.display();
    }

    std::cout << "Program exited successfully!" << std::endl;
    return 0;
}