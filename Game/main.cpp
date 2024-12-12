#include <SFML/Graphics.hpp>
#include <iostream> 
#include <string>
#include <vector>
#include "entity.h"

const int TILE_SIZE = 18;
const int NUM_TILES_HEIGHT = 30;
const int NUM_TILES_WIDTH = 40;
const int LOG_HEIGHT = 8 * TILE_SIZE;

void displayMap(Map& map, sf::RenderWindow& window, sf::Font& font) {
    for (int i = 0; i < map.getHeight(); ++i) {
        for (int j = 0; j < map.getWidth(); ++j) {
            if (map.getTile(j, i).getVisible() == true) {
                sf::Text tileSprite(map.getTile(j, i).getSymbol(), font, TILE_SIZE);
                tileSprite.setFillColor(sf::Color::White);
                tileSprite.setPosition(TILE_SIZE * (j+0.25), TILE_SIZE * (i-0.125) + LOG_HEIGHT);

                window.draw(tileSprite);
            }
            else if (map.getTile(j, i).getSeen() == true) {
                sf::Text tileSprite(map.getTile(j, i).getSymbol(), font, TILE_SIZE);
                tileSprite.setFillColor(sf::Color(255, 255, 255, 125));
                tileSprite.setPosition(TILE_SIZE * (j+0.25), TILE_SIZE * (i-0.125) + LOG_HEIGHT);

                window.draw(tileSprite);
            }
        }
    }
}

void displayEntities(std::vector<Entity*>& entities, sf::RenderWindow& window, sf::Font& font) {
    for (int i = 0; i < entities.size(); ++i) {
        sf::Text entitySprite(entities.at(i)->getSymbol(), font, TILE_SIZE);
        entitySprite.setFillColor(entities.at(i)->getColour());
        entitySprite.setPosition((entities.at(i)->getX() + 0.25) * TILE_SIZE, (entities.at(i)->getY() - 0.125) * TILE_SIZE + LOG_HEIGHT);

        sf::RectangleShape clear(sf::Vector2f(TILE_SIZE, TILE_SIZE));
        clear.setFillColor(sf::Color::Black);
        clear.setPosition((entities.at(i)->getX() + 0.25) * TILE_SIZE, (entities.at(i)->getY() - 0.125) * TILE_SIZE + LOG_HEIGHT);

        window.draw(clear);
        window.draw(entitySprite);
    }
}

void displayMessages(std::deque<Message> messages, sf::RenderWindow& window, sf::Font& font) {
    for (int i = 0; i < messages.size(); ++i) {
        sf::Text message(messages.at(i).getContent(), font, TILE_SIZE);
        message.setFillColor(sf::Color(messages.at(i).getColour()));
        message.setPosition(0, (i * TILE_SIZE));
        window.draw(message);
    }
}

void displayStats(Map& map, sf::RenderWindow& window, sf::Font& font, Entity* player) {
    sf::Text stats("", font, TILE_SIZE);
    stats.setFillColor(sf::Color::White);
    stats.setPosition(0, 6*TILE_SIZE);
    stats.setString("DLvl: " + std::to_string(map.getLevel()) + ", XpLvl: " + std::to_string(player->getLevel()) + ", AU: " + std::to_string(player->getGold())  + ", HP: " 
        + std::to_string(player->getStats()->getMaxHP()) + ", SP: " + std::to_string(player->getStats()->getMaxSP()));
    window.draw(stats);
    stats.setPosition(0, 8*TILE_SIZE);
    stats.setString("Str: " + std::to_string(player->getStats()->getStr()) + ", Con: " + std::to_string(player->getStats()->getCon()) + ", Dex: " + std::to_string(player->getStats()->getDex()) 
        + ", Int: " + std::to_string(player->getStats()->getInte()) + ", Wis: " + std::to_string(player->getStats()->getWis()) + ", Cha: " + std::to_string(player->getStats()->getCha()));
    window.draw(stats);
}

void refresh(sf::RenderWindow& window, Map& map, sf::Font& font, std::vector<Entity*>& entities, MessageLog& messageLog, bool oldMessages) {
    window.clear(sf::Color::Black);

    displayMap(map, window, font);

    displayEntities(entities, window, font);

    if (oldMessages) {
        displayMessages(messageLog.getOldMessage(), window, font);
    }
    else {
        displayMessages(messageLog.getMessages(), window, font);
    }

    displayStats(map, window, font, entities.at(0));

    window.display();
}

void toggleFullScreen(sf::RenderWindow& window, sf::View& view, bool& isFullScreen) {
    window.close();
    isFullScreen = !isFullScreen;

    if (isFullScreen) {
        sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
        window.create(desktop, "Fullscreen", sf::Style::Fullscreen);
    }
    else {
        window.create(sf::VideoMode(TILE_SIZE * NUM_TILES_WIDTH, TILE_SIZE * NUM_TILES_HEIGHT + LOG_HEIGHT), "Windowed", sf::Style::Close);
    }

    view.setSize(NUM_TILES_WIDTH * TILE_SIZE, NUM_TILES_HEIGHT * TILE_SIZE + LOG_HEIGHT);
    view.setCenter(view.getSize() / 2.f);
    window.setView(view);
}

