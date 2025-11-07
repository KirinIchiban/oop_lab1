# include "../include/array.h"

Array::Array() : data(nullptr), size(0), capacity(0) {}

void Array::Add(Shape* shape) {
    if (size >= capacity) {
        Resize();
    }
    data[size++] = shape;
}

void Array::Remove(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Out_of_range");
    }
    delete data[index];
    for (size_t i = index; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
    data[--size] = nullptr;
}

void Array::Print() const {
    if (size == 0) {
        return;
    }
    for (size_t i = 0; i < size; ++i) {
        data[i]->print_figure(std::cout); 
    }
}

double Array::All_squeare() const {
    if (size == 0) {
        return -1.0;
    }
    double total = 0;
    for (size_t i = 0; i < size; ++i) {
        total += data[i]->Squere();
    }
    return total;
}


void Array::Centers() const {
    if (size == 0) {
        return;
    }
    for (size_t i = 0; i < size; ++i) {
        Point cent = data[i]->Center();  
        std::cout << i << cent <<endl;
    }
}

void Array::Resize() {  
    size_t newlen = (capacity == 0) ? 1 : capacity * 2;
    Shape** new_data = new Shape*[newlen];
    for (size_t i = 0; i < size; ++i) {
        new_data[i] = data[i];
    }

    delete[] data;
    data = new_data;
    capacity = newlen;
}


Array::~Array() {
    for (size_t i = 0; i < size; ++i) {
        delete data[i];
    }
    delete[] data;
}