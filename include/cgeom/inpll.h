#ifndef _CGEOM_INPLL_H_
#define _CGEOM_INPLL_H_

/**
 * @date 2011-08-16
 */

inline point inpll(const line &la, const line &lb) {
	double u = cross(la.vec(), point(lb.b - la.b));
	double v = cross(la.vec(), point(lb.a - la.b));
	return (lb.b * v - lb.a * u) / (v - u);
}

#endif /* _CGEOM_INPLL_H_ */
