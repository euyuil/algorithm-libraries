#ifndef _CGEOM_LINE_H_
#define _CGEOM_LINE_H_

struct line
{
	point a, b;

	inline line() : a(0.0, 0.0), b(0.0, 0.0) { }
	inline line(const point &_a, const point &_b) : a(_a), b(_b) { }
	inline line(double x1, double y1, double x2, double y2) :
		a(point(x1, y1)), b(point(x2, y2)) { }
		
	/**
	 * @brief Returns reference to a if i is false, otherwise reference to
     *        b. Usually used in loops, for iterating the two points of a
     *        line.
	 * @param i The parameter.
	 * @return See brief.
	 * @date 2011-08-16
	 */

	inline point &operator[](bool i) { return i ? b : a; }

	/**
	 * @brief Makes the ray from the line segment. The point a will become
     *        the end-point of the ray and the point b will be extended to
     *        inf.
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

#endif /* _CGEOM_LINE_H_ */
