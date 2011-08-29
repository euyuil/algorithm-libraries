#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cg.2.base.h>

using namespace std;
using namespace glib::cg;

struct papa {
    double d; int s;
    bool operator<(const papa &p) {
        return d < p.d;
    }
};

line house, property;
vector<papa> points;

inline bool testcase()
{
    double a, b, c;
    scanf("%lf%lf%lf", &a, &b, &c);
    if (!sgn(a) && !sgn(b) && !sgn(c))
        return false;
    house.a.x = a; house.b.x = b;
    house.a.y = house.b.y = c;
    scanf("%lf%lf%lf", &a, &b, &c);
    property.a.x = a; property.b.x = b;
    property.a.y = property.b.y = c;

    size_t n;
    scanf("%lu", &n); points.clear(); points.reserve((n << 1) + 99);
    while (n--)
    {
        scanf("%lf%lf%lf", &a, &b, &c);
        line sl(house.b, point(a, c)), sr(house.a, point(b, c));
        point pl(inpll(sl, property)), pr(inpll(sr, property));
        if (lt(pl.x, property.a.x)) pl.x = property.a.x;
        if (lt(pr.x, property.a.x)) pr.x = property.a.x;
        if (gt(pl.x, property.b.x)) pl.x = property.b.x;
        if (gt(pr.x, property.b.x)) pr.x = property.b.x;
        papa pa; pa.d = pl.x; pa.s = 1; points.push_back(pa);
        pa.d = pr.x; pa.s = -1; points.push_back(pa);
    }
    sort(points.begin(), points.end());

    size_t i; int s = 0;
    for (i = 0; i < points.size(); ++i) {
        s += points[i].s;
    }

    return true;
}

int main(int, char *[]) {
    return EXIT_SUCCESS;
}
