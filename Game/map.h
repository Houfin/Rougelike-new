#include <string>

class Room {
    private:
    int startX;
    int startY;
    int endX;
    int endY;
    int doorX;
    int doorY;
    int corridorDirection;

    public:
    Room();
    Room(int, int, int, int, int, int);
    int getStartX();
    int getStartY();
    void setStart(int, int);
    int getEndX();
    int getEndY();
    void setEnd(int, int);
    int getDoorX();
    int getDoorY();
    void setDoor(int, int);
    int getCorridorDirection();
    void setCorridorDirection(int);
};

class Tile {
    private:
    bool blocksMove;
    bool blocksLight;
    std::string type;
    char symbol;
    bool room;

    public:
    bool getBlocksMove();
    bool getBlocksLight();
    std::string getType();
    bool getRoom();
    char getSymbol();
    void setRoom(bool);
    void setSymbol(char);
    void setBlocksMove(bool);
    void setBlocksLight(bool);
    void setType(std::string);
    Tile(bool, bool, std::string, char, bool);
    Tile();
};

class Map {
    private: 
    const int width;
    const int height;
    std::vector<std::vector<Tile>> tiles;

    public:
    Map(int, int);
    Tile& getTile(int, int);
    void setTile(int, int, bool, bool, std::string, char, bool);
    int getWidth();
    int getHeight();
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
    bool createChildren(Map*, std::vector<Room>*);
    void joinChildren(Map*, std::vector<Room>*);
    Room createRoom(Map*);
};
