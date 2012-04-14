#ifndef _NUMBTH_CHNREM_H_
#define _NUMBTH_CHNREM_H_

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

#endif /* _NUMBTH_CHNREM_H_ */
