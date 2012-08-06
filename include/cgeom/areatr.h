#ifndef _CGEOM_AREATR_H_
#define _CGEOM_AREATR_H_

/**
 * @date 2011-08-16
 */

inline double areatr(const point &a, const point &b, const point &c) {
	return 0.5 * cross(b - a, c - a);
}

#endif /* _CGEOM_AREATR_H_ */
