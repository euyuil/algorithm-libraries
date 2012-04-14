#ifndef _CGEOM_AREAPO_H_
#define _CGEOM_AREAPO_H_

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

#endif /* _CGEOM_AREAPO_H_ */
