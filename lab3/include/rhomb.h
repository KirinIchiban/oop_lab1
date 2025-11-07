#include "shape.h"

class Rhomb : public Shape
{
public:
    Rhomb();
    Rhomb(const Rhomb& other);
    Rhomb(Rhomb&& other) noexcept;

    Rhomb& operator=(const Rhomb& other);
    Rhomb& operator=(Rhomb&& other) noexcept;
    virtual void print_figure(std::ostream& os) const override;
    virtual void get_coords(std::istream& is) override;
    virtual Point Center() const override;
    virtual double Squere() const override;
    virtual operator double() const override;
    virtual bool operator==(const Shape& other) const override;

    ~Rhomb();

private:
    Point* coords{nullptr};
    int count{4};
};

