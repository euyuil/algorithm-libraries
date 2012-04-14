#ifndef _CGEOM_RELLS_H_
#define _CGEOM_RELLS_H_

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

#endif /* _CGEOM_RELLS_H_ */
