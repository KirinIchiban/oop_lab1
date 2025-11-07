#pragma once

#include "shape.h"
#include <vector>
#include <memory>

class Array {
public:
    Array();
    void Add(Shape* shape);
    void Remove(size_t index);
    void Print() const;
    double All_squeare() const;
    void Centers() const;
    ~Array();

private:
    Shape** data;     
    size_t size;       
    size_t capacity;
    void Resize();
};