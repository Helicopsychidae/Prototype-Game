#ifndef GEOM_H
#define GEOM_H

//Defines a point in 2D space.
struct Point {int x, y;};

//Defines a circle.
struct Circle {
    Point center;
    int r;
};
#endif // GEOM_H
