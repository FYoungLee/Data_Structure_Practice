#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

struct monomial {
    int coef, expon;
    monomial *link;
    monomial(int x = 0, int y = 0) : coef(x), expon(y), link(nullptr) {}
//    friend monomial operator+(const monomial& lft, const monomial& rht);
//    friend monomial operator*(const monomial& lft, const monomial& rht);
//    friend monomial operator==(const monomial& lft, const monomial& rht);
//    friend monomial operator>(const monomial& lft, const monomial& rht);
};

class polynomial {
    monomial *head;
public:
    polynomial() : head(new monomial) {}
    polynomial(const monomial&);
    ~polynomial();
    void push(const monomial&);
    void paste(monomial*);
    void pop();
    void sort();
    void disp();
    friend monomial* operator+(const polynomial&, const polynomial&);
    friend monomial* operator*(const polynomial&, const polynomial&);
};

#endif // POLYNOMIAL_H
