#include <string>

class Room {
    private:
    int startX;
    int startY;
    int endX;
    int endY;

    public:
    Room();
    Room(int, int, int, int);
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
    int room;

    public:
    bool getBlocksMove();
    bool getBlocksLight();
    std::string getType();
    int getRoom();
    std::string getSymbol();
    void setRoom(int);
    void setSymbol(std::string);
    void setBlocksMove(bool);
    void setBlocksLight(bool);
    void setType(std::string);
    Tile(bool, bool, std::string, std::string, int);
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
    void setTile(int, int, bool, bool, std::string, std::string, int);
    void setTile(int, int, bool, bool, std::string, std::string);
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
    void joinChildren(Map*);
    Room createRoom(Map*, int);
};
