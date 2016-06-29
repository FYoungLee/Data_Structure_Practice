//
//  MyGroup.h
//  CPP
//
//  Created by mac on 6/28/16.
//  Copyright (c) 2016 Fyang. All rights reserved.
//
/*****************/
#ifndef MYGROUP_H
#define MYGROUP_H
#include <iostream>
template <typename T>
class Node {
public:
    T data;
    Node * next;
    Node() { next = nullptr; }
    Node(const T&);
    ~Node();
    template <typename pT>
        friend std::ostream& operator<<(std::ostream& os, const Node<pT>& n);
};

template <typename T>
Node<T>::Node(const T& _data) {
    data = _data;
    next = nullptr;
}

template <typename T>
Node<T>::~Node() {
    if (!next)
        delete next;
    next = nullptr;
}
template <typename pT>
std::ostream& operator<<(std::ostream& os, const Node<pT>& n) {
        os << n.data;
        return os;
}

/*****************/
template <typename T>
class My_Group {
    Node<T>* Head;
public:
    My_Group();
    My_Group(const Node<T>&);
    ~My_Group();
    size_t display();                       //输出链表，返回值为链表中的结点数
    template <typename fT>
        friend std::ostream& operator<<(std::ostream& os, const My_Group<fT>& mg);
    T operator[](size_t n);
    void insert(const Node<T>&);            //插入：将结点插入链表，该结点作为第一个结点
    void append(const Node<T>&);            //追加：将结点插入链表，该结点作为最后一个结点
    void put(size_t n, const Node<T>&);     // 在 n 位置 放置一个 m。
    void cat(My_Group&);                    //将链表il连接到当前对象的后面
    void cut(size_t);                       //删除第几个节点
    void cut(size_t, size_t);               //删除范围内节点
    void cut(const Node<T>&);               //删除某个值的节点
    size_t find(const Node<T>&);            //查找m
    size_t length();                        //返回链表中的结点数
    Node<T>* get_addres(size_t n);          //查找n号位元素返回指针
    T cut_biggest();                        //删除最大
    T cut_smallest();                       //删除最小
    void s_sort();                          //由小到大排序
    void b_sort();                          //由大到小排序
    void reverse();                         //反转链表
};

template <typename T>
My_Group<T>::My_Group(): Head(new Node<T>) {
    Head->next = nullptr;
}

template <typename T>
My_Group<T>::My_Group(const Node<T> &n): Head(new Node<T>) {
    Node<T> * nd = new Node<T>;
    nd->data = n.data;
    Head->next = nd;
}
template <typename T>
My_Group<T>::~My_Group() {
    Node<T> * nd = Head;
    while (nd != nullptr) {
        nd = nd->next;
        delete Head;
        Head = nd;
    }
}

template <typename T>
size_t My_Group<T>::display() {
    Node<T> * pn = Head;
    size_t num = 1;
    while (pn) {
        std::cout << '[' << pn->data << "] -> ";
        pn = pn->next;
        ++num;
    }
    std::cout << "[]"<< std::endl;
    return num;
}

template <typename fT>
std::ostream& operator<<(std::ostream& os, const My_Group<fT>& mg) {
    auto * pn = mg.Head;
    while (pn) {
        os << pn->data << ' ';
        pn = pn->next;
    }
    return os;
}
template <typename T>
T My_Group<T>::operator[](size_t n) {
    if (n > length()) return T();
    Node<T> * pn = Head;
    for (size_t m = n; m--;)
        pn = pn->next;
    return pn->data;
}

template <typename T>
void My_Group<T>::put(size_t n, const Node<T>& m) {
    size_t len = length();
    if (len == 0 || n == 0)   insert(m);            // 当链表为空，无论给出什么位置都插入， 或者位置为0，插入第一个位置。
    else if (n >= len)  append(m);                  // 当位置大于或等于节点数，追加在后面。
    else {                                          // 放置到节点数以内的n位置。
        Node<T>* pn = new Node<T>, *pt = Head;
        pn->data = m.data;
        for (len = 1; len < n; ++len)
            pt = pt->next;
        pn->next = pt->next;
        pt->next = pn;
    }
}

template <typename T>
void My_Group<T>::insert(const Node<T>& n) {
    Node<T> *pn = new Node<T>;
    pn->data = n.data;
    pn->next = Head->next;
    Head->next = pn;
}

template <typename T>
void My_Group<T>::append(const Node<T> &n) {
    Node<T> *pn = new Node<T>, *pt = Head;
    pn->data = n.data;
    while (pt->next)
        pt = pt->next;
    pt->next = pn;
}

template <typename T>
void My_Group<T>::cat(My_Group & mg) {
    Node<T> *pn = Head->next, *pt = mg.Head->next;
    while (pn->next)
        pn = pn->next;
    while (pt) {
        Node<T> *cn = new Node<T>;
        cn->data = pt->data;
        pn->next = cn;
        pn = pn->next;
        pt = pt->next;
    }
}

template <typename T>
void My_Group<T>::cut(size_t n) {
    if (n == 0) { std::cerr << "invalid\n"; return;}
    Node<T> *p = get_addres(n - 1), *pt;
    if (!p) { std::cerr << "invalid\n"; return;}
    pt = p->next;
    p->next = pt->next;
    delete pt;
}

template <typename T>
void My_Group<T>::cut(size_t n, size_t m) {
    if (n > m || n == 0) { std::cerr << "invalid\n"; return;}
    Node<T> *ps = get_addres(n - 1), *pt;
    if (!ps) { std::cerr << "invalid\n"; return;}
    while (n <= m) {
        if (!ps->next) return;
        pt = ps->next;
        ps->next = pt->next;
        delete pt;
        ++n;
    }
}

template <typename T>
void My_Group<T>::cut(const Node<T>& m) {
    if (!Head->next) return;
    Node<T> *p = Head->next, *pt;
    while (p->next->next && p->next->data != m.data)
        p = p->next;
    if (p->next) {
        pt = p->next;
        p->next = pt->next;
        delete pt;
    }
}

template <typename T>
size_t My_Group<T>::find(const Node<T>& m){
    Node<T> * pn = Head;
    size_t num = 1;
    while (pn) {
        if (pn->data != m.data) {
            pn = pn->next;
            ++num;
        } else return num;
    }
    return 0;
}

template <typename T>
size_t My_Group<T>::length() {
    Node<T> * pn = Head->next;
    size_t num = 0;
    while (pn) {
        pn = pn->next;
        ++num;
    }
    return num;
}

template <typename T>
Node<T>* My_Group<T>::get_addres(size_t n){
    Node<T> * pn = Head;
    for (size_t m = n; m--;) {
        pn = pn->next;
        if (!pn) return nullptr;
    }
    return pn;
}

template <typename T>
T My_Group<T>::cut_biggest() {
    if (Head->next == nullptr) return T();
    Node<T> *p = Head->next, *pt;
    T t = p->data;
    pt = p;
    while (p->next) {
        if (t < p->next->data) {
            t = p->next->data;
            pt = p;
        }
        p = p->next;
    }
    p = pt->next;
    pt->next = p->next;
    delete p;
    return t;
}

template <typename T>
T My_Group<T>::cut_smallest() {
    if (Head->next == nullptr) return T();
    Node<T> *p = Head->next, *pt;
    T t = p->data;
    pt = p;
    while (p->next) {
        if (t > p->next->data) {
            t = p->next->data;
            pt = p;
        }
        p = p->next;
    }
    p = pt->next;
    pt->next = p->next;
    delete p;
    return t;
}

template <typename T>
void My_Group<T>::s_sort() {
    if (Head->next->next == nullptr) return;
/*  排序算法1，取符合条件的节点出来插入最前面，然后范围起始指针往后挪
    Node<T> *ps = Head;
    while (ps->next) {
        Node<T> *p = ps->next, *pt;
        T t = ps->next->data;
        pt = ps;
        while (p->next) {
            if (t > p->next->data) {
                t = p->next->data;
                pt = p;
            }
            p = p->next;
        }
        p = pt->next;
        pt->next = p->next;
        p->next = ps->next;
        ps->next = p;
        ps = p;
    }
*//*  排序算法2，截断成2个链，然后挨个从第二个链中取出头节点与第一链从头比较放入序列合适位置。*/
    Node<T> *p1 = Head, *p2 = Head->next->next, *p3;
    p1->next->next = nullptr;
    while (p2) {
        p3 = p2->next;
        while (p1->next && p2->data > p1->next->data)
            p1 = p1->next;
        p2->next = p1->next;
        p1->next = p2;
        p2 = p3;
        p1 = Head;
    }
}

template <typename T>
void My_Group<T>::b_sort() {
    if (Head->next->next == nullptr) return;
    Node<T> *p1 = Head, *p2 = Head->next->next, *p3;
    p1->next->next = nullptr;
    while (p2) {
        p3 = p2->next;
        while (p1->next && p2->data < p1->next->data)
            p1 = p1->next;
        p2->next = p1->next;
        p1->next = p2;
        p2 = p3;
        p1 = Head;
    }
}

template <typename T>
void My_Group<T>::reverse() {
    if (!Head->next) return;
    auto p = Head->next->next;
    Head->next->next = nullptr;
    while (p) {
        auto pn = p->next;
        p->next = Head->next;
        Head->next = p;
        p = pn;
    }
}

#endif // MYGROUP_H
