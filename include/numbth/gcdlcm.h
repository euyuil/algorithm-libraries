#ifndef _NUMBTH_GCDLCM_H_
#define _NUMBTH_GCDLCM_H_

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

#endif /* _NUMBTH_GCDLCM_H_ */
