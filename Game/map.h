#include <string>
#include "item.cpp"

class Room {
    private:
    int startX;
    int startY;
    int endX;
    int endY;
    bool stairs = false;

    public:
    Room();
    Room(int, int, int, int);
    bool getStairs();
    void setStairs(bool);
    int getStartX();
    int getStartY();
    void setStart(int, int);
    int getEndX();
    int getEndY();
    void setEnd(int, int);
};

class Tile {
    private:
    bool blocksMove;
    bool blocksLight;
    std::string type;
    std::string symbol;
    bool visible = false;
    bool lit = false;
    bool seen = false;

    public:
    bool getBlocksMove();
    bool getBlocksLight();
    bool getVisible();
    bool getLit();
    std::string getType();
    std::string getSymbol();
    bool getSeen();
    void setSymbol(std::string);
    void setBlocksMove(bool);
    void setBlocksLight(bool);
    void setType(std::string);
    void setVisible(bool);
    void setLit(bool);
    void setSeen();
    Tile(bool, bool, std::string, std::string);
    Tile();
};

class Map {
    private: 
    const int width;
    const int height;
    std::vector<std::vector<Tile>> tiles;
    int level = 0;
    std::vector<Room>* rooms = {};

    public:
    int getLevel();
    std::pair<int, int> generateDungeon();
    void makeStairs();
    Map(int, int);
    Tile& getTile(int, int);
    void setTile(int, int, bool, bool, std::string, std::string);
    int getWidth();
    int getHeight();
    std::vector<Item*> placeItems();
};

class BSPNode {
    private:
    int x;
    int y;
    int width;
    int height;
    BSPNode* child1;
    BSPNode* child2;

    public:
    BSPNode(int, int, int, int);
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    bool createChildren(Map*, std::vector<Room>*, bool);
    void joinChildren(Map*);
    Room createRoom(Map*, int);
};
