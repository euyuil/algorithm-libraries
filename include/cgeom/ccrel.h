#include <cmath> 
#include <cstdio> 
#include <vector> 
using namespace std;
const double eps = 1e-9;
const double pi = acos(-1.0);
const double inf = 1e18;
struct point_t
{
    double x, y;
    inline point_t(double a, double b) : x(a), y(b) { }
    inline point_t operator-(const point_t &b) const {
        return point_t(x - b.x, y - b.y);
    }
    inline double magsqr() const {
        return x * x + y * y;
    }
    inline double mag() const {
        return sqrt(magsqr());
    }
};
struct circle_t
{
    point_t center;
    double radius;
    inline circle_t(const point_t &c, double r) : center(c), radius(r) { }
};
inline int ccrel(const circle_t &a, const circle_t &b)
{
    double d = (b.center - a.center).mag();
    double p = a.radius + b.radius;
    double s = abs(a.radius - b.radius);
    if (p <= d) return -1; // Outer. 
    if (d <= s) return 1; // Inner. 
    return 0; // Coincide. 
}
inline double cirarea(double radius)
{
    return pi * radius * radius;
}
inline double sectarea(double radius, double theta)
{
    return theta / (2.0 * pi) * cirarea(radius);
}
inline double triarea(double a, double b, double c)
{
    double m = (a + b + c) / 2.0;
    return sqrt(m * (m - a) * (m - b) * (m - c));
}
inline double ccarea(const circle_t &a, const circle_t &b)
{
    //* 
    int rel = ccrel(a, b);
    if (rel < 0) return 0.0f;
    if (rel > 0) {
        if (a.radius < b.radius)
            return cirarea(a.radius);
        return cirarea(b.radius);
    }
    //*/ 
    // Otherwise, two circles must coincide. 
    double d = (b.center - a.center).mag();
    double d2 = d * d;
    double r2 = a.radius * a.radius;
    double R2 = b.radius * b.radius;
    double cosa = (r2 + d2 - R2) / (2.0 * a.radius * d);
    double cosb = (R2 + d2 - r2) / (2.0 * b.radius * d);
    double secta = sectarea(a.radius, 2.0 * acos(cosa));
    double sectb = sectarea(b.radius, 2.0 * acos(cosb));
    double quad = 2.0 * triarea(d, a.radius, b.radius);
    return secta + sectb - quad;
}
inline bool is_available(
    const circle_t &umbrella, const vector<circle_t> &malls)
{
    for (int i = 0; i < malls.size(); ++i)
    {
        int rel = ccrel(umbrella, malls[i]);
        if (rel < 0) return false;
        double coincide = ccarea(umbrella, malls[i]);
        double halfarea = cirarea(malls[i].radius) / 2.0;
        if (coincide >= halfarea)
            continue;
        else
            return false;
    }
    return true;
}
int main()
{
    // freopen("input.txt", "r", stdin); 
    int T, n;
    vector<circle_t> malls;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        malls.clear();
        malls.reserve(20);
        while (n--)
        {
            double x, y, r;
            scanf("%lf %lf %lf", &x, &y, &r);
            malls.push_back(circle_t(point_t(x, y), r));
        }
        double result = inf;
        for (int i = 0; i < malls.size(); ++i)
        {
            double left = 0.0f, right = inf;
            circle_t umbrella(malls[i].center, inf / 2.0);
            while (right - left >= eps)
            {
                if (is_available(umbrella, malls))
                    right = umbrella.radius;
                else
                    left = umbrella.radius;
                umbrella.radius = (right + left) / 2.0;
            }
            if (umbrella.radius < result)
                result = umbrella.radius;
        }
        printf("%.4lf\n", result);
    }
    return 0;
}