#pragma once 

#ifndef SAIL
#define SAIL

#include "common.h"

SAIL_NAMESPACE_BEGIN
int add(int a, int b) { return a + b;}
class vec {
public:
    vec(): e{} { len = 0; } // use empty vector by default
    vec(double _x, double _y, double _z): e{_x, _y, _z} { len = 3; }
    ~vec() { e.clear(); len = 0;}
// GET
    double x() const { if (len > 0) return e[0]; else return 0;}
    double y() const { if (len > 1) return e[1]; else return 0;}
    double z() const { if (len > 2) return e[2]; else return 0;}
    double w() const { if (len > 3) return e[3]; else return 0;}
    double operator[](int i) const { if (i < len) return e[i]; else return 0;}
    int getLen() const { return len;}
// SET
    double set(int i, double val) { e[i] = val; }
    void push_back(double val) { e.push_back(val); len+=1; }

public:
// COMPUTE

protected:
    int len = 0;
    std::vector<double> e;
};

inline vec operator+(const vec &u, const vec &v) {
    int lu = u.getLen();
    int lv = v.getLen();
    int len = IMAX(lu, lv);
    vec sum;
    for (int i=0; i < len; i++) {
        sum.push_back(u[i]+v[i]);
    }
    return sum;
}
SAIL_NAMESPACE_END

#endif
