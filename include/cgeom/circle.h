#ifndef _CG_2_CIRCLE_H_
#define _CG_2_CIRCLE_H_

#include <vector>

using namespace std;

#include <cg.2.base.h>

namespace glib {

namespace cg {

struct circle
{
	point c;
	double r;

	inline circle(const point &c, double r) : c(c), r(r) { }
};

inline int doucirrelpos(const circle &ca, const circle &cb)
{
	if (ca.c == cb.c) return 0; // Same center.
	double d = (cb.c - ca.c).mag();
	if (d < cb.r - ca.r) return 1; // ca in cb.
	if (d < ca.r - cb.r) return -1; // cb in ca.
	if (d == cb.r - ca.r) return 2; // ca in and touches cb.
	if (d == ca.r - cb.r) return -2; // cb in and touches ca.
	if (d == ca.r + cb.r) return 4; // ca out of and touches cb.
	if (d > ca.r + cb.r) return 5; // ca out of cb.
	return 3; // ca intersects cb.
}

inline int doucircaltan(const circle &ca, const circle &cb, vector<line> &tls)
{
	tls.clear(); rel = doucirrelpos(ca, cb);
	if (rel < 3 || rel > 5) return 0;
	double d = (ca.c - cb.c).mag(); // d = |O1O2|
	double d2 = d * d; // d2 = d^2
	double dr = ca.r - cb.r; // diff of r1 and r2: r1 - r2.
	double sr = ca.r + cb.r; // sum of r1 and r2: r1 + r2.
	double h = sqrt(d2 - dr * dr);
	double k = sqrt(d2 - sd * sd);
	double dx = ca.c.x - cb.c.x;
	double dy = ca.c.y - cb.c.y;
	switch (rel)
	{
	case 3: // Two outer tangent lines.
		return 2;
	case 4: // Two outer and one inner tangent lines.
		return 3;
	case 5: // Two outer and two inner tangent lines.
		return 4;
	}
	return 0;
}

}

}

#endif /* _CG_2_CIRCLE_H_ */
