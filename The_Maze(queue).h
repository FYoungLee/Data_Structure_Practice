//
//  Header.h
//  CPP
//
//  Created by mac on 6/30/16.
//  Copyright (c) 2016 Fyang. All rights reserved.
//

#ifndef CPP_Header_h
#define CPP_Header_h
#include <iostream>
#include <vector>
#include <unistd.h>
/* location nodes */
class killMaze;

using namespace std;
struct loc {
    int j, i;
    int road;
    loc *next;
    loc *pre;
    loc(int y, int x, int r = 0): j(y), i(x), road(r), next(nullptr), pre(nullptr) {}
    loc(const loc& l): j(l.j), i(l.i), road(l.road), next(nullptr), pre(l.pre) {}
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

/* location queue */
class LocQueue {
    loc *rear;
    loc *step;
public:
    LocQueue();
    ~LocQueue();
    void push(const loc&);
    bool deque();
    void add_pre(loc *pl);
    loc *getStep() { return step; }
    void nextStep() { step = step->next; }
    const loc* stepToExit();
    const loc* stepPre();
};

LocQueue::LocQueue(): rear(nullptr), step(nullptr) {}

LocQueue::~LocQueue() {
    while (rear)
        deque();
}

void LocQueue::push(const loc& l) {
    loc *n = new loc(l);
    if (rear) {
        n->next = rear->next;
        rear->next = n;
        rear = n;
    } else {
        n->next = n;
        rear = n;
    }
    if (!step) step = n;
}

bool LocQueue::deque() {
    if (!rear) return false;
    if (rear != rear->next) {
        loc *p = rear->next;
        rear->next = p->next;
        delete p;
        return true;
    } else {
        delete rear;
        rear = nullptr;
        return true;
    };
}

void LocQueue::add_pre(loc *pl) {
    rear->pre = pl;
}

const loc* LocQueue::stepToExit() {
    step = rear;
    return step;
}

const loc* LocQueue::stepPre() {
    if (step->pre) {
        step = step->pre;
        return step;
    } else return nullptr;
}

/* the maze class */
class killMaze {
    vector<vector<int>> map;
    loc entrance, exit;
    int wid, hgt;
    LocQueue pathLog;
    void cur_loc_chk(loc&);
public:
    killMaze(const vector<vector<int>>& m, loc entr, loc ex);
    void display();
    bool getPath();
    void viewPath();
    bool goUp(loc&);
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
    wid = static_cast<int>(m[0].size());
    hgt = static_cast<int>(m.size());
    map[entrance.j][entrance.i] = 3;
}

void killMaze::display() {
    for (int y = 0; y < hgt; ++y) {
        for (int x = 0; x < wid; ++x)
            if (map[y][x] == 1)
                cout << "▉";
            else if (map[y][x] == 0)
                cout << ' ';
            else if (map[y][x] == 3)
                cout << '.';
            else
                cout << "X";
        cout << endl;
    }
}

bool killMaze::getPath() {
    pathLog.push(entrance);
    auto p = pathLog.getStep();
    auto start = *p;
    while (start != exit) {
        p = pathLog.getStep();
        start = *p;
        if (goUp(start)) {
            pathLog.push(start);
            pathLog.add_pre(p);
        } else if (goRight(start)) {
            pathLog.push(start);
            pathLog.add_pre(p);
        } else if (goDown(start)) {
            pathLog.push(start);
            pathLog.add_pre(p);
        } else if (goLeft(start)) {
            pathLog.push(start);
            pathLog.add_pre(p);
        } else
            pathLog.nextStep();
        //sleep(1);
        //system("clear");
        display();
    }
    viewPath();
    cout << "WIN!\n";
    return true;
}

void killMaze::viewPath() {
    auto p = pathLog.stepToExit();
    while (p != nullptr) {
        map[p->j][p->i] = 3;
        p = pathLog.stepPre();
    }
    display();
}

bool killMaze::goUp(loc& l) {
    if (map[l.j - 1][l.i] == 0) {
        --l.j;
        map[l.j][l.i] = 2;
        return true;
    } else return false;
}

bool killMaze::goDown(loc& l) {
    if (map[l.j + 1][l.i] == 0) {
        ++l.j;
        map[l.j][l.i] = 2;
        return true;
    } else return false;
}

bool killMaze::goLeft(loc& l) {
    if (map[l.j][l.i - 1] == 0) {
        --l.i;
        map[l.j][l.i] = 2;
        return true;
    } else return false;
}

bool killMaze::goRight(loc& l) {
    if (map[l.j][l.i + 1] == 0) {
        ++l.i;
        map[l.j][l.i] = 2;
        return true;
    } else return false;
}

#endif // MAZE


