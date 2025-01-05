#include <SFML/Graphics.hpp>
#include "map.h"
#include "messages.h"

class StatBlock {
    private:
    int str;
    int con;
    int dex;
    int inte;
    int wis;
    int cha;

    public:
    StatBlock(int, int, int, int, int, int);
    int getStr();
    int getCon();
    int getDex();
    int getInte();
    int getWis();
    int getCha();
    void setStr(int);
    void setCon(int);
    void setDex(int);
    void setInte(int);
    void setWis(int);
    void setCha(int);
    int getMaxHP();
    int getMaxSP();
};

class Entity {
    private:
    int x;
    int y;
    int prevX;
    int prevY;
    char symbol;
    sf::Color colour;
    int light;
    StatBlock stats = StatBlock(0, 0, 0, 0, 0, 0);
    int gold = 0;
    int level = 1;
    int hp = 1;
    int sp = 0;

    public:
    Entity(int, int, char, sf::Color, int);
    int getX();
    int getPrevX();
    int getPrevY();
    int getY();
    int getLight();
    int getGold();
    int getLevel();
    void setLevel(int);
    void setGold(int);
    sf::Color getColour();
    StatBlock* getStats();
    void setStats(int, int, int, int, int, int);
    void setPos(int, int);
    void setPrevPos(int, int);
    void setLight(int);
    char getSymbol();
    void setSymbol(char);
    void setColour(sf::Color);
    void move(Map*, int, int, bool, MessageLog*);
    std::vector<Item> traverseStairs(Map*);
    void calculateFov(Map*);
    void recursiveFov(Map*, int, float, float, int, int, int, int);
};