#include "polynomial.h"
#include <iostream>
//monomial operator+(const monomial& lft, const monomial& rht) {
//    monomial ret;
//    ret.coef = lft.coef + rht.coef;
//    return ret;
//}

//monomial operator*(const monomial& lft, const monomial& rht) {
//    monomial ret;
//    ret.coef = lft.coef * rht.coef;
//    ret.expon = lft.expon + rht.expon;
//    return ret;
//}
//monomial operator==(const monomial& lft, const monomial& rht) {
//    return lft.expon == rht.expon;
//}

//monomial operator>(const monomial& lft, const monomial& rht) {
//    return lft.expon > rht.expon;
//}


polynomial::polynomial(const monomial& mo) {
    head = new monomial;
    monomial* n = new monomial(mo.coef, mo.expon);
    head->link = n;
}

polynomial::~polynomial() {
    while (head) {
        auto p = head;
        head = head->link;
        delete p;
    }
}

void polynomial::push(const monomial& mo) {
    monomial* p = head;
    while (p->link)
        p = p->link;
    monomial* n = new monomial(mo.coef, mo.expon);
    p->link = n;
}

void polynomial::paste(monomial* mo) {
    head = mo;
}

void polynomial::pop() {
    if (!head) return;
    monomial *p = head;
    while (p->link)
        p = p->link;
    delete p;
}

void polynomial::sort() {
    if (!head->link->link) return;
    auto pre = head;
    auto p = head->link;
    auto pt = p->link;
    while (pt) {
        if (p->expon < pt->expon) {
            pre->link = pt;
            p->link = pt->link;
            pt->link = p;
            p = pt;
            pt = p->link;
        } else {
            pt = pt->link;
        }
        if (!pt && p->link) {
            pre = pre->link;
            p = p->link;
            pt = p->link;
        }
    }
    pre = head;
    p = head->link;
    pt = p->link;
    while (pt) {
        if (p->expon == pt->expon) {
            p->coef += pt->coef;
            p->link = pt->link;
            auto pd = pt;
            pt = pt->link;
            delete pd;
        } else {
            pre = pre->link;
            p = p->link;
            pt = p->link;
        }
    }
}

void polynomial::disp() {
    auto p = head->link;
    while (p) {
        std::cout << p->coef;
        if (p->expon)
            std::cout << "*X^" << p->expon;
        if (p->link && p->link->coef > 0)
            std::cout << " +";
        else std::cout << " ";
        p = p->link;
    }
    std::cout << std::endl;
}

monomial* operator+(const polynomial& lft, const polynomial& rht) {
    auto lfp = lft.head->link; auto rtp = rht.head->link;
    monomial* n = new monomial;
    auto *p = n;
    while (lfp && rtp) {
        if (lfp->expon == rtp->expon) {
            auto coef = lfp->coef + rtp->coef;
            monomial* mn = new monomial(coef, lfp->expon);
            p->link = mn;
            p = mn;
            lfp = lfp->link;
            rtp = rtp->link;
        } else if (lfp->expon > rtp->expon) {
            monomial* mn = new monomial(lfp->coef, lfp->expon);
            p->link = mn;
            p = mn;
            lfp = lfp->link;
        } else {
            monomial* mn = new monomial(rtp->coef, rtp->expon);
            p->link = mn;
            p = mn;
            rtp = rtp->link;
        }
    }
    while (lfp) {
        monomial* mn = new monomial(lfp->coef, lfp->expon);
        p->link = mn;
        p = mn;
        lfp = lfp->link;
    }
    while (rtp) {
        monomial* mn = new monomial(rtp->coef, rtp->expon);
        p->link = mn;
        p = mn;
        rtp = rtp->link;
    }
    return n;
}

monomial* operator*(const polynomial& lft, const polynomial& rht) {
    auto lfp = lft.head->link; auto rtp = rht.head->link;
    monomial* n = new monomial;
    auto *p = n;
    while (rtp) {
        while (lfp) {
            auto coef = lfp->coef * rtp->coef;
            auto expon = lfp->expon + rtp->expon;
            monomial* mn = new monomial(coef, expon);
            p->link = mn;
            p = mn;
            lfp = lfp->link;
        }
        rtp = rtp->link;
        lfp = lft.head->link;
    }
    return n;
}
