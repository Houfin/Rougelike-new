#include <string>

class Room {
    private:
    int centerX;
    int centerY;

    public:
    Room(int, int);
    int getX();
    int getY();
    void setX(int);
    void setY(int);
};

class Tile {
    private:
    bool blocksMove;
    bool blocksLight;
    std::string type;

    public:
    bool getBlocksMove();
    bool getBlocksLight();
    std::string getType();
    void setBlocksMove(bool);
    void setBlocksLight(bool);
    void setType(std::string);
    Tile(bool, bool, std::string);
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
    void setTile(int, int, bool, bool, std::string);
    int getWidth();
    int getHeight();
};

class Node {
    private:
    int x;
    int y;
    int width;
    int height;
    Node* child1;
    Node* child2;

    public:
    Node(int, int, int, int);
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    bool createChildren(Map*, std::vector<Room>*);
    void joinChildren(Map*, std::vector<Room>*);
    Room createRoom(Map*);
};
