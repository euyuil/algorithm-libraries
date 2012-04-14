#ifndef _CGEOM_ROTPCR_H_
#define _CGEOM_ROTPCR_H_

/**
 * @brief Rotate the point around the given center. The original point will
 *        Not be rotated, instead, the rotated point will be provided as the
 *        return value.
 * @param p The point to be rotated.
 * @param c The center point.
 * @param rad The rotation angle in radius. Negative for clockwise.
 * @return The rotated point.
 * @date 2011-08-16
 */

inline point rotpcr(const point &p, const point &c, double rad) {
	return (p - c).rot(rad) + c;
}

#endif /* _CGEOM_ROTPCR_H_ */
