#include "gsnake.h"
bool operator==(const SNodes& lft, const SNodes& rht) {
    return (lft.c == rht.c && lft.r == rht.r);
}

void GSnake::init(int n) {
    body.push_back(SNodes(n/2, n/4));
}

bool GSnake::move_up(GameMap& map) {
    bool newbody = false;
    if (map.s_map[body[0].r - 1][body[0].c] > 0)
        return false;
    else if (map.s_map[body[0].r - 1][body[0].c] == -1)
        newbody = true;
    auto rear = body[body.size() - 1];
    for (size_t n = body.size() - 1; n > 0; --n)
        body[n] = body[n - 1];
    --body[0].r;
    if (newbody) {
        body.push_back(rear);
        map.Gold.r = 0, map.Gold.c = 0;
    }
    map.s_map[rear.r][rear.c] = 0;
    return true;
}

bool GSnake::move_down(GameMap& map) {
    bool newbody = false;
    if (map.s_map[body[0].r + 1][body[0].c] > 0)
        return false;
    else if (map.s_map[body[0].r + 1][body[0].c] == -1)
        newbody = true;
    auto rear = body[body.size() - 1];
    for (size_t n = body.size() - 1; n > 0; --n)
        body[n] = body[n - 1];
    ++body[0].r;
    if (newbody) {
        body.push_back(rear);
        map.Gold.r = 0, map.Gold.c = 0;
    }
    map.s_map[rear.r][rear.c] = 0;
    return true;
}

bool GSnake::move_left(GameMap& map) {
    bool newbody = false;
    if (map.s_map[body[0].r][body[0].c - 1] > 0)
        return false;
    else if (map.s_map[body[0].r][body[0].c - 1] == -1)
        newbody = true;
    auto rear = body[body.size() - 1];
    for (size_t n = body.size() - 1; n > 0; --n)
        body[n] = body[n - 1];
    --body[0].c;
    if (newbody) {
        body.push_back(rear);
        map.Gold.r = 0, map.Gold.c = 0;
    }
    map.s_map[rear.r][rear.c] = 0;
    return true;
}

bool GSnake::move_right(GameMap& map) {
    bool newbody = false;
    if (map.s_map[body[0].r][body[0].c + 1] > 0)
        return false;
    else if (map.s_map[body[0].r][body[0].c + 1] == -1)
        newbody = true;
    auto rear = body[body.size() - 1];
    for (size_t n = body.size() - 1; n > 0; --n)
        body[n] = body[n - 1];
    ++body[0].c;
    if (newbody) {
        body.push_back(rear);
        map.Gold.r = 0, map.Gold.c = 0;
    }
    map.s_map[rear.r][rear.c] = 0;
    return true;
}

/*******************************/

GameMap::GameMap(int n) {
    srand(static_cast<unsigned>(time(0)));
    Gold.r = Gold.c = 0;
    int m = n * 2;
    for (int i = 0; i < n; ++i) {
        vector<int> row;
        for (int j = 0; j < m; ++j)
            if (i == 0 || j == 0 || i == n - 1 || j == m - 1)
                row.push_back(1);
            else
                row.push_back(0);
        s_map.push_back(row);
    }
    snk.init(n);
}

void GameMap::display_game() {
    if (Gold.c == 0 && Gold.r == 0)
       add_gold();
    pos_snake();
    system("clear");
    for (size_t i = 0; i < s_map.size(); ++i) {
        for (size_t j = 0; j < s_map[0].size(); ++j)
            if (s_map[i][j] == 2)
                cout << '*';
            else if (s_map[i][j] == 1)
                cout << '#';
            else if (s_map[i][j] == -1)
                cout << '$';
            else
                cout << ' ';
        cout << endl;
    }
}

void GameMap::pos_snake() {
    for (auto& i : snk.body)
        s_map[i.r][i.c] = 2;
}

bool GameMap::add_gold() {
    auto r = rand() % (s_map.size() - 1) + 1;
    auto c = rand() % (s_map[0].size() - 1) + 1;
    if (s_map[r][c] == 0) {
        Gold.r = r, Gold.c = c;
        s_map[r][c] = -1;
        return true;
    }
    else return false;
}

bool GameMap::g_start() {
    auto d = loc_Gold();
    switch (d) {
    case 3:
        if (snk.move_up(*this))
            return true;
        break;
    case 1:
        if (snk.move_right(*this))
            return true;
        break;
    case 4:
        if (snk.move_down(*this))
            return true;
        break;
    case 2:
        if (snk.move_left(*this))
            return true;
        break;
    }
    if (snk.move_up(*this))
        return true;
    if (snk.move_right(*this))
        return true;
    if (snk.move_down(*this))
        return true;
    if (snk.move_left(*this))
        return true;
    return false;
}

bool GameMap::isGold() {
    return (Gold.r == 0 && Gold.c == 0);
}

int GameMap::loc_Gold() {
    // 1 == move to right, 2 == move to left, 3 == move to up, 4 == move to down.
    if (Gold.r == snk.body[0].r) {
        if (Gold.c > snk.body[0].c)
            return 1;
        else if (Gold.c < snk.body[0].c)
            return 2;
    }
    else if (Gold.c == snk.body[0].c) {
        if (Gold.r < snk.body[0].r)
            return 3;
        else if (Gold.r > snk.body[0].r)
            return 4;
    }
    else if (Gold.r < snk.body[0].r)
            return 3;
    else if (Gold.r > snk.body[0].r)
            return 4;
    return 1;
}
