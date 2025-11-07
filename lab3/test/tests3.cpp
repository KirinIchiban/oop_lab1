#include <gtest/gtest.h>
#include <stdexcept>
#include <iostream>

#include "../include/rhomb.h"
#include "../include/trapeze.h"      
#include "../include/array.h"      
#include "../include/pentagon.h"

template <typename T>
T* createFigure(const std::string& input_str) {
    std::stringstream ss(input_str);
    T* fig = new T();
    fig->get_coords(ss);
    return fig;
}

//
// ---------- ТЕСТЫ ДЛЯ PENTAGON ----------
//

TEST(PentagonTest, AreaCalculation) {
    Pentagon* p = createFigure<Pentagon>("0 0 2 0 3 2 1 4 -1 2");
    double expected_area = p->Squere(); 
    EXPECT_NEAR(static_cast<double>(*p), expected_area, 1e-9);

    delete p;
}

TEST(PentagonTest, CenterCalculation) {
    Pentagon* p = createFigure<Pentagon>("0 0 2 0 3 2 1 4 -1 2");
    Point c = p->Center();
    EXPECT_NEAR(c.get_x(), 1.0, 1.0);
    EXPECT_NEAR(c.get_y(), 1.5, 1.0);

    delete p;
}

TEST(PentagonTest, EqualityOperator) {
    Pentagon* p1 = createFigure<Pentagon>("0 0 2 0 3 2 1 4 -1 2");
    Pentagon* p2 = createFigure<Pentagon>("0 0 2 0 3 2 1 4 -1 2");
    Pentagon* p3 = createFigure<Pentagon>("0 0 2 0 3 2 1 4 0 2");

    EXPECT_TRUE(*p1 == *p2);
    EXPECT_FALSE(*p1 == *p3);

    delete p1;
    delete p2;
    delete p3;
}

TEST(PentagonTest, OutputStream) {
    Pentagon* p = createFigure<Pentagon>("0 0 2 0 3 2 1 4 -1 2");

    testing::internal::CaptureStdout();
    p->print_figure(std::cout);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("pentagon"), std::string::npos);
    EXPECT_NE(output.find("("), std::string::npos);

    delete p;
}

// ---------- ТЕСТЫ ДЛЯ ARRAY ----------

TEST(ArrayTest, AddAndTotalArea) {
    Array arr;

    Shape* p1 = createFigure<Pentagon>("0 0 2 0 3 2 1 4 -1 2");
    Shape* p2 = createFigure<Pentagon>("0 0 1 0 1 1 0 1 0.5 1.5");

    arr.Add(p1);
    arr.Add(p2);

    double expected = p1->Squere() + p2->Squere();
    EXPECT_NEAR(arr.All_squeare(), expected, 1e-9);
}

TEST(ArrayTest, RemoveValid) {
    Array arr;

    Shape* p1 = createFigure<Pentagon>("0 0 2 0 3 2 1 4 -1 2");
    Shape* p2 = createFigure<Pentagon>("0 0 1 0 1 1 0 1 0.5 1.5");

    arr.Add(p1);
    arr.Add(p2);

    double before = arr.All_squeare();
    arr.Remove(0);

    EXPECT_NEAR(arr.All_squeare(), p2->Squere(), 1e-9);
    EXPECT_LT(arr.All_squeare(), before);
}

TEST(ArrayTest, RemoveOutOfCapacity) {
    Array arr;
    arr.Add(createFigure<Pentagon>("0 0 2 0 3 2 1 4 -1 2"));
    EXPECT_THROW(arr.Remove(5), std::out_of_range);
    EXPECT_THROW(arr.Remove(999), std::out_of_range);
}

TEST(ArrayTest, PrintOutput) {
    Array arr;
    arr.Add(createFigure<Pentagon>("0 0 2 0 3 2 1 4 -1 2"));

    testing::internal::CaptureStdout();
    arr.Print();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("pentagon"), std::string::npos);
}

TEST(ArrayTest, CentersOutput) {
    Array arr;
    arr.Add(createFigure<Pentagon>("0 0 2 0 3 2 1 4 -1 2"));

    testing::internal::CaptureStdout();
    arr.Centers();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("("), std::string::npos);
}

// ---------- ТЕСТЫ ДЛЯ TRAPEZE ----------

TEST(TrapezeTest, SimpleArea) {
    // Прямая трапеция с координатами:
    // A(0,0), B(4,0), C(3,2), D(1,2)
    Trapeze* t = createFigure<Trapeze>("0 0 4 0 3 2 1 2");

    // Основания: 4 и 2, высота: 2
    double expected_area = (4 + 2) / 2.0 * 2; // = 6
    EXPECT_NEAR(t->Squere(), expected_area, 1e-9);
    EXPECT_EQ(static_cast<double>(*t), expected_area);

    delete t;
}

TEST(TrapezeTest, CenterRoughlyMiddle) {
    Trapeze* t = createFigure<Trapeze>("0 0 4 0 3 2 1 2");
    Point c = t->Center();
    EXPECT_NEAR(c.get_x(), 2.0, 0.5);
    EXPECT_NEAR(c.get_y(), 1.0, 0.5);

    delete t;
}

TEST(TrapezeTest, EqualityOperator) {
    Trapeze* t1 = createFigure<Trapeze>("0 0 4 0 3 2 1 2");
    Trapeze* t2 = createFigure<Trapeze>("0 0 4 0 3 2 1 2");
    Trapeze* t3 = createFigure<Trapeze>("0 0 3 0 2 1 1 1");

    EXPECT_TRUE(*t1 == *t2);
    EXPECT_FALSE(*t1 == *t3);

    delete t1;
    delete t2;
    delete t3;
}

TEST(TrapezeTest, PrintOutput) {
    Trapeze* t = createFigure<Trapeze>("0 0 4 0 3 2 1 2");

    testing::internal::CaptureStdout();
    t->print_figure(std::cout);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("trapeze"), std::string::npos);
    EXPECT_NE(output.find("("), std::string::npos);

    delete t;
}

// ---------- ТЕСТЫ ДЛЯ Rhomb ----------

TEST(RhombTest, SimpleSquareArea) {
    // Ромб со стороной 2, диагонали 4 и 2 => площадь = (4 * 2) / 2 = 4
    // Пусть вершины: (0,0), (2,1), (0,2), (-2,1)
    Rhomb* r = createFigure<Rhomb>("0 0 2 1 0 2 -2 1");

    double expected_area = 4.0;
    EXPECT_NEAR(r->Squere(), expected_area, 1e-9);
    EXPECT_EQ(static_cast<double>(*r), expected_area);

    delete r;
}

TEST(RhombTest, CenterShouldBeAtOrigin) {
    // Ромб симметричен относительно начала координат
    Rhomb* r = createFigure<Rhomb>("-1 -1 1 -1 1 1 -1 1");
    Point c = r->Center();

    EXPECT_NEAR(c.get_x(), 0.0, 1e-9);
    EXPECT_NEAR(c.get_y(), 0.0, 1e-9);

    delete r;
}

TEST(RhombTest, EqualityOperator) {
    Rhomb* r1 = createFigure<Rhomb>("0 0 2 1 0 2 -2 1");
    Rhomb* r2 = createFigure<Rhomb>("0 0 2 1 0 2 -2 1");
    Rhomb* r3 = createFigure<Rhomb>("0 0 3 1 1 3 -2 2");

    EXPECT_TRUE(*r1 == *r2);
    EXPECT_FALSE(*r1 == *r3);

    delete r1;
    delete r2;
    delete r3;
}

TEST(RhombTest, OutputStream) {
    Rhomb* r = createFigure<Rhomb>("0 0 2 1 0 2 -2 1");

    testing::internal::CaptureStdout();
    r->print_figure(std::cout);
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("rhomb"), std::string::npos);
    EXPECT_NE(output.find("("), std::string::npos);

    delete r;
}

// ---------- ТЕСТЫ ДЛЯ ARRAY (С TRAPEZE и Rhomb) ----------

TEST(ArrayTest, AddAndTotalAr) {
    Array arr;

    Shape* t = createFigure<Trapeze>("0 0 4 0 3 2 1 2");  // площадь 6
    Shape* r = createFigure<Rhomb>("-1 -1 1 -1 1 1 -1 1"); // квадрат со стороной 2 → S = 4

    arr.Add(t);
    arr.Add(r);

    EXPECT_NEAR(arr.All_squeare(), 10.0, 1e-9);
}

TEST(ArrayTest, RemoveAndRecalculateArea) {
    Array arr;

    Shape* t = createFigure<Trapeze>("0 0 4 0 3 2 1 2");  // S = 6
    Shape* r = createFigure<Rhomb>("-1 -1 1 -1 1 1 -1 1"); // S = 4

    arr.Add(t);
    arr.Add(r);

    EXPECT_NEAR(arr.All_squeare(), 10.0, 1e-9);

    arr.Remove(0); // удаляем трапецию
    EXPECT_NEAR(arr.All_squeare(), 4.0, 1e-9);
}

TEST(ArrayTest, CenterinArrayOutput) {
    Array arr;
    arr.Add(createFigure<Rhomb>("-1 -1 1 -1 1 1 -1 1"));
    arr.Add(createFigure<Trapeze>("0 0 4 0 3 2 1 2"));

    testing::internal::CaptureStdout();
    arr.Centers();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("("), std::string::npos);
}

TEST(ArrayTest, RemoveOutOfRange) {
    Array arr;
    arr.Add(createFigure<Rhomb>("0 0 2 1 0 2 -2 1"));
    EXPECT_THROW(arr.Remove(10), std::out_of_range);
    EXPECT_THROW(arr.Remove(5), std::out_of_range);
}
