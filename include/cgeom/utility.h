#ifndef _CGEOM_UTILITY_H_
#define _CGEOM_UTILITY_H_

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

/**
 * @brief For Each Segment of POlygon.
 * @param s Output segment.
 * @param i Iterator of the first end-point of the segment.
 * @param b The begin iterator of the polygon.
 * @param e The end iterator of the polygon.
 * @return True if succeeded.
 */

template <typename I> bool fespo(line &s, I &i, I b, I e)
{
	if (i == e) return false;
	I j = i; ++j;
	if (j == e) s = line(*i, *b);
	else s = line(*i, *j);
	i = j; return true;
}

#endif /* _CGEOM_UTILITY_H_ */
