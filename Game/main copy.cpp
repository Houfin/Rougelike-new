#include <SFML/Graphics.hpp>
#include <iostream>  // To output errors to the console

int main() {
    // Try to create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Test");

    if (!window.isOpen()) {
        std::cerr << "Window couldn't be opened!" << std::endl;
        return -1;  // Exit if the window fails to open
    }

    // Game loop
    while (window.isOpen()) {
        // Event handling
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window with a blue color
        window.clear(sf::Color::Blue);

        // Display the contents of the window
        window.display();
    }

    std::cout << "Program exited successfully!" << std::endl;
    return 0;
}