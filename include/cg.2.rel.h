#ifndef _CG_2_REL_H_
#define _CG_2_REL_H_

#include <cg.2.base.h>

namespace glib {

namespace cg {

/**
 * @brief Calculates the relationship between a point and a line.
 * @param p The point.
 * @param l The line.
 * @return  0 if the point is on the line;
 *         -1 if the point is on the left of vector ab;
 *          1 if the point is on the right of vector ab.
 * @date 2011-08-10
 */

inline int relpl(const point &p, const line &l) {
	return sgn(cross(p - l.a, l.vec())); // 0: on; -1: .|; 1: |..
}

/**
 * @brief Calculates the relationship between a point and a segment.
 * @param p The point.
 * @param s The line segment.
 * @return  0 if the point is between the two end-points of the segment;
 *         -1 if the point is at the end-point a of the segment;
 *          1 if the point is at the end-point b of the segment;
 *         -2 if the point is on the line s and near the end-point a;
 *          2 if the point is on the line s and near the end-point b;
 *         -3 if the point is on the left of vector ab of segment s;
 *          3 if the point is on the right of vector ab of segment s.
 * @date 2011-08-10
 */

inline int relps(const point &p, const line &s) {
	// int rp = sgn(cross(p - s.a, s.vec())); // Rel between p and the line s.
	int rp = relpl(p, s); // Rel between p and the line s.
	if (rp) return rp * 3; // -3: .|; 3: |..
	point psa = s.a - p, psb = s.b - p;
	int r = sgn(dot(psa, psb));
	if (r < 0) return 0; // The point is on the segment between end-points.
	if (r == 0) {
		if (p == s.a) return -1; // The point is at s.a.
		else return 1; // The point is at s.b.
	}
	if (psa.magsqr() <= psb.magsqr())
		return -2; // The point is on the line s, near s.a.
	return 2; // The point is on the line s, near s.b.
}

/**
 * @brief Simpler function to calculate the relationship between a point and a
 *        segment.
 * @param p The point.
 * @param s The line segment.
 * @return  0 if the point is between the two end-points of the segment;
 *          1 if the point is at either end-point of the segment;
 *          2 if the point is on the line s;
 *         -3 if the point is on the left of vector ab of segment s;
 *          3 if the point is on the right of vector ab of segment s.
 * @date 2011-08-22
 */

inline int relpssimp(const point &p, const line &s) {
	// int rp = sgn(cross(p - s.a, s.vec())); // Rel between p and the line s.
	int rp = relpl(p, s); // Rel between p and the line s.
	if (rp) return rp * 3; // -3: .|; 3: |..
	point psa = s.a - p, psb = s.b - p;
	int r = sgn(dot(psa, psb));
	if (r < 0) return 0; // The point is on the segment between end-points.
	if (r == 0) return 1; // The point is at either end-point.
	return 2; // The point is on the line s.
}

/**
 * @brief Calculates the relationship between two lines.
 * @param la One line.
 * @param lb The other line.
 * @return 0 if they are parallel;
 *         1 if they intersect each other;
 *         2 if they are the same line.
 * @date 2011-08-10
 */

inline int relll(const line &la, const line &lb) {
	point u = la.vec(), v = lb.vec();
	double x = u.y * v.x, y = v.y * u.x;
	if (eq(x, y))
		if (!relpl(la.a, lb)) return 2; // The same line.
		else return 0; // They are parallel.
	return 1; // The two lines intersect.
}

/**
 * @brief Calculates the relationship between a line and a segment.
 * @param l The line.
 * @param s The segment.
 * @return 0 if they standard intersect each other.
 *         1 if one of the end-points of the segment is on the line.
 *         2 if the segment is a part of the line.
 *         3 if they have no intersection point.
 * @date 2011-08-10
 */

inline int rells(const line &l, const line &s) {
	int sa = relpl(s.a, l), sb = relpl(s.b, l); int sab = sa * sb;
	if (sab > 0) return 3; // No intersection point.
	if (sab < 0) return 0; // Standard intersection.
	if (sa || sb) return 1; // One of the end-points of the segment intersects the line.
	return 2; // The segment is a part of the line.
}

/**
 * @brief Calculates the original information about the relationship between
 *        two line segments.
 * @param sa One segment.
 * @param sb The other segment.
 * @return The raw information about the relationship between sa and sb. The
 *         return value has 4 bytes and the lowest byte is the info about sa.a,
 *         next is about sa.b and so on. Each byte is the return value of
 *         function relps (relationship between point and segment).
 * @date 2011-08-15
 */

inline int relssraw(const line &sa, const line &sb) {
	int r; signed char (*p)[4] = (signed char (*)[4])(&r);
	(*p)[0] = relps(sa.a, sb); (*p)[1] = relps(sa.b, sb);
	(*p)[2] = relps(sb.a, sa); (*p)[3] = relps(sb.b, sa);
	return r;
}

/**
 * @brief Calculates the relationship between two segments.
 * @param sa One segment.
 * @param sb The other segment.
 * @param raw The raw relationship information between sa and sb. This param
 *        is optional, or you can give the return value of function relssraw.
 * @return 0 if standard intersection;
 *         1~14 if nonstandard intersection, see the comments of the function
                implementation in detail.
 *         15 no intersection.
 * @date 2011-08-11
 */

inline int relssfull(const line &sa, const line &sb, int raw) {
	signed char r[4], s[4] = {0};
	*(int *)r = raw;
	if (r[0] * r[1] == -9 && r[2] * r[3] == -9)
		return 0; // Standard intersection (X).
	++s[abs(r[0])]; ++s[abs(r[1])]; ++s[abs(r[2])]; ++s[abs(r[3])];
	if (s[0] == 1 && s[3] == 3) return 1; // Nonstandard intersection (T).
	if (s[1] == 2 && s[3] == 2) return 2; // Nonstandard intersection (7).
	if (s[1] == 2 && s[2] == 2) return 3; // Nonstandard intersection (--).
	if (s[0] == 2 && s[2] == 2) return 4; // Nonstandard intersection (~=-).
	if (s[0] == 1 && s[1] == 2 && s[2] == 1) return 5; // n-std inters. (~=).
	if (s[0] == 2 && s[2] == 2) return 6; // n-std inters. (Long fully cover short).
	if (s[1] == 4) return 7; // Nonstandard intersection (=), same segment.
	// if (s[0] == 0 && s[1] == 0)
	return 15; // No intersection. Maybe parallel, same-line, or others.
}

/**
 * @date 2011-08-15
 */

inline int relss(const line &sa, const line &sb) {
	return relssfull(sa, sb, relssraw(sa, sb));
}

/**
 * @brief Simpler function to calculate the relationship between two segments.
 * @param sa One segment.
 * @param sb The other segment.
 * @return 0 if they intersect each other standardly;
 *         15 otherwise.
 * @date 2011-08-22
 */

inline int relsssimp(const line &sa, const line &sb) {
	if (relpl(sa.a, sb) ^ relpl(sa.b, sb) == -2 &&
		relpl(sb.a, sa) ^ relpl(sb.b, sa) == -2)
		return 0;
	return 15;
}

/**
 * @brief Calculates the relationship between a point and a polygon.
 * @param p The point.
 * @param b The begin iterator of the polygon.
 * @param e The end iterator of the polygon.
 * @return 0 if the point is in the polygon;
 *         1 if the point is on the edge of the polygon.
 *         2 if the point is out of the polygon.
 * @date 2011-08-15
 */

template <typename I> inline int relppo(const point &p, I b, I e) {
	if (b == e) return 2; // 2: Outside from the polygon.
	I next = b + 1;
	if (next == e) return p == *b ? 1 : 2; // 1: On the edge of the polygon.
	int count = 0; I it = b;
	line r = line(p, point(p.x + 1.0, p.y)).ray();
	for ( ; next != e; ++it, ++next) {
		line s(*it, *next); // For each edge s of the polygon...
		if (relps(p, s) < 2)
			return 1; // 1: The point is on an edge.
		if (sgn(s.vec().y)) { // If edge s isn't horizontal...
			int w = relssraw(s, r);
			int m = relss(s, r, w);
			if (m == 1) { // If one of the end-points is on the ray...
				bool u = ((w & 0xff) == 0); // Whether s.a is on the ray.
				bool v = gt(s.a.y, s.b.y); // Whether s.a is higher than s.b.
				if (!(u ^ v)) ++count; // If the end-points is on the ray and it's higher.
			} else if (m == 0) // Standard intersection.
				++count;
		}
	}
	return (count & 1) ? 0 : 2; // 0: In the polygon!
}

/**
 * @brief TODO: rellpo
 */

} // namespace cg

} // namespace glib

#endif /* _CG_2_REL_H_ */
