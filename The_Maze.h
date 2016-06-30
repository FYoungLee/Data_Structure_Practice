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

/*      location nodes    */
struct loc {
    int j, i;
    int road;
    loc *next;
    loc(int y, int x, int r = 0): j(y), i(x), road(r), next(nullptr) {}
//    void update_road(int n) { road = n; }
    loc operator++() { ++road; return *this; }
    loc operator--() { --road; return *this; }
    friend bool operator==(const loc& lft, const loc& rht) {
        return (lft.i == rht.i && lft.j == rht.j);
    }
    friend bool operator!=(const loc& lft, const loc& rht) {
        return !(lft == rht);
    }
    friend ostream& operator<<(ostream& os, const loc& l) {
        os << "(" << l.j << "," << l.i << ") -> ";
        return os;
    }
};
/*      location stack            */
class LocStack {
    loc *top;
public:
    LocStack(): top(nullptr) {}
    void add(const loc& l);
    bool pop();
    bool isEmpty();
    loc getTopVal();
};

void LocStack::add(const loc &l) {
    loc *nl = new loc(l.j, l.i, l.road);
    nl->next = top;
    top = nl;
}

bool LocStack::pop() {
    if (top) {
        loc *tl = top;
        top = top->next;
        delete tl;
        return true;
    } else return false;
}

bool LocStack::isEmpty() {
    return top == nullptr;
}

loc LocStack::getTopVal() {
    return *top;
}


/*      the maze class      */
class killMaze {
    vector<vector<int>> map;
    loc entrance, exit;
    int wid, hgt;
    LocStack pathLog;
    void cur_loc_chk(loc&);
public:
    killMaze(const vector<vector<int>>& m, loc entr, loc ex);
    void display();     // display current map.
    bool getPath();     // figure out how to exit the maze, return false if there is no way to get out.
    void viewPath();    // report the path to exit.
    bool goUp(loc&);    // move operations.
    bool goDown(loc&);
    bool goLeft(loc&);
    bool goRight(loc&);
};

void killMaze::cur_loc_chk(loc& l) {
    if (map[l.j - 1][l.i] == 0)
        ++l;
    if (map[l.j][l.i + 1] == 0)
        ++l;
    if (map[l.j + 1][l.i] == 0)
        ++l;
    if (map[l.j][l.i - 1] == 0)
        ++l;
}

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
            else if (map[y][x] == 0)
                cout << ' ';
            else if (map[y][x] == 3)
                cout << '-';
            else
                cout << "+";
        cout << endl;
    }
}

bool killMaze::getPath() {
    loc start = entrance;
    while (start != exit) {
        loc pre = start;
        if (goUp(start) || goRight(start) || goDown(start) || goLeft(start)){
            cur_loc_chk(pre);
            pathLog.add(pre);
            pre = start;
        }
        else {
            map[start.j][start.i] = 3;
            do {
                if (pathLog.isEmpty()){
                    cerr << "No Way\n";
                    return false;
                 } else if (pathLog.getTopVal().road <= 0) {
                    map[pathLog.getTopVal().j][pathLog.getTopVal().i] = 3;
                    pathLog.pop();
                } else break;
                display();
            } while (1);
            start = pathLog.getTopVal();
            pathLog.pop();
        }
        usleep(1000);
        system("clear");
        display();
    }
    cout << "WIN!\n";
    return true;
}

void killMaze::viewPath() {
    LocStack reverse;
    while (!pathLog.isEmpty()) {
        reverse.add(pathLog.getTopVal());
        pathLog.pop();
    }
    int n = 6;
    while (!reverse.isEmpty()) {
        if (--n == 0) {
            cout << endl;
            n = 6;
        }
        cout << reverse.getTopVal();
        reverse.pop();
    }
    cout << endl;
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

