#ifndef _CG_2_CALC_H_
#define _CG_2_CALC_H_

#include <cg.2.base.h>

namespace glib {

namespace cg {

// Calculating.
// inp: intersection point; area: area; dis: distance, rot: rotate; tri: triangle.

/**
 * @date 2011-08-16
 */

inline point inpll(const line &la, const line &lb) {
	double u = cross(la.vec(), point(lb.b - la.b));
	double v = cross(la.vec(), point(lb.a - la.b));
	return (lb.b * v - lb.a * u) / (v - u);
}

/**
 * @date 2011-08-16
 */

inline double areatri(const point &a, const point &b, const point &c) {
	return 0.5 * cross(b - a, c - a);
}

/**
 * @date 2011-08-15
 */

template <typename I> inline double areapo(I b, I e) {
	if (b == e) return 0.0;
	I next = b + 1;
	if (next == e) return 0.0;
	double area = 0.0;
	I it = b;
	for ( ; next != e; ++it, ++next)
		area += it->cross(*next);
	area += it->cross(*b);
	return area / 2.0;
}

/**
 * @date 2011-08-16
 */

inline double dispp(const point &a, const point &b) {
    return (b - a).mag();
}

/**
 * @date 2011-08-16
 */

inline double displ(const point &p, const line &l) {
    return abs(cross(l.vec(), p - l.a)) / l.len();
}

/**
 * @brief Rotate the point around the given center. The original point will
 *        Not be rotated, instead, the rotated point will be provided as the
 *        return value.
 * @param p The point to be rotated.
 * @param c The center point.
 * @param rad The rotation angle in radius. Negative for clockwise.
 * @return The rotated point.
 * @date 2011-08-16
 */

inline point rotpcr(const point &p, const point &c, double rad) {
	return (p - c).rot(rad) + c;
}

} // namespace cg

} // namespace glib

#endif /* _CG_2_CALC_H_ */
