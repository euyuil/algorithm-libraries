#ifndef _CG_2_BASE_H_
#define _CG_2_BASE_H_

#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

namespace glib {

namespace cg {

const double eps = 1e-8;
const double inf = 1e+8;

/**
 * @brief Gets the sign of the float number.
 * @param a The float number.
 * @return -1 if negative, 1 if positive or 0 if the float is considered zero.
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

struct point
{
	double x, y;

	inline point() : x(0.0), y(0.0) { }
	inline point(double _x, double _y) : x(_x), y(_y) { }

	/**
	 * @brief Returns reference to x if i is false, otherwise reference to y.
	 *        Usually used in loops, for iterating the two coordinates of a
	 *        point.
	 * @param i The parameter.
	 * @return See brief.
	 * @date 2011-08-16
	 */

	inline double &operator[](bool i) { return i ? y : x; }

	inline point operator+(const point &p) const { return point(x + p.x, y + p.y); }
	inline point operator-(const point &p) const { return point(x - p.x, y - p.y); }
	inline point operator*(double k) const { return point(x * k, y * k); }
	inline point operator/(double k) const { return point(x / k, y / k); }

	inline bool operator==(const point &p) const {
		return !sgn(x - p.x) && !sgn(y - p.y);
	}

	/**
	 * @brief Returns the square of magnitude of the point, or the square of
	 *        the length of the vector. This is frequently used to compare
	 *        the length of two vectors. If you want to know the exact length
	 *        of the vector, use mag() instead.
	 * @return See brief.
	 * @date 2011-08-10
	 */

	inline double magsqr() const { return x * x + y * y; }

	/**
	 * @brief Returns the magnitude of the point, or the length of the vector.
	 * @return See brief.
	 * @date 2011-08-10
	 */

	inline double mag() const { return sqrt(magsqr()); }

	/**
	 * @brief Rotate the point around the center (0, 0).
	 * @param rad The angle in radius, negative for clockwise.
	 * @return The rotated angle.
	 * @date 2011-08-16
	 */

	inline point rot(double rad) const {
		return point(x * cos(rad) - y * sin(rad),
			y * cos(rad) + x * sin(rad));
	}
};

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

struct line
{
	point a, b;

	inline line() { }
	inline line(const point &_a, const point &_b) : a(_a), b(_b) { }
	inline line(double x1, double y1, double x2, double y2) :
		a(point(x1, y1)), b(point(x2, y2)) { }
		
	/**
	 * @brief Returns reference to a if i is false, otherwise reference to b.
	 *        Usually used in loops, for iterating the two points of a line.
	 * @param i The parameter.
	 * @return See brief.
	 * @date 2011-08-16
	 */

	inline point &operator[](bool i) { return i ? b : a; }

	/**
	 * @brief Makes the ray from the line segment. The point a will become the
	 *        end-point of the ray and the point b will be extended to inf.
	 * @return The ray.
	 * @date 2011-08-15
	 */

	inline line ray() const {
		point t = vec();
		return line(a, a + t * (inf / max(t.x, t.y)));
	}

	/**
	 * @brief Makes the direction vector of the line segment.
	 * @return The direction vector of the line segment, i.e. (b - a).
	 * @date 2011-08-10
	 */

	inline point vec() const { return b - a; }

	/**
	 * @brief Calculates the length of the line segment.
	 * @return The length of the line segment, i.e. vec().mag().
	 * @date 2011-08-10
	 */

	inline double len() const { return vec().mag(); }
};

} // namespace cg

} // namespace glib

#endif /* _CG_2_BASE_H_ */
