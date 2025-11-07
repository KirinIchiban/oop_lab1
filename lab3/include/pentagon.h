#include "shape.h"

class Pentagon : public Shape
{
public:
    Pentagon();
    Pentagon(const Pentagon& other);
    Pentagon(Pentagon&& other) noexcept;

    Pentagon& operator=(const Pentagon& other);
    Pentagon& operator=(Pentagon&& other) noexcept;
    virtual void print_figure(std::ostream& os) const override;
    virtual void get_coords(std::istream& is) override;
    virtual Point Center() const override;
    virtual double Squere() const override;
    virtual operator double() const override;
    virtual bool operator==(const Shape& other) const override;

    ~Pentagon();

private:
    Point* coords{nullptr};
    int count{5};
};
