#pragma once
#include "point.h"

inline double Squere_triangle(const Point& A, const Point& B, const Point& C) {
    return std::fabs(
        A.get_x()*(B.get_y() - C.get_y()) + 
        B.get_x()*(C.get_y() - A.get_y()) + 
        C.get_x()*(A.get_y() - B.get_y())
    ) / 2.0;
}

