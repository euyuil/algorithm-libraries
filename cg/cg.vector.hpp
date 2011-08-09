#ifndef _CG_VECTOR_HPP_
#define _CG_VECTOR_HPP_

/***********************************************
 * GATeLib :: Computational Geometry :: Vector *
 ***********************************************/

#include <cmath>

#include "cg.meta.hpp"

/**
 * @brief A class which represents a point in 2d space.
 */

template <typename T> class vector2
{
public:
	vector2() : x(T(0)), y(T(0)) { }
	vector2(T u, T v) : x(u), y(v) { }

public:

	/**
	 * @brief Gets the const reference i-th coordinate. Notice these two
	 *        functions must be benchmarked.
	 * @date 2011-07-28
	 */

	const T &operator[](size_t i) const throw (std::out_of_range) {
		if (i == 0) return x;
		else if (i == 1) return y;
		throw std::out_of_range("Parameter of " "the function"
			" must be 0 or 1.");
	}

	/**
	 * @brief Gets the i-th coordinate. Notice these two functions must be
	 *        benchmarked.
	 * @date 2011-07-28
	 */

	T &operator[](size_t i) throw (std::out_of_range) {
		return const_cast<T &>(const_cast<const vector2 *>(this)->operator[](i));
	}

public:

	/**
	 * @brief Gets the sum of this and the other vector.
	 * @param v : The other vector.
	 * @return The sum of the two vectors.
	 * @date 2011-08-09
	 */

	vector2 operator+(const vector2 &v) { return vector2(x + v.x, y + v.y); }

	/**
	 * @brief Gets the difference of this and the other vector.
	 * @param v : The other vector.
	 * @return The difference of the two vectors.
	 * @date 2011-08-09
	 */

	vector2 operator-(const vector2 &v) { return vector2(x - v.x, y - v.y); }

	/**
	 * @brief Gets the product of this and a scalar.
	 * @param f : The scalar.
	 * @return The result vector.
	 * @date 2011-08-09
	 */

	vector2 operator*(T f) { return vector2(x * f, y * f); }

	/**
	 * @brief Gets whether vector this equals the other.
	 * @param v : The other vector.
	 * @date 2011-08-09
	 */

	bool operator==(const vector2 &v) {
		return meta<T>::eq(x, v.x) && meta<T>::eq(y, v.y);
	}

	/**
	 * @brief Gets the cross product of this and a given vector.
	 * @param foo : The given vector.
	 * @return The cross product of this and foo.
	 * @date 2011-07-28
	 */

	T cross(const vector2 &foo) const { return x * foo.y - foo.x * y; }

	/**
	 * @brief Gets the dot product of this and a given vector.
	 * @param foo : The given vector.
	 * @return The dot product of this and foo.
	 * @date 2011-07-28
	 */

	T dot(const vector2 &foo) const { return x * foo.x + y * foo.y; }

	/**
	 * @brief Gets the magnitude square of this vector. This value is usually
	 *        used to compare the length of two vectors because it's faster
	 *        than calculating the real length.
	 * @return The magnitude square of this vector.
	 * @date 2011-08-09
	 */

	T magsqr() const { return x * x + y * y; }

	/**
	 * @brief Gets the magnitude of this vector.
	 * @return The magnitude of this vector.
	 * @date 2011-08-09
	 */

	T mag() const { return std::sqrt(magsqr()); }

public:
	T x, y;
};

#endif /* _CG_VECTOR_HPP_ */
