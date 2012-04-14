#ifndef _CGEOM_RELLL_H_
#define _CGEOM_RELLL_H_

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

#endif /* _CGEOM_RELLL_H_ */
