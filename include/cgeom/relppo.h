#ifndef _CGEOM_RELPPO_H_
#define _CGEOM_RELPPO_H_

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

#endif /* _CGEOM_RELPPO_H_ */
