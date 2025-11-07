#include "../include/trapeze.h"
#include "../include/triangle.h"
#include <cmath>

Trapeze::Trapeze() {
    coords = new Point[count];
}

Trapeze::Trapeze(const Trapeze& other) : count(other.count) {
    coords = new Point[count];
    for (int i = 0; i < count; ++i){
        coords[i] = other.coords[i];
    }
}

Trapeze::Trapeze(Trapeze&& other) noexcept : coords(other.coords), count(other.count) {
    other.coords = nullptr;
    other.count= 0;
}

Trapeze& Trapeze::operator=(const Trapeze& other) {
    if (this != &other) {
        delete[] coords;  
        count = other.count;
        coords = new Point[count]; 
        for (int i = 0; i < count; ++i) {
            coords[i] = other.coords[i];
        }
    }
    return *this;
}

Trapeze& Trapeze::operator=(Trapeze&& other) noexcept {
    if (this != &other) {
        delete[] coords;
        coords = other.coords;
        count = other.count;
        other.coords = nullptr;
        other.count = 0;
    }
    return *this;
}

void Trapeze::print_figure(std::ostream& os) const {
    os << "trapeze: ";
    for (size_t i = 0; i < 4; ++i){
        os << coords[i] << " ";
    }
    os << ";";
}

void Trapeze::get_coords(std::istream& is) {
    for (size_t i = 0; i < 4; i++) {
        is >> coords[i];
    }
}

Point Trapeze::Center() const {
    double A = 0.0;
    double Cx = 0.0;
    double Cy = 0.0;

    for (int i = 0; i < count; i++) {
        int j = (i + 1) % count; 

        double cross = coords[i].get_x() * coords[j].get_y() - coords[j].get_x() * coords[i].get_y();
        A = A + cross;
        Cx = Cx + (coords[i].get_x() + coords[j].get_x()) * cross;
        Cy = Cy + (coords[i].get_y() + coords[j].get_y()) * cross;
    }

    A = A * 0.5;
    Cx = Cx / (6.0 * A);
    Cy = Cy / (6.0 * A);

    return Point(Cx, Cy);
}

double Trapeze::Squere() const {
    double S1 = Squere_triangle(coords[0], coords[1], coords[2]);
    double S2 = Squere_triangle(coords[0], coords[2], coords[3]);
    return S1 + S2;
}

Trapeze::operator double() const {
    return Squere();
}

bool Trapeze::operator==(const Shape& other) const {
    if (typeid(*this) != typeid(other)) { return false; }
    const Trapeze& my_oth = static_cast<const Trapeze&>(other);
    if (this->count != my_oth.count) return false;
    else {
        for (int i = 0; i < (*this).count; i++) {
            if (!((*this).coords[i] == my_oth.coords[i])) { return false; }
        }
    }
    return true;
}

Trapeze::~Trapeze() {
    delete[] coords;
}