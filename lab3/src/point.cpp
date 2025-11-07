#include "../include/point.h"

#include <cmath>

Point::Point() : m_x(0.0), m_y(0.0) {}
Point::Point(std::istream &is) {
  is >> m_x >> m_y;
}

double Point::dist(Point& other) {
    double dx = (other.m_x - m_x);
    double dy = (other.m_y - m_y);
    return std::sqrt(dx*dx + dy*dy);
}

std::istream& operator>>(std::istream& is, Point& p) {
    is >> p.m_x >> p.m_y;
    return is;
}

std::ostream& operator<<(std::ostream& os, Point& p) {
    os << "(" << p.m_x << ", " << p.m_y<< ")";
    return os;
}

int comparator (double a, double b) {
    if (!(a == b)) return a < b ? -1 : 1;
    return 0;
}

bool Point::operator==(const Point& other) const {
    return (comparator(this->m_x, other.m_x) == 0 && comparator(this->m_y, other.m_y) == 0);
}