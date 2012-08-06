#ifndef _CGEOM_TRIANGLE_H_
#define _CGEOM_TRIANGLE_H_

struct triangle
{
    point a, b, c;
    double x, y, z;

    inline triangle() { }

    inline triangle(const point &a, const point &b, const point &c) :
        a(a), b(b), c(c)
    {
        sort((point *)&a, (point *)&a + 3);
        x = (a - b).mag();
        y = (b - c).mag();
        z = (c - a).mag();
        sort((double *)&x, (double *)&x + 3);
    }

    inline bool is_valid() const
    {
        if (x + y <= z || y + z <= x || z + x <= y)
            return false;
        point u = b - a, v = c - b;
        if (u.x * v.y == u.y * v.x)
            return false;
        return true;
    }
};

#endif /* _CGEOM_TRIANGLE_H_ */