int main() {
    srand(time(0));
    std::cerr << "Main method is run" << std::endl;

    //Loads a font from a file
    sf::Font font;
    if (!font.loadFromFile("./Inconsolata-Regular.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return -1;
    }

    //Creates the player sprite
    std::vector<Entity*> entities;
    Entity player(NUM_TILES_WIDTH/2, NUM_TILES_HEIGHT/2, '@', sf::Color::White, 5);
    player.setStats(5, 5, 5, 5, 5, 5);
    entities.push_back(&player);

    MessageLog messageLog = MessageLog();
    messageLog.addMessage(Message(16777215, "Welcome to <INSERT_NAME_HERE>!"));

    //Create a new map object
    Map map = Map(NUM_TILES_WIDTH, NUM_TILES_HEIGHT);
    std::pair<int,int> playerLoc = map.generateDungeon();
    player.setPos(playerLoc.first, playerLoc.second);
    std::cerr << "Successfully generates map" << std::endl;
    player.calculateFov(&map);
    
    // Creates a window
    sf::RenderWindow window(sf::VideoMode(TILE_SIZE * NUM_TILES_WIDTH, TILE_SIZE * NUM_TILES_HEIGHT + LOG_HEIGHT), "CPP Rougelike");
    sf::View view(sf::FloatRect(0, 0, TILE_SIZE * NUM_TILES_WIDTH, TILE_SIZE * NUM_TILES_HEIGHT + LOG_HEIGHT));
    window.setView(view);
    bool fullscreen = false;
    bool oldMessages = false;

    if (!window.isOpen()) {
        std::cerr << "Window couldn't be opened!" << std::endl;
        return -1;  // Exit if the window fails to open
    }

    refresh(window, map, font, entities, messageLog, oldMessages);

    // Game loop
    while (window.isOpen()) {
        // Clear the window with a black color

        // Event handling
        sf::Event event;
        
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) //red x in the corner is pressed
                window.close();

            //Check for all relevant keypress events
            if (event.type == sf::Event::KeyPressed) {
                //Ctrl - Key operations
                bool ctrl = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl);
                //Shift - Key operations
                bool shift = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
                //Basic Key operations
                if (event.key.code == sf::Keyboard::F && ctrl) {
                    toggleFullScreen(window, view, fullscreen);
                }
                if (event.key.code == sf::Keyboard::Period && shift) {
                    player.traverseStairs(&map);
                    refresh(window, map, font, entities, messageLog, oldMessages);
                }
                if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Numpad8) {
                    player.move(&map, 0, -1, shift, &messageLog);
                    refresh(window, map, font, entities, messageLog, oldMessages);
                }
                if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Numpad2) {
                    player.move(&map, 0, 1, shift, &messageLog);
                    refresh(window, map, font, entities, messageLog, oldMessages);
                }
                if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Numpad4) {
                    player.move(&map, -1, 0, shift, &messageLog);
                    refresh(window, map, font, entities, messageLog, oldMessages);
                }
                if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Numpad6) {
                    player.move(&map, 1, 0, shift, &messageLog);
                    refresh(window, map, font, entities, messageLog, oldMessages);
                }
                if (event.key.code == sf::Keyboard::Numpad7 || event.key.code == sf::Keyboard::Home) {
                    player.move(&map, -1, -1, shift, &messageLog);
                    refresh(window, map, font, entities, messageLog, oldMessages);
                }
                if (event.key.code == sf::Keyboard::Numpad9 || event.key.code == sf::Keyboard::PageUp) {
                    player.move(&map, 1, -1, shift, &messageLog);
                    refresh(window, map, font, entities, messageLog, oldMessages);
                }
                if (event.key.code == sf::Keyboard::Numpad1 || event.key.code == sf::Keyboard::End) {
                    player.move(&map, -1, 1, shift, &messageLog);
                    refresh(window, map, font, entities, messageLog, oldMessages);
                }
                if (event.key.code == sf::Keyboard::Numpad3 || event.key.code == sf::Keyboard::PageDown) {
                    player.move(&map, 1, 1, shift, &messageLog);
                    refresh(window, map, font, entities, messageLog, oldMessages);
                }
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
                if (event.key.code == sf::Keyboard::Num6 && shift) {
                    oldMessages = true;
                    refresh(window, map, font, entities, messageLog, oldMessages);
                    oldMessages = false;
                }
            }
        }
    }

    std::cout << "Program exited successfully!" << std::endl;
    return 0;
}