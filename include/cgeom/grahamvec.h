#include <cmath> 
#include <vector> 
#include <cstdio> 
#include <algorithm> 
using namespace std;
///////////// 
// Numbers // 
///////////// 
const double eps = 1e-6;
inline int sgn(double a)
{
    return a > eps ? 1 : a < -eps ? -1 : 0;
}
inline bool eq(double a, double b)
{
    return !sgn(a - b);
}
inline bool lt(double a, double b)
{
    return sgn(a - b) < 0;
}
inline bool gt(double a, double b)
{
    return sgn(a - b) > 0;
}
//////////// 
// Points // 
//////////// 
struct point
{
    double x, y;
    inline point() : x(0.0), y(0.0) { }
    inline point(double x, double y) : x(x), y(y) { }
    inline point operator+(const point &b) const {
        return point(x + b.x, y + b.y);
    }
    inline point operator-(const point &b) const {
        return point(x - b.x, y - b.y);
    }
    inline point operator*(double k) const {
        return point(x * k, y * k);
    }
    inline point operator/(double k) const {
        return point(x / k, y / k);
    }
    inline point &operator+=(const point &b) {
        x += b.x; y += b.y; return *this;
    }
    inline point &operator-=(const point &b) {
        x -= b.x; y -= b.y; return *this;
    }
    inline point &operator*=(double k) {
        x *= k; y *= k; return *this;
    }
    inline point &operator/=(double k) {
        x /= k; y /= k; return *this;
    }
    inline bool operator==(const point &b) const {
        return eq(x, b.x) && eq(y, b.y);
    }
    inline double magsqr() const {
        return x * x + y * y;
    }
};
inline double cross(const point &a, const point &b) {
    return a.x * b.y - a.y * b.x;
}
inline double dot(const point &a, const point &b) {
    return a.x * b.x + a.y * b.y;
}
inline double ccw(const point &p, const point &a, const point &b) {
    return cross(a - p, b - p);
}
/////////// 
// Lines // 
/////////// 
struct line
{
    point a, b;
    inline line(const point &a, const point &b) : a(a), b(b) { }
    inline point vec() const {
        return b - a;
    }
};
inline point inpll(const line &la, const line &lb)
{
    double u = cross(la.vec(), point(lb.b - la.b));
    double v = cross(la.vec(), point(lb.a - la.b));
    return (lb.b * v - lb.a * u) / (v - u);
}
inline int relpl(const point &p, const line &l)
{
    return sgn(cross(p - l.a, l.vec())); // 0: on; -1: .|; 1: |.. 
}
inline int relps(const point &p, const line &s)
{
    int rp = relpl(p, s);
    if (rp) return rp * 3; // -3: .|; 3: |.. 
    point psa = s.a - p, psb = s.b - p;
    int r = sgn(dot(psa, psb));
    if (r < 0) return 0; // The point is on the segment between end-points. 
    if (r == 0) return 1; // The point is at either end-point. 
    return 2; // The point is on the line s. 
}
inline point plupl(const point &p, const line &l)
{
    point u = l.vec(), v = p - l.a;
    return l.a + u * dot(u, v) / u.magsqr();
}
////////////// 
// Polygons // 
////////////// 
typedef vector<point> polygon;
inline point tricore(const point &a, const point &b, const point &c)
{
    return point((a.x + b.x + c.x) / 3.0, (a.y + b.y + c.y) / 3.0);
}
inline point polycore(const polygon &poly)
{
    point core(0.0, 0.0);
    double mass = 0.0;
    for (int i = 2; i < poly.size(); ++i)
    {
        point c = tricore(poly[0], poly[i - 1], poly[i]);
        double m = ccw(poly[0], poly[i - 1], poly[i]);
        core += (c *= m);
        mass += m;
    }
    return core /= mass;
}
struct graham_scan
{
    vector<bool> instack;
    vector<int> indices;
    inline static bool lessthan(const point &a, const point &b)
    {
        if (eq(a.y, b.y))
            return lt(a.x, b.x);
        return lt(a.y, b.y);
    }
    inline void scan(const polygon &po, int begin, int end, int delta)
    {
        for (int i = begin; i != end; i += delta)
        {
            if (instack[i]) continue;
            while (indices.size() >= 2)
            {
                const point &a = po[indices.back()];
                const point &p = po[indices[indices.size() - 2]];
                if (sgn(ccw(p, a, po[i])) <= 0) {
                    instack[indices.back()] = false; indices.pop_back();
                } else break;
            }
            instack[i] = true; indices.push_back(i);
        }
    }
    inline void solve_indices(polygon &poly) // Incoming poly will be changed. 
    {
        instack.clear(); instack.resize(poly.size(), false);
        indices.clear(); indices.reserve(poly.size() + 1);
        sort(poly.begin(), poly.end(), lessthan);
        poly.resize(unique(poly.begin(), poly.end()) - poly.begin());
        indices.push_back(0);
        scan(poly, 1, poly.size(), 1);
        scan(poly, poly.size() - 1, -1, -1);
        indices.pop_back();
    }
    inline polygon polygon_from_indices(const polygon &original)
    {
        polygon result; result.reserve(indices.size());
        for (int i = 0; i < indices.size(); ++i)
            result.push_back(original[indices[i]]);
        return result;
    }
};
graham_scan graham;
inline int stable_side_count(const polygon &original)
{
    polygon sorted = original;
    graham.solve_indices(sorted);
    polygon convex = graham.polygon_from_indices(sorted);
    int result = 0;
    point core = polycore(original);
    for (int i = 0; i < convex.size(); ++i)
    {
        int j = (i + 1) % convex.size();
        line edge(convex[i], convex[j]);
        point plumb = plupl(core, edge);
        if (relps(plumb, edge) == 0)
            ++result;
    }
    return result;
}
int main()
{
    // freopen("input.txt", "r", stdin); 
    int T, n;
    scanf("%d", &T);
    while (T--)
    {
        polygon poly;
        scanf("%d", &n);
        poly.reserve(n);
        while (n--)
        {
            double x, y;
            scanf("%lf %lf", &x, &y);
            poly.push_back(point(x, y));
        }
        printf("%d\n", stable_side_count(poly));
    }
    return 0;
}