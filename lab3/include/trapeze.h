#include "shape.h"

class Trapeze : public Shape
{
public:
    Trapeze();
    Trapeze(const Trapeze& other);
    Trapeze(Trapeze&& other) noexcept;

    Trapeze& operator=(const Trapeze& other);
    Trapeze& operator=(Trapeze&& other) noexcept;
    virtual void print_figure(std::ostream& os) const override;
    virtual void get_coords(std::istream& is) override;
    virtual Point Center() const override;
    virtual double Squere() const override;
    virtual operator double() const override;
    virtual bool operator==(const Shape& other) const override;

    ~Trapeze();

private:
    Point* coords{nullptr};
    int count{4};
};

