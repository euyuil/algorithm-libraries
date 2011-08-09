/**
 * DONE: gcd, lcm, gcd_euclid, gcd_stein, gcd_euclid_extended,
 *       chinese_remainder_theorem
 * TODO: prime_by_index, prime_by_base, euler_recursive
 */

#ifndef _NUMBER_THEORY_HPP_
#define _NUMBER_THEORY_HPP_

namespace gatelib {

namespace nt {

/**
 * @brief Gets the greatest common divider of a and b, using Euclid algorithm.
 * @param T a - The input integer a.
 * @param T b - The input integer b.
 * @return The greatest common divider of a and b.
 * @date 2011-07-21
 */

template <typename T> T gcd_euclid(T a, T b) {
	T r;
	while (b > 0) {
		r = a % b;
		a = b;
		b = r;
	}
	return a;
}

/**
 * @brief Gets an integer solution (x,y) to a*x+b*y=gcd(a,b).
 *        And it can calculate gcd(a,b) by the way.
 * @param T a - Input value a.
 * @param T b - Input value b.
 * @param T &x - Output value x.
 * @param T &y - Output value y.
 * @return The greatest common divider of a and b.
 * @date 2011-07-21
 */

template <typename T> T gcd_euclid_extended(T a, T b, T &x, T &y) {
	if (b == 0) {
		x = T(1);
		y = T(0);
		return a;
	}
	T d = gcd_euclid_extended(a, b, x, y);
	T u = y;
	T v = x - a / b * y;
	x = u; y = v;
	return d;
}

/**
 * @brief Gets the greatest common divider of a and b, using Stein algorithm.
 * @param T a - The input integer a.
 * @param T b - The input integer b.
 * @return The greatest common divider of a and b.
 * @date 2011-07-21
 */

template <typename T> T gcd_stein(T a, T b) {
	unsigned long r = 0ul;
	while (b > 0) {
		if (!(a & 1) && !(b & 1)) {
			a >>= 1;
			b >>= 1;
			++r;
		} else if (!(a & 1) && (b & 1)) {
			a >>= 1;
		} else if ((a & 1) && !(b & 1)) {
			b >>= 1;
		} else {
			a = (a - b) >> 1;
		}
		if (a < b) {
			T t = a;
			a = b;
			b = t;
		}
	}
	return a << r;
}

/**
 * @brief Gets the greatest common divider of a and b.
 * @param T a - The input integer a.
 * @param T b - The input integer b.
 * @return The greatest common divider of a and b.
 * @date 2011-07-21
 */

template <typename T> T gcd(T a, T b) {
	return gcd_euclid(a, b);
}

/**
 * @brief Gets the least common modifier of a and b, using gcd algorithm.
 * @param T a - The input integer a.
 * @param T b - The input integer b.
 * @return The least common modifier of a and b.
 * @date 2011-07-21
 */

template <typename T> T lcm(T a, T b) {
	return a * b / gcd(a, b);
}

/**
 * @brief Finds the minimum integer x, which satisfies x=a_i(mod r_i),
 *        for each index i.
 * @param const T a[] - The array a_i.
 * @param const T r[] - The array r_i.
 * @param size_t n - The size of array a_i and r_i. These two arrays
 *        must be the same size.
 * @return The minimum integer x, which satisfies x=a_i(mod r_i), for
 *         each index i.
 * @date 2011-07-22
 */

template <typename T>
T chinese_remainder_theorem(const T a[], const T r[], size_t n) {
	T s = 0;
	for (size_t i = 0; i < n; ++i)
		s += r[i];
	T m, x, y, t = 0;
	for (size_t i = 0; i < n; ++i) {
		m = s / r[i];
		gcd_euclid_extended(m, r[i], x, y);
		t += a[i] * x * m;
	}
	return t % s;
}

} /* namespace nt */

} /* namespace gatelib */

#endif /* _NUMBER_THEORY_HPP_ */
