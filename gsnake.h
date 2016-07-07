#ifndef GSNAKE_H
#define GSNAKE_H
#include <iostream>
#include <vector>
#include <time.h>
using namespace std;
using Map2D = vector<vector<int>>;
class GameMap;

struct SNodes {
    int r, c;
    SNodes(int _x = 0, int _y= 0) : r(_x), c(_y) {}
    friend bool operator==(const SNodes&, const SNodes&);
};

class GSnake {
    vector<SNodes> body;
public:
    friend class GameMap;
    void init(int);
    bool move_up(GameMap&);
    bool move_down(GameMap&);
    bool move_left(GameMap&);
    bool move_right(GameMap&);
};

class GameMap {
    Map2D s_map;
    GSnake snk;
    SNodes Gold;
public:
    friend class GSnake;
    GameMap(int);
    void display_game();
    void pos_snake();
    bool add_gold();
    bool g_start();
    bool isGold();
    int loc_Gold();
};

#endif // GSNAKE_H
