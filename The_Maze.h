/*
#include "maze.h"

int main() {
    system("clear");
    vector<vector<int>>maze({
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1},
        {1,1,0,0,0,1,1,1,0,1,0,1,0,0,1,1,0,0,0,1},
        {1,1,0,1,1,1,0,0,0,0,1,0,0,1,1,0,0,0,0,1},
        {1,0,0,1,1,1,0,1,0,1,0,0,0,0,1,0,1,1,1,1},
        {1,0,1,0,0,0,0,1,0,1,1,1,1,0,1,0,0,0,0,1},
        {1,0,0,0,1,1,0,1,0,0,0,0,0,0,1,1,1,1,0,1},
        {1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1},
        {1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    });
    loc start{1, 1};
    loc end{10, 1};
    killMaze m1(maze, start, end);
    m1.display();
    m1.getPath();
    return 0;
}


*/



#ifndef MAZE
#define MAZE
#include <iostream>
#include <vector>
#include <unistd.h>
using namespace std;
struct loc {
    int j, i;
    loc(int y, int x): j(y), i(x) {}
    friend bool operator==(const loc& lft, const loc& rht) {
        return (lft.i == rht.i && lft.j == rht.j);
    }
    friend bool operator!=(const loc& lft, const loc& rht) {
        return !(lft == rht);
    }
};
class killMaze {
    vector<vector<int>> map;
    loc entrance, exit;
    int wid, hgt;
    vector<pair<loc, int>> pathLog;
public:
    killMaze(const vector<vector<int>>& m, loc entr, loc ex);
    void display();
    bool getPath();
    int current_loc_status(const loc&);
    bool goUp(loc&);
    bool goDown(loc&);
    bool goLeft(loc&);
    bool goRight(loc&);
};

killMaze::killMaze(const vector<vector<int>>& m, loc entr, loc ex):
    map(m), entrance(entr), exit(ex) {
    wid = m[0].size();
    hgt = m.size();
}

void killMaze::display() {
    for (int y = 0; y < hgt; ++y) {
        for (int x = 0; x < wid; ++x)
            if (map[y][x] == 1)
                cout << "▉";
            else if (map[y][x] == 0 || map[y][x] == 3)
                cout << ' ';
            else
                cout << "+";
        cout << endl;
    }
}

bool killMaze::getPath() {
    loc start = entrance;
    int ways = current_loc_status(start);
    pathLog.push_back(make_pair(start, ways));
    while (start != exit) {
        if (goUp(start)) {
            --pathLog[pathLog.size() - 1].second;
            pathLog.push_back(make_pair(start, current_loc_status(start)));
        }
        else if (goRight(start)) {
            --pathLog[pathLog.size() - 1].second;
            pathLog.push_back(make_pair(start, current_loc_status(start)));
        }
        else if (goDown(start)) {
            --pathLog[pathLog.size() - 1].second;
            pathLog.push_back(make_pair(start, current_loc_status(start)));
        }
        else if (goLeft(start)) {
            --pathLog[pathLog.size() - 1].second;
            pathLog.push_back(make_pair(start, current_loc_status(start)));
        }
        else {
            map[start.j][start.i] = 2;
            while (pathLog[pathLog.size() - 1].second == 0) {
                start = pathLog[pathLog.size() - 1].first;
                map[start.j][start.i] = 3;
                pathLog.pop_back();
                if (pathLog.size() == 1 && pathLog[0].second == 0) {
                    cerr << "No Way\n";
                    return false;
                }
            }
            start = pathLog[pathLog.size() - 1].first;
        }
        //sleep(1);
        system("clear");
        display();
    }
    return true;
}
int killMaze::current_loc_status(const loc& l) {
    int n = 0;
    if (map[l.j - 1][l.i] == 0)
        ++n;
    if (map[l.j][l.i + 1] == 0)
        ++n;
    if (map[l.j + 1][l.i] == 0)
        ++n;
    if (map[l.j][l.i - 1] == 0)
        ++n;
    return n;
}

bool killMaze::goUp(loc& l) {
    if (map[l.j - 1][l.i] == 0) {
        map[l.j][l.i] = 2;
        --l.j;
        return true;
    } else return false;
}

bool killMaze::goDown(loc& l) {
    if (map[l.j + 1][l.i] == 0) {
        map[l.j][l.i] = 2;
        ++l.j;
        return true;
    } else return false;
}

bool killMaze::goLeft(loc& l) {
    if (map[l.j][l.i - 1] == 0) {
        map[l.j][l.i] = 2;
        --l.i;
        return true;
    } else return false;
}

bool killMaze::goRight(loc& l) {
    if (map[l.j][l.i + 1] == 0) {
        map[l.j][l.i] = 2;
        ++l.i;
        return true;
    } else return false;
}

#endif // MAZE

