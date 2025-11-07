#include "../include/pentagon.h"
#include "../include/triangle.h"
#include <cmath>

Pentagon::Pentagon() {
    coords = new Point[count]; 
}

Pentagon::Pentagon(const Pentagon& other) : count(other.count) {
    coords = new Point[count];
    for (int i = 0; i < count; ++i){
        coords[i] = other.coords[i];
    }
}

Pentagon::Pentagon(Pentagon&& other) noexcept : coords(other.coords), count(other.count) {
    other.coords = nullptr;
    other.count= 0;
}

Pentagon& Pentagon::operator=(const Pentagon& other) {
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

Pentagon& Pentagon::operator=(Pentagon&& other) noexcept {
    if (this != &other) {
        delete[] coords;
        coords = other.coords;
        count = other.count;
        other.coords = nullptr;
        other.count = 0;
    }
    return *this;
}

void Pentagon::print_figure(std::ostream& os) const {
    os << "pentagon: ";
    for (int i = 0; i < 5; ++i){
        os << coords[i] << " ";
    }
    os << ";";
}

void Pentagon::get_coords(std::istream& is) {
    for (size_t i = 0; i < 5; i++) {
        is >> coords[i];
    }
}

Point Pentagon::Center() const {
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

double Pentagon::Squere() const {
    double S1 = Squere_triangle(coords[0], coords[1], coords[2]);
    double S2 = Squere_triangle(coords[0], coords[2], coords[3]);
    double S3 = Squere_triangle(coords[0], coords[3], coords[4]);
    return S1 + S2 + S3;
}

Pentagon::operator double() const {
    return Squere();
}

bool Pentagon::operator==(const Shape& other) const {
    if (typeid(*this) != typeid(other)) { return false; }
    const Pentagon& my_oth = static_cast<const Pentagon&>(other);
    if (this->count != my_oth.count) return false;
    else {
        for (int i = 0; i < (*this).count; i++) {
            if (!((*this).coords[i] == my_oth.coords[i])) { return false; }
        }
    }
    return true;
}

Pentagon::~Pentagon() {
    delete[] coords;
}