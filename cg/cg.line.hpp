#ifndef _CG_LINE_HPP_
#define _CG_LINE_HPP_

/*****************************************************************
 * GATeLib :: Computational Geometry :: Line, Line Segment & Ray *
 *****************************************************************/

#include "cg.meta.hpp"
#include "cg.vector.hpp"

namespace gatelib {

namespace cg {

template <typename T> class line2;
template <typename T> class lineseg2;
template <typename T> class ray2;


/**
 * @brief The class of 2d lines determined by 2 points.
 */

template <typename T> class line2
{
public:
	line2(T x1, T y1, T x2, T y2) : a(x1, y1), b(x2, y2) { }
	line2(const vector2 &u, const vector2 &v) : a(u), b(v) { }
	line2(const lineseg2 &s) : a(s.a), b(s.b) { }
	line2(const ray2 &r) : a(r.a), b(r) { }

public:

	/**
	 * @brief Gets the direction vector of the line.
	 * @return The direction vector of the line (b - a).
	 * @date 2011-07-28
	 */

	vector2<T> dir() const { return b - a; }

public:

	/**
	 * @brief Gets the relationship between this and a given line.
	 * @param foo : The given line.
	 * @return The relationship between two lines. 0 means they are parallel;
	 *         1 means one intersects the other; 2 means they are the same
	 *         line.
	 * @date 2011-08-09
	 */

	int rel(const line2 &foo) {

		vector2<T> u = dir(), v = foo.dir();
		T x = u.y * v.x, y = v.y * u.x;

		if (unit<T>::eq(x, y) || unit<T>::iszero(x + y)) {

			vector2<T> w = (a - foo.b).dir();
			T p = u.y * w.x, q = w.y * u.x;

			if (unit<T>::eq(p, q) || unit<T>::iszero(p + q))
				return 2;
			return 0;
		}
		return 1;
	}

public:
	vector2<T> a, b;
};


/**
 * @brief The class of 2d line segments represented by 2 vertexes.
 */

template <typename T> class lineseg2 : class line2<T>
{
public:
	lineseg2(T x1, T y1, T x2, T y2) : a(x1, y1), b(x2, y2) { }
	lineseg2(const vector2 &u, const vector2 &v) : a(u), b(v) { }

private:

	static bool in_range(const vector2<T> &p, const lineseg2 &l) {
		vector2<T> pp1(l.a - p), pp2(l.b - p);
		return meta<T>::sgn(pp1.dot(pp2)) <= 0;
		/* return meta<T>::isndesc(min(l.a.x, l.b.x), p.x, max(l.a.x, l.b.x))
			&& meta<T>::isndesc(min(l.a.y, l.b.y), p.y, max(l.a.y, l.b.y)); */
	}

public:

	/**
	 * @brief Get the relationship between this lineseg2 and a point.
	 * @param p : The point.
	 * @return The relationship between this lineseg2 and the point. 0 means
	 *         the point is not on the lineseg2; 1 means the point is on the
	 *         lineseg2.
	 * @date 2011-08-09
	 */

	int rel(const vector2 &p) const
	{
		bool a = meta<T>::sgn(this->dir().cross(p - this->a));
		if (a) return 0; // Point is not even on this line rather than segment.

		if (in_range(p, *this))
			return 1;
		return 0; // On the line but not the segment.
	}

private:

	static T rel_helper(
		const vector2 &p, const lineseg2 &l, char &zs, char &rs
	) {
		T r = l.dir().cross(p - l.a);
		zs <<= 1; rs <<= 1;
		if (meta<T>::iszero(r)) { // r == 0 means p is on line l.
			zs |= 1;
			if (in_range(p, l)) rs |= 1; // Means p is on line segment l.
		}
		return r;
	}

public:

	/**
	 * @brief Get the relationship between this lineseg2 and the other.
	 * @param s : The other line segment.
	 * @return The relationship between this lineseg2 and the other. 0 means
	 *         they have no common point; 1 means one lineseg2 goes across the
	 *         other, ie. standard intersection; 2 and above mean non-standard
	 *         intersection.
	 * @date 2011-08-09
	 */

	int rel(const lineseg2 &s)
	{
		char zs = 0, rs = 0;

		T x = rel_helper(  dir(), s.a -   a, state);
		T y = rel_helper(  dir(), s.b -   a, state);
		T z = rel_helper(s.dir(),   a - s.a, state);
		T w = rel_helper(s.dir(),   s - s.a, state);

		if (zs == 0) { // No point is on either line.
			if (meta<T>::sgn(x * y) < 0 && meta<T>::sgn(z * w) < 0)
				return 1;
			return 0;
		}
		if (zs & rs)
			return 2; // Non-standard intersection. May be more complex.
		return 0; // One or two points is on a line but not segment.
	}

public:
	vector2<T> a, b;
};


/**
 * @brief The class of 2d rays represented by 2 points.
 */

template <typename T> class ray2 : class lineseg2<T>
{
public:
	ray2(T x1, T y1, T x2, T y2) : a(x1, y1), b(x2, y2) { }
	ray2(const vector2 &u, const vector2 &v) : a(u), b(v) { }

public:
	void make() {
		vector2<T> d = dir() * abs(meta<T>::inf / max(d.x, d.y));
		b = a + d;
	}

public:
	vector2<T> a, b;
};

} // namespace cg

} // namespace gatelib

#endif /* _CG_LINE_HPP_ */
