#pragma once
#include <iostream>
#include <string.h>
#include <stdexcept>
#include "point.h"

using namespace std;

class Shape
{
    friend ostream& operator<<(ostream& os, const Shape& f);
    friend istream& operator>>(istream& is, Shape& f);

public:
    Shape() = default;
    virtual void print_figure(ostream& os) const = 0;
    virtual ~Shape() = default;
    virtual Point Center() const = 0;
    virtual double Squere() const = 0;
    virtual void get_coords(istream& is) = 0;
    virtual operator double() const = 0;
    virtual bool operator==(const Shape& other) const = 0;
};

inline ostream& operator<<(ostream& os, const Shape& area) {
    area.print_figure(os);
    return os;
}

inline istream& operator>>(istream& is, Shape& area) {
    area.get_coords(is);
    return is;
}