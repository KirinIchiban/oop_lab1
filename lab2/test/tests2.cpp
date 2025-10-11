#include <gtest/gtest.h>
#include "../include/headers.hpp"

TEST(ConstructorTest, DefaultConstructor) {
    Twelve t;
    EXPECT_EQ(t.tostr(), "0");
}

TEST(ConstructorTest, StringConstructorlz) {
    Twelve t("000A0B");
    EXPECT_EQ(t.tostr(), "A0B");
}

TEST(ConstructorTest, StringConstructorone) {
    Twelve t("B");
    EXPECT_EQ(t.tostr(), "B");
}

TEST(ConstructorTest, StringConstructor0) {
    Twelve t("0");
    EXPECT_EQ(t.tostr(), "0");
}

TEST(ConstructorTest, Emptystr) {
    EXPECT_THROW(Twelve(""), std::invalid_argument);
}

TEST(ConstructorTest, Invalidinput) {
    EXPECT_THROW(Twelve("1G"), std::invalid_argument);
    EXPECT_THROW(Twelve("X"), std::invalid_argument);
}

TEST(ConstructorTest, Lowercase) {
    Twelve t("a0b");
    EXPECT_EQ(t.tostr(), "A0B");
}

TEST(InitializerListTest, Validnums) {
    Twelve t{'B', 0, 5};
    EXPECT_EQ(t.tostr(), "B05");
}

TEST(InitializerListTest, Onenum) {
    Twelve t{5};
    EXPECT_EQ(t.tostr(), "5");
}

TEST(InitializerListTest, Zero) {
    Twelve t{0};
    EXPECT_EQ(t.tostr(), "0");
}

TEST(InitializerListTest, All0) {
    Twelve t{0, 0, 0};
    EXPECT_EQ(t.tostr(), "0");
}

TEST(InitializerListTest, EmptyList) {
    EXPECT_THROW(Twelve({}), std::invalid_argument);
}

TEST(InitializerListTest, InvalidDig) {
    EXPECT_THROW(Twelve({12}), std::invalid_argument);
    EXPECT_THROW(Twelve({0, 13, 5}), std::invalid_argument);
}

TEST(SizeCharConstructorTest, ValidDig) {
    Twelve t(3, 'A');
    EXPECT_EQ(t.tostr(), "AAA");
}

TEST(SizeCharConstructorTest, Zero) {
    Twelve t(4, '0');
    EXPECT_EQ(t.tostr(), "0");
}

TEST(SizeCharConstructorTest, Size0) {
    EXPECT_THROW(Twelve(0, 5), std::invalid_argument);
}

TEST(SizeCharConstructorTest, InvalidChar) {
    EXPECT_THROW(Twelve(2, 'G'), std::invalid_argument);
    EXPECT_THROW(Twelve(1, 15), std::invalid_argument); 
}

TEST(CopyMoveTest, Constructor) {
    Twelve a("A0B");
    Twelve b(a);
    EXPECT_EQ(a.tostr(), b.tostr());
    EXPECT_TRUE(a.isEqual(b));
}

TEST(CopyMoveTest, Copynums) {
    Twelve a("1A3");
    Twelve b("B0");
    b = a;
    EXPECT_EQ(a.tostr(), b.tostr());
}

TEST(CopyMoveTest, MoveConstructor) {
    Twelve a("A0B");
    Twelve b(std::move(a));
    EXPECT_EQ(b.tostr(), "A0B");
    EXPECT_EQ(a.tostr(), "0"); 
}

TEST(CopyMoveTest, Movenums) {
    Twelve a("1A3");
    Twelve b("B0");
    b = std::move(a);
    EXPECT_EQ(b.tostr(), "1A3");
    EXPECT_EQ(a.tostr(), "0");
}

TEST(CopyMoveTest, Selfcopy) {
    Twelve a("A0B");
    a = a;
    EXPECT_EQ(a.tostr(), "A0B");
}

TEST(ArithmeticTest, AddSimple) {
    Twelve a("1");
    Twelve b("B");
    Twelve c = a.add(b); 
    EXPECT_EQ(c.tostr(), "10");
}

TEST(ArithmeticTest, RecizeAdd) {
    Twelve a("B");
    Twelve b("1");
    Twelve c = a.add(b);
    EXPECT_EQ(c.tostr(), "10");
}

TEST(ArithmeticTest, AddLargerNums) {
    Twelve a("1A3"); 
    Twelve b("B0"); 
    Twelve c = a.add(b);
    EXPECT_EQ(c.tostr(), "293");
}

TEST(ArithmeticTest, Add0) {
    Twelve a("A0B");
    Twelve zero("0");
    Twelve c = a.add(zero);
    EXPECT_EQ(c.tostr(), "A0B");
}

TEST(ArithmeticTest, Minus_Simple) {
    Twelve a("10"); 
    Twelve b("1");  
    Twelve c = a.minus(b);
    EXPECT_EQ(c.tostr(), "B"); 
}

TEST(ArithmeticTest, MinusRecize) {
    Twelve a("100"); 
    Twelve b("1");   
    Twelve c = a.minus(b); 
    EXPECT_EQ(c.tostr(), "BB");
}

TEST(ArithmeticTest, Equals) {
    Twelve a("A0B");
    Twelve b("A0B");
    Twelve c = a.minus(b);
    EXPECT_EQ(c.tostr(), "0");
}

TEST(ArithmeticTest, MinusThrow) {
    Twelve a("5");
    Twelve b("B");
    EXPECT_THROW(a.minus(b), std::underflow_error);
}

TEST(ArithmeticTest, Minus0) {
    Twelve a("A0B");
    Twelve zero("0");
    Twelve c = a.minus(zero);
    EXPECT_EQ(c.tostr(), "A0B");
}

TEST(ComparisonTest, Equal_Same) {
    Twelve a("A0B");
    Twelve b("A0B");
    EXPECT_TRUE(a.isEqual(b));
    EXPECT_FALSE(a.isLess(b));
    EXPECT_FALSE(a.isGreater(b));
}

TEST(ComparisonTest, DiffLength) {
    Twelve a("10"); 
    Twelve b("B");  
    EXPECT_FALSE(a.isEqual(b));
    EXPECT_TRUE(a.isGreater(b));
    EXPECT_FALSE(a.isLess(b));
}

TEST(ComparisonTest, Leading0) {
    Twelve a("00A0B");
    Twelve b("A0B");
    EXPECT_TRUE(a.isEqual(b));
}

TEST(ComparisonTest, ZeroComparisons) {
    Twelve zero("0");
    Twelve a("1");
    EXPECT_TRUE(zero.isLess(a));
    EXPECT_FALSE(zero.isGreater(a));
    EXPECT_FALSE(zero.isEqual(a));
}

TEST(MemoryTest, CreateAndDestroy) {
    Twelve* t = new Twelve("A0B");
    delete t;
    SUCCEED();
}

TEST(EdgeCaseTest, HugeReciseAdd) {
    Twelve a("BBB");
    Twelve b("1");
    Twelve c = a.add(b); 
    EXPECT_EQ(c.tostr(), "1000");
}
