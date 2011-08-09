#ifndef _CG_LINE_HPP_
#define _CG_LINE_HPP_

/*********************************************
 * GATeLib :: Computational Geometry :: Line *
 *********************************************/

/**
 * @brief The class of 2d lines determined by 2 points.
 */

template <typename T> class line2
{
public:

	/**
	 * @brief Gets the direction vector of the line.
	 * @return The direction vector of the line (b - a).
	 * @date 2011-07-28
	 */

	vector2<T> dir() const {
		return b - a;
	}

public:

	/**
	 * @brief Gets the relationship between this and a given vector.
	 * @param foo : The given line.
	 * @return The relationship between two lines.
	 * @date 2011-07-29
	 */

	int rel(const line2 &foo) {

		vector2<T> u = dir(), v = foo.dir();
		T x = u.y * v.x, y = v.y * u.x;

		if (unit<T>::eq(x, y) || unit<T>::iszero(x + y)) {

			vector2<T> w = (a - foo.b).dir();
			T p = u.y * w.x, q = w.y * u.x;

			if (unit<T>::eq(p, q) || unit<T>::iszero(p + q))
				return relation.coincide_entire;
			return relation.parallel_std;
		}
		return relation.intersect_std;
	}

public:

	vector2<T> a;
	vector2<T> b;
};


/**
 * Class lineseg2 is the class of 2D line segments represented by 2
 * vertices.
 */

template <typename T> class lineseg2 : public line2<T>
{
public:

	enum relation
	{
		parallel_std = 1, // Standard parallel.
		intersect_std = 2, // Standard intersect.
		intersect_ncross = 4, // Have one common point but not cross.
		coincide_partly = 8, // Partly coincide.
		coincide_entire = 16, // Entirely coincide.
		on_the_same_line = 32,
		the_same = coincide_entire, // Alternative name.
		parallel_nstd = coincide_partly | coincide_entire, // Nonstandard mask.
		intersect_nstd = intersect_ncross | parallel_nstd, // Nonstandard mask.
		parallel_gener = parallel_std | parallel_nstd, // Generalized mask.
		intersect_gener = intersect_std | intersect_nstd // Generalized mask.
	};

	enum relation_vector2
	{
		on_the_lineseg = 1,
		on_the_line = 2,
		out_of_the_lineseg = 4,
		out_of_the_line = 8
	};

private:

	static bool in_range(const vector2 &p, const lineseg2 &l) {
		return unit<T>::non_decreases(min(l.a.x, l.b.x), p.x, max(l.a.x, l.b.x))
			&& unit<T>::non_decreases(min(l.a.y, l.b.y), p.y, max(l.a.y, l.b.y));
	}

public:

	relation_vector2 relation_between(const vector2 &p) const
	{
		bool a = unit<T>::equals(T(0),
			vector2<T>::cross_product(this->direction(), p - this->a));
		if (a) return out_of_the_line | out_of_the_lineseg;

		if (in_range(p, *this))
			return on_the_lineseg | on_the_line;
		return on_the_line | out_of_the_lineseg;
	}

private:

	static T relation_between_helper(
		const vector2 &p, const lineseg2 &l, int &zeroes, int &ranges
	) {
		T r = vector2<T>::cross_product(l.direction(), p - l.a);
		if (unit<T>::equals(T(0), r)) {
			++zeroes;
			if (in_range(p, l))
				++ranges;
		}
		return r;
	}

public:

	static relation relation_between(const lineseg2 &a, const lineseg2 &b)
	{
		int zeroes = 0, ranges = 0;

		T x = relation_between_helper(a.direction(), b.a - a.a, zeroes, ranges);
		T y = relation_between_helper(a.direction(), b.b - a.a, zeroes, ranges);
		T z = relation_between_helper(b.direction(), a.a - b.a, zeroes, ranges);
		T w = relation_between_helper(b.direction(), a.b - b.a, zeroes, ranges);

		if (zeroes == 0) {
			if (unit<T>::lt(x * y, T(0)) && unit<T>::lt(z * w, T(0)))
				return relation.intersect_std;
			return 0;
		}
		if (zeroes == 1
	}
};


#endif /* _CG_LINE_HPP_ */
