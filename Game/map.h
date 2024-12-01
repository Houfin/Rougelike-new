#include <string>

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
    void generateMap();
};