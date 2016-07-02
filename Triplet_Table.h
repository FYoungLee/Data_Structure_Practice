#ifndef TRIPLENODE_H
#define TRIPLENODE_H
#include <iostream>
#include <vector>
#include <algorithm>
template<typename T>
using V2D = std::vector<std::vector<T>>;
using std::vector;

struct TriNode {
    int r;
    int c;
    int data;
    TriNode(int a, int b, int d = 0): r(a), c(b), data(d) {}
    friend std::ostream& operator<<(std::ostream& os, const TriNode& tn);
    friend bool operator<(const TriNode& lt, const TriNode& rt);
};
std::ostream& operator<<(std::ostream& os, const TriNode& tn) {
    os << "Row: "<< tn.r << "\tColumn: " << tn.c << "\tValue: " << tn.data;
    return os;
}
bool operator<(const TriNode& lt, const TriNode& rt) {
    if (lt.r == rt.r) return lt.c < rt.c;
    else return lt.r < rt.r;
}

class TriMatrix {
    int rows;
    int cols;
    vector<TriNode> data;
public:
    TriMatrix(const V2D<int>&);
    void printMatrix();
    int at(int, int);
    bool edit(int, int, int);
    void trans();
};

TriMatrix::TriMatrix(const V2D<int> &v) {
    rows = v.size();
    cols = v[0].size();
    for (int n = 0; n < rows; ++n)
        for (int m = 0; m < cols; ++m)
            if (v[n][m] != 0)
                data.push_back(TriNode(n, m, v[n][m]));
}

void TriMatrix::printMatrix() {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c)
            std::cout << at(r, c) << ' ';
        std::cout << std::endl;
    }
}

int TriMatrix::at(int ro, int co) {
    if (ro >= rows || co >= cols) { std::cerr<< "out of range\n"; return 0; }
    for (int n = 0; n < static_cast<int>(data.size()); ++n)
        if (data[n].r == ro && data[n].c == co)
            return data[n].data;
    return 0;
}

bool TriMatrix::edit(int ro, int co, int val) {
    if (ro >= rows || co >= cols) { std::cerr<< "out of range\n"; return false; }
    int n;
    for (n = 0; data[n].r <= ro; ++n) {
        if (data[n].r == ro && data[n].c == co) {
            data[n].data = val;
            return true;
        }
        if (data[n].r == ro && data[n].c > co)
            break;
    }
    data.insert(data.begin()+n, TriNode(ro, co, val));
    return true;
}

void TriMatrix::trans() {
    int t;
    t = rows;
    rows = cols;
    cols = t;
    for (size_t n = 0; n < data.size(); ++n) {
        t = data[n].r;
        data[n].r = data[n].c;
        data[n].c = t;
    }
    std::sort(data.begin(), data.end());
}

#endif // TRIPLENODE_H

