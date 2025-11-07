#include "../include/rhomb.h"
#include "../include/triangle.h"
#include <cmath>

Rhomb::Rhomb() {
    coords = new Point[count]; 
}

Rhomb::Rhomb(const Rhomb& other) : count(other.count) {
    coords = new Point[count];
    for (int i = 0; i < count; ++i){
        coords[i] = other.coords[i];
    }
}

Rhomb::Rhomb(Rhomb&& other) noexcept : coords(other.coords), count(other.count) {
    other.coords = nullptr;
    other.count= 0;
}

Rhomb& Rhomb::operator=(const Rhomb& other) {
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

Rhomb& Rhomb::operator=(Rhomb&& other) noexcept {
    if (this != &other) {
        delete[] coords;
        coords = other.coords;
        count = other.count;
        other.coords = nullptr;
        other.count = 0;
    }
    return *this;
}

void Rhomb::print_figure(std::ostream& os) const {
    os << "rhomb: ";
    for (int i = 0; i < 4; ++i){
        os << coords[i] << " ";
    }
    os << ";";
}

void Rhomb::get_coords(std::istream& is) {
    for (size_t i = 0; i < 4; i++) {
        is >> coords[i];
    }
}

Point Rhomb::Center() const {
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

double Rhomb::Squere() const {
    double d1 = coords[0].dist(coords[2]);
    double d2 = coords[1].dist(coords[3]);
    return d1 * d2 / 2.0;
}

Rhomb::operator double() const {
    return Squere();
}

bool Rhomb::operator==(const Shape& other) const {
    if (typeid(*this) != typeid(other)) { return false; }
    const Rhomb& my_oth = static_cast<const Rhomb&>(other);
    if (this->count != my_oth.count) return false;
    else {
        for (int i = 0; i < (*this).count; i++) {
            if (!((*this).coords[i] == my_oth.coords[i])) { return false; }
        }
    }
    return true;
}

Rhomb::~Rhomb() {
    delete[] coords;
}