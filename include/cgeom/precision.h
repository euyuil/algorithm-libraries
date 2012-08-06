#ifndef _CGEOM_BASIC_H_
#define _CGEOM_BASIC_H_

const double eps = 1e-8;
const double inf = 1e+8;

/**
 * @brief Gets the sign of the float number.
 * @param a The float number.
 * @return -1 if negative, 1 if positive or 0 if the float is considered
 *         zero.
 * @date 2011-08-11
 */

inline int sgn(double a) {
	return a > eps ? 1 : a < -eps ? -1 : 0;
}

/**
 * @brief Returns whether the first number is less than (lt), greater than
 *        (gt) or equals (eq) the second number.
 * @param a The first number.
 * @param b The second number.
 * @return See brief.
 */

inline bool lt(double a, double b) { return sgn(a - b) < 0; }
inline bool gt(double a, double b) { return sgn(a - b) > 0; }
inline bool eq(double a, double b) { return sgn(a - b) == 0; }
inline bool eq(double a, double b, double c) {
    return eq(a, b) && eq(b, c) && eq(a, c);
}

#endif /* _CGEOM_BASIC_H_ */
