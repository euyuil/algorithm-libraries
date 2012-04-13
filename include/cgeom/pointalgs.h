#ifndef _CGEOM_POINTALGS_H_
#define _CGEOM_POINTALGS_H_

/**
 * @brief Returns the cross product of two vectors.
 * @param a One vector.
 * @param b The other vector.
 * @return The cross product of a and b.
 * @date 2011-08-09
 */

inline double cross(const point &a, const point &b) {
	return a.x * b.y - b.x * a.y;
}

/**
 * @brief Returns the dot product of two vectors.
 * @param a One vector.
 * @param b The other vector.
 * @return The dot product of a and b.
 * @date 2011-08-09
 */

inline double dot(const point &a, const point &b) {
	return a.x * b.x + a.y * b.y;
}

#endif /* _CGEOM_POINTALGS_H_ */
