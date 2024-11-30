#include <SFML/Graphics.hpp>
#include <iostream> 
#include <stdio.h>

int main() {
    // Creates a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "CPP Rougelike");

    if (!window.isOpen()) {
        std::cerr << "Window couldn't be opened!" << std::endl;
        return -1;  // Exit if the window fails to open
    }

    //Loads a font from a file
    sf::Font font;
    if (!font.loadFromFile("./Inconsolata-Regular.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return -1;
    }

    sf::Text text;
    text.setFont(font);
    text.setString("@");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    sf::FloatRect textbounds = text.getLocalBounds();
    float textWidth = textbounds.width;
    float textHeight = textbounds.height;

    text.setPosition((window.getSize().x - textWidth) / 2, (window.getSize().y - textHeight) / 2);

    // Game loop
    while (window.isOpen()) {
        // Event handling
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) //red x in the corner is pressed
                window.close();
        }

        // Clear the window with a black color
        window.clear(sf::Color::Black);

        window.draw(text);

        // Display the contents of the window
        window.display();
    }

    std::cout << "Program exited successfully!" << std::endl;
    return 0;
}