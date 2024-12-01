#include <gtest/gtest.h>

#include <Segment3D.hpp>
#include <Vector3D.hpp>

TEST(Segments, Intersection) {

    // Случаи с "отрезком"-точкой

    Segment3D s1(0, 0, 0, 0, 0, 0);
    Segment3D s2(-0.5, -0.5, -0.5, 0.5, 0.5, 0.5);
    Vector3D intersectionPoint;
    ASSERT_TRUE(intersect(intersectionPoint, s1, s2));
    ASSERT_EQ(intersectionPoint, s1.getStart());
    ASSERT_EQ(intersectionPoint, s1.getEnd());

    s1.setStart(-0.25, -0.25, -0.25);
    s1.setEnd(-0.25, -0.25, -0.25);
    ASSERT_TRUE(intersect(intersectionPoint, s1, s2));
    ASSERT_EQ(intersectionPoint, s1.getStart());
    ASSERT_EQ(intersectionPoint, s1.getEnd());

    s1.setStart(0.25, 0.25, 0.25);
    s1.setEnd(0.25, 0.25, 0.25);
    ASSERT_TRUE(intersect(intersectionPoint, s1, s2));
    ASSERT_EQ(intersectionPoint, s1.getStart());
    ASSERT_EQ(intersectionPoint, s1.getEnd());

    s1.setStart(1, 1, 1);
    s1.setEnd(1, 1, 1);
    ASSERT_FALSE(intersect(intersectionPoint, s1, s2));
    ASSERT_FALSE(intersect(intersectionPoint, s2, s1));

    s2.setStart(1, 1, 1);
    s2.setEnd(1, 1, 1);
    ASSERT_TRUE(intersect(intersectionPoint, s1, s2));
    ASSERT_EQ(intersectionPoint, s1.getStart());
    ASSERT_EQ(intersectionPoint, s1.getEnd());
    ASSERT_EQ(intersectionPoint, s2.getStart());
    ASSERT_EQ(intersectionPoint, s2.getEnd());

    s1.setStart(3, 3, 3);
    s1.setEnd(3, 3, 3);
    ASSERT_FALSE(intersect(intersectionPoint, s1, s2));
    ASSERT_FALSE(intersect(intersectionPoint, s2, s1));

    // Случаи с отрезками на совпадающих и параллельных прямых

    s1.setStart(-1, -1, -1);
    s1.setEnd(1, 1, 1);
    s2.setStart(-10, -10, -10);
    s2.setEnd(10, 10, 10);
    ASSERT_FALSE(intersect(intersectionPoint, s1, s2));

    s2.setStart(-10, -10, -13);
    s2.setEnd(10, 10, 7);
    ASSERT_FALSE(intersect(intersectionPoint, s1, s2));

    // Случаи пересечения отрезков в одной крайней точке при совпадении прямых

    //Совпадают начала
    s1.setStart(-1, -1, -1);
    s1.setEnd(-2, -2, -2);
    s2.setStart(-1, -1, -1);
    s2.setEnd(0, 0, 0);
    ASSERT_TRUE(intersect(intersectionPoint, s1, s2));
    ASSERT_EQ(intersectionPoint, s1.getStart());
    ASSERT_EQ(intersectionPoint, s2.getStart());

    s2.setEnd(-3, -3, -3);
    ASSERT_FALSE(intersect(intersectionPoint, s1, s2));
    ASSERT_FALSE(intersect(intersectionPoint, s2, s1));

    // Совпадают начало и конец
    s1.setStart(0, 0, 0);
    s1.setEnd(1, 1, 1);
    s2.setStart(-1, -1, -1);
    s2.setEnd(0, 0, 0);    
    ASSERT_TRUE(intersect(intersectionPoint, s1, s2));
    ASSERT_EQ(intersectionPoint, s1.getStart());
    ASSERT_EQ(intersectionPoint, s2.getEnd());

    s2.setStart(2, 2, 2);
    ASSERT_FALSE(intersect(intersectionPoint, s1, s2));
    ASSERT_FALSE(intersect(intersectionPoint, s2, s1));

    s2.setStart(1, 1, 1);
    s2.setEnd(2, 2, 2);
    ASSERT_TRUE(intersect(intersectionPoint, s1, s2));
    ASSERT_EQ(intersectionPoint, s1.getEnd());
    ASSERT_EQ(intersectionPoint, s2.getStart());

    s2.setEnd(-1, -1, -1);
    ASSERT_FALSE(intersect(intersectionPoint, s1, s2));
    ASSERT_FALSE(intersect(intersectionPoint, s2, s1));

    // Совпадают концы
    s1.setStart(-2, -2, -2);
    s1.setEnd(-1, -1, -1);
    ASSERT_TRUE(intersect(intersectionPoint, s1, s2));
    ASSERT_EQ(intersectionPoint, s1.getEnd());
    ASSERT_EQ(intersectionPoint, s2.getEnd());

    s1.setStart(2, 2, 2);
    ASSERT_FALSE(intersect(intersectionPoint, s1, s2));
    ASSERT_FALSE(intersect(intersectionPoint, s2, s1));

    //Случаи совпадения отрезков

    s1.setEnd(0, 0, 0);
    ASSERT_FALSE(intersect(intersectionPoint, s1, s2));
    ASSERT_FALSE(intersect(intersectionPoint, s2, s1));

    s1.setStart(1, 1, 1);
    s2.setStart(0, 0, 0);
    s2.setEnd(1, 1, 1);
    ASSERT_FALSE(intersect(intersectionPoint, s1, s2));
    ASSERT_FALSE(intersect(intersectionPoint, s2, s1));

    s2.setStart(0.5, 0.5, 0.5);
    s2.setEnd(1.5, 1.5, 1.5);
    ASSERT_FALSE(intersect(intersectionPoint, s1, s2));
    ASSERT_FALSE(intersect(intersectionPoint, s2, s1));

    // Случаи непересечения отрезков

    s2.setStart(3, 3, 3);
    s2.setEnd(4, 4, 4);
    ASSERT_FALSE(intersect(intersectionPoint, s1, s2));
    ASSERT_FALSE(intersect(intersectionPoint, s2, s1));

    s1.setStart(1, 1, 1);
    s1.setEnd(3, 3, 3);
    s2.setStart(1, 2, 3);
    s2.setEnd(-1, 1, -2);
    ASSERT_FALSE(intersect(intersectionPoint, s1, s2));
    ASSERT_FALSE(intersect(intersectionPoint, s2, s1));

    s1.setStart(1, 3, 0);
    s1.setEnd(2, 5, 0);
    s2.setStart(2, 4, 0);
    s2.setEnd(3, 6, 0);
    ASSERT_FALSE(intersect(intersectionPoint, s1, s2));
    ASSERT_FALSE(intersect(intersectionPoint, s2, s1));

    s1.setStart(1, 3, 0);
    s1.setEnd(3, 3, 0);
    s2.setStart(2, 1, 3);
    s2.setEnd(2, 4, 3);
    ASSERT_FALSE(intersect(intersectionPoint, s1, s2));
    ASSERT_FALSE(intersect(intersectionPoint, s2, s1));

    s1.setStart(1, 0, 0);
    s1.setEnd(2, 0, 0);
    s2.setStart(0, 1, 0);
    s2.setEnd(0, 2, 0);
    ASSERT_FALSE(intersect(intersectionPoint, s1, s2));
    ASSERT_FALSE(intersect(intersectionPoint, s2, s1));

    // Случаи пересечения отрезков

    s1.setStart(0, 0, 0);
    s1.setEnd(2, 0, 0);
    s2.setStart(0, 0, 0);
    s2.setEnd(0, 2, 0);
    ASSERT_TRUE(intersect(intersectionPoint, s1, s2));
    ASSERT_EQ(intersectionPoint, s1.getStart());
    ASSERT_EQ(intersectionPoint, s2.getStart());

    s1.setStart(3, 1, 0);
    s1.setEnd(5, 0, 8);
    s2.setStart(3, 1, 0);
    s2.setEnd(0, 3, -4);
    ASSERT_TRUE(intersect(intersectionPoint, s1, s2));
    ASSERT_EQ(intersectionPoint, s1.getStart());
    ASSERT_EQ(intersectionPoint, s2.getStart());

    s1.setStart(-0.5, -1, -0.5);
    s1.setEnd(0.5, 1, 0.5);
    s2.setStart(-0.5, -0.5, -0.5);
    s2.setEnd(0.5, 0.5, 0.5);
    ASSERT_TRUE(intersect(intersectionPoint, s1, s2));
    ASSERT_EQ(intersectionPoint, Vector3D(0, 0, 0));

    s1.setStart(4, 2, 3);
    s1.setEnd(2, 4, 3);
    s2.setStart(2, 2, 3);
    s2.setEnd(4, 4, 3);
    ASSERT_TRUE(intersect(intersectionPoint, s1, s2));
    ASSERT_EQ(intersectionPoint, Vector3D(3, 3, 3));

    s1.setStart(4, 2, 2);
    s1.setEnd(2, 4, 4);
    s2.setStart(2, 2, 4);
    s2.setEnd(4, 4, 2);
    ASSERT_TRUE(intersect(intersectionPoint, s1, s2));
    ASSERT_EQ(intersectionPoint, Vector3D(3, 3, 3));

    s1.setStart(0, 0, 4);
    s1.setEnd(0, 0, 6);
    s2.setStart(1, -1, 5);
    s2.setEnd(-1, 1, 5);
    ASSERT_TRUE(intersect(intersectionPoint, s1, s2));
    ASSERT_EQ(intersectionPoint, Vector3D(0, 0, 5));
}

