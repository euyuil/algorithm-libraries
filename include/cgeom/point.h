#ifndef _CGEOM_POINT_H_
#define _CGEOM_POINT_H_

struct point
{
	double x, y;

	inline point() : x(0.0), y(0.0) { }
	inline point(double _x, double _y) : x(_x), y(_y) { }

	/**
	 * @brief Returns reference to x if i is false, otherwise reference to
     *        y. Usually used in loops, for iterating the two coordinates
     *        of a point.
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
	 *        the length of two vectors. If you want to know the exact
     *        length of the vector, use mag() instead.
	 * @return See brief.
	 * @date 2011-08-10
	 */

	inline double magsqr() const { return x * x + y * y; }

	/**
	 * @brief Returns the magnitude of the point, or the length of the
     *        vector.
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

#endif /* _CGEOM_POINT_H_ */
