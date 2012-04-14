#ifndef _CGEOM_RELPL_H_
#define _CGEOM_RELPL_H_

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

#endif /* _CGEOM_RELPL_H_ */
