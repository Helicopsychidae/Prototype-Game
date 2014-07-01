#ifndef POLYGON_H
#define POLYGON_H

//A point structure, usable for creating polygonal hitboxes.
struct Point{
    int x, y;
};
//A class that stores a set of points (in order) which form a polygon.
class Polygon
{
    public:
        Polygon();
        virtual ~Polygon();
    protected:
    private:
        std::vector<Point> points;
};

#endif // POLYGON_H
