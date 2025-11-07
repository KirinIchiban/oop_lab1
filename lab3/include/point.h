#ifndef POINT_H
#define POINT_H
#include <iostream>
#include <cmath>

class Point
{
public:

    Point();
    Point(std::istream &is);
    Point(double x, double y) : m_x(x), m_y(y) {}

    double dist(Point& other);
    double get_x() const { return m_x; }
    double get_y() const { return m_y; }
  
    friend std::istream& operator>>(std::istream& is, Point& p);
    friend std::ostream& operator<<(std::ostream& os, Point& p);
    bool operator==(const Point& other) const;

private:
    double m_x{};
    double m_y{};
};

#endif