#ifndef ORTHOGONALLIST
#define ORTHOGONALLIST
#include <iostream>
#include <vector>
#include <memory>
using namespace std;
template <typename T>
using Vec2d = std::vector<std::vector<T>>;
using r_pos = int;
using c_pos = int;

template <class T>
struct Orth_Node {
    r_pos row;
    c_pos col;
    T data;
    shared_ptr<Orth_Node> r, d;
};

template <class T>
class Orth_List {
    shared_ptr<Orth_Node<T>> Head;
public:
    Orth_List(const Vec2d<T>&);
    bool set(r_pos, c_pos, const T&);
    void r_view();
    void d_view();
    void PrintMatrix();
};

template <class T>
Orth_List<T>::Orth_List(const Vec2d<T>& v2) {
    Head = std::make_shared<Orth_Node<T>>();
    Head->d = Head->r = Head;
    Head->row = v2.size();
    Head->col = v2[0].size();
    shared_ptr<Orth_Node<T>> p = Head, pt;
    /* creating rows head chain */
    for (size_t n = 0; n < v2.size(); ++n) {
        shared_ptr<Orth_Node<T>> node(new Orth_Node<T>);
        node->d = p->d;
        node->r = node; // make the new node point to itself in right side.
        p->d = node;
        p = node;
    }
    p = Head;
    /* creating columns head chain */
    for (size_t n = 0; n < v2[0].size(); ++n) {
        shared_ptr<Orth_Node<T>> node(new Orth_Node<T>);
        node->r = p->r;
        node->d = node; // make the new node point to itself in down side.
        p->r = node;
        p = node;
    }

    for (size_t m = 0; m < v2.size(); ++m)
        for (size_t n = 0; n < v2[m].size(); ++n)
            if (v2[m][n] != 0) { // catch a non-zero value from array
                shared_ptr<Orth_Node<T>> node(new Orth_Node<T>);
                node->row = m;
                node->col = n;
                node->data = v2[m][n]; // assign values to new node.
                p = Head->d; // mark row headers.
                for (auto i = m; i--;) // catch the accurate row.
                    p = p->d;
                pt = p; // mark the row header.
                while (p->r != pt) // get to last node in this row.
                    p = p->r;
                node->r = p->r; // append new node to rear.
                p->r = node;
                // appending the new node to column, same operation as above.
                p = Head->r;
                for (auto i = n; i--;)
                    p = p->r;
                pt = p;
                while (p->d != pt)
                    p = p->d;
                node->d = p->d;
                p->d = node;
            }
}

template <class T>
bool Orth_List<T>::set(r_pos ro, c_pos co, const T& val) {
    if (ro >= Head->row || co >= Head->col) return false;
    shared_ptr<Orth_Node<T>> pr = Head->r, pd = Head->d, pn(new Orth_Node<T>), pt;
    pn->row = ro, pn->col = co, pn->data = val;
    auto tro = ro, tco = co;
    while (tro--)
        pd = pd->d;
    while (tco--)
        pr = pr->r;
    pt = pd;
    while (pd->r != pt && pd->r->col < co)
        pd = pd->r;
    pt = pr;
    while (pr->d != pt && pr->d->row < ro)
        pr = pr->d;
    if (pd->r->col == co && pr->d->row == ro) {
        pd->r->data = val;
        return true;
    } else {
        pn->r = pd->r;
        pd->r = pn;
        pn->d = pr->d;
        pr->d = pn;
        return true;
    }
}

template <class T>
void Orth_List<T>::r_view() {
    shared_ptr<Orth_Node<T>> p = Head, pt;
    while (p->d != Head) {
        p = p->d;
        pt = p;
        p = p->r;
        while (p != pt) {
            std::cout << "(" << p->row << "," << p->col << ") : [" << p->data <<"]\n";
            p = p->r;
        }
        p = pt;
    }
}

template <class T>
void Orth_List<T>::d_view() {
    shared_ptr<Orth_Node<T>> p = Head, pt;
    while (p->r != Head) {
        p = p->r;
        pt = p;
        p = p->d;
        while (p != pt) {
            std::cout << "(" << p->row << "," << p->col << ") : [" << p->data <<"]\n";
            p = p->d;
        }
        p = pt;
    }
}

template <class T>
void Orth_List<T>::PrintMatrix() {
    shared_ptr<Orth_Node<T>> p = Head->d, pt;
    while (p != Head) {
        pt = p;
        p = p->r;
        for (r_pos n = 0; n != Head->col; ++n) {
            if (p->col == n) {
                cout << p->data << ' ';
                p = p->r;
            } else cout << 0 << ' ';
        }
        cout << endl;
        p = pt->d;
    }
}

#endif // ORTHOGONALLIST

