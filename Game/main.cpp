#include <SFML/Graphics.hpp>
#include <iostream> 
#include <string>
#include <vector>
#include "map.h"
#include "entity.h"

const int TILE_SIZE = 18;
const int NUM_TILES_HEIGHT = 50;
const int NUM_TILES_WIDTH = 80;
bool refresh = false;

void displayMap(Map& map, sf::RenderWindow& window, sf::Font& font) {
    for (int i = 0; i < map.getHeight(); ++i) {
        for (int j = 0; j < map.getWidth(); ++j) {
            sf::Text tileSprite(".", font, TILE_SIZE);
            tileSprite.setFillColor(sf::Color::White);

            if (map.getTile(j, i).getType() == "wall") {
                tileSprite.setString("#");
            }

            tileSprite.setPosition(TILE_SIZE * (j+0.25), TILE_SIZE * (i-0.375));

            window.draw(tileSprite);
        }
    }
}

void displayEntities(std::vector<Entity*>& entities, sf::RenderWindow& window, sf::Font& font) {
    for (int i = 0; i < entities.size(); ++i) {
        sf::Text entitySprite(entities.at(i)->getSymbol(), font, TILE_SIZE);
        entitySprite.setFillColor(entities.at(i)->getColour());
        entitySprite.setPosition((entities.at(i)->getX() + 0.25) * TILE_SIZE, (entities.at(i)->getY() - 0.125) * TILE_SIZE);

        sf::RectangleShape clear(sf::Vector2f(TILE_SIZE, TILE_SIZE));
        clear.setFillColor(sf::Color::Black);
        clear.setPosition((entities.at(i)->getX() + 0.25) * TILE_SIZE, (entities.at(i)->getY() - 0.125) * TILE_SIZE);

        window.draw(clear);
        window.draw(entitySprite);
    }
}

void generateMap(Map* map) {
    srand(time(0));
    std::cerr << "Starts generating map" << std::endl;

    // Every tile at the start is a wall.  
    for (int i = 0; i < map->getWidth(); ++i) {
        for (int j = 0; j < map->getHeight(); ++j) {
            map->setTile(i, j, true, true, "wall");
        }
    }

    Node parent = Node(1, 1, map->getWidth() - 2, map->getHeight() - 2);
    std::vector<Room> rooms;
    parent.createChildren(map, &rooms);
    parent.joinChildren(map, &rooms);
}

void moveEntity(Entity& entity, int xChange, int yChange, Map* map) {
    if (entity.getX() + xChange < 0 || entity.getX() + xChange > (NUM_TILES_WIDTH-1) 
        || entity.getY() + yChange < 0 || entity.getY() + yChange > (NUM_TILES_HEIGHT-1)) {
        return;
    }
    Tile tile = map->getTile(entity.getX() + xChange, entity.getY() + yChange);
    if (tile.getBlocksMove()) {
        return;
    }
    entity.setPos(entity.getX() + xChange, entity.getY() + yChange);
    refresh = true;
}

void toggleFullScreen(sf::RenderWindow& window, sf::View& view, bool& isFullScreen) {
    window.close();
    isFullScreen = !isFullScreen;

    if (isFullScreen) {
        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
        window.create(desktop, "Fullscreen", sf::Style::Fullscreen);
    }
    else {
        window.create(sf::VideoMode(TILE_SIZE * NUM_TILES_WIDTH, TILE_SIZE * NUM_TILES_HEIGHT), "Windowed", sf::Style::Close);
    }

    view.setSize(NUM_TILES_WIDTH * TILE_SIZE, NUM_TILES_HEIGHT * TILE_SIZE);
    view.setCenter(view.getSize() / 2.f);
    window.setView(view);
}

int main() {

    std::cerr << "Main method is run" << std::endl;

    //Loads a font from a file
    sf::Font font;
    if (!font.loadFromFile("./Inconsolata-Regular.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return -1;
    }

    //Creates the player sprite
    std::vector<Entity*> entities;
    Entity player(NUM_TILES_WIDTH/2, NUM_TILES_HEIGHT/2, '@', sf::Color::White);
    entities.push_back(&player);

    //Create a new map object
    Map map = Map(NUM_TILES_WIDTH, NUM_TILES_HEIGHT);
    generateMap(&map);
    std::cerr << "Successfully generates map" << std::endl;

    // Creates a window
    sf::RenderWindow window(sf::VideoMode(TILE_SIZE * NUM_TILES_WIDTH, TILE_SIZE * NUM_TILES_HEIGHT), "CPP Rougelike");
    sf::View view(sf::FloatRect(0, 0, TILE_SIZE * NUM_TILES_WIDTH, TILE_SIZE * NUM_TILES_HEIGHT));
    window.setView(view);
    bool fullscreen = false;

    if (!window.isOpen()) {
        std::cerr << "Window couldn't be opened!" << std::endl;
        return -1;  // Exit if the window fails to open
    }

    // Game loop
    while (window.isOpen()) {
        // Clear the window with a black color
        window.clear(sf::Color::Black);

        displayMap(map, window, font);

        displayEntities(entities, window, font);

        // Display the contents of the window
        window.display();
        
        // Event handling
        sf::Event event;
        
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) //red x in the corner is pressed
                window.close();

            //Check for all relevant keypress events
            if (event.type == sf::Event::KeyPressed) {
                //Ctrl - Key operations
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                    if (event.key.code == sf::Keyboard::F) {
                        toggleFullScreen(window, view, fullscreen);
                    }
                }
                //Shift - Key operations
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
                    
                }
                //Basic Key operations
                else {
                    if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Numpad8) {
                        moveEntity(player, 0, -1, &map);
                    }
                    if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Numpad2) {
                        moveEntity(player, 0, 1, &map);
                    }
                    if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Numpad4) {
                        moveEntity(player, -1, 0, &map);
                    }
                    if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Numpad6) {
                        moveEntity(player, 1, 0, &map);
                    }
                    if (event.key.code == sf::Keyboard::Numpad7) {
                        moveEntity(player, -1, -1, &map);
                    }
                    if (event.key.code == sf::Keyboard::Numpad9) {
                        moveEntity(player, 1, -1, &map);
                    }
                    if (event.key.code == sf::Keyboard::Numpad1) {
                        moveEntity(player, -1, 1, &map);
                    }
                    if (event.key.code == sf::Keyboard::Numpad3) {
                        moveEntity(player, 1, 1, &map);
                    }
                    if (event.key.code == sf::Keyboard::Escape) {
                        window.close();
                    }
                }
            }
        }
    }

    std::cout << "Program exited successfully!" << std::endl;
    return 0;
}