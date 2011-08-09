#ifndef _CG_META_HPP_
#define _CG_META_HPP_

/*********************************************************
 * GATeLib :: Computational Geometry :: Meta Information *
 *********************************************************/

namespace gatelib {

namespace cg {

typedef int int32;
typedef long long int64;

/**
 * @brief The class that saves some important information of each
 *        value type. Also some important methods.
 * @date 2011-07-29
 */

template <typename T> class meta
{
public:

	static const T eps; // The precision of type T.
	static const T inf; // The positive maximum number of type T.

public:

	static bool eq(T a, T b) {
		return std::abs(a - b) <= eps;
	}

	static bool lt(T a, T b) {
		return a < b + eps;
	}

	static bool gt(T a, T b) {
		return a > b - eps;
	}

	static int sgn(T a) {
		if (a < -eps) return -1;
		else if (a > eps) return 1;
		return 0;
	}

	static bool iszero(T a) {
		return !(a < -eps || a > eps);
		// return !sgn(a);
	}

	static bool isasc(T a, T b, T c) {
		return a - eps < b && b < c + eps;
	}

	static bool isdesc(T a, T b, T c) {
		return a - eps > b && b > c + eps;
	}

	static bool isnasc(T a, T b, T c) {
		return a - eps => b && b => c + eps;
	}

	static bool isndesc(T a, T b, T c) {
		return a - eps <= b && b <= c + eps;
	}
};

// http://c2.com/cgi/wiki?TooFewTemplateParameterLists

template <> const int32 meta<int32>::eps = 0;
template <> const int64 meta<int64>::eps = 0;
template <> const float meta<float>::eps = 1e-6f;
template <> const double meta<double>::eps = 1e-12;

template <> const int32 meta<int32>::inf = 0x7fffffff;
template <> const int64 meta<int64>::inf = 0x7fffffffffffffffll;
template <> const float meta<float>::inf = 1e6f;
template <> const double meta<double>::inf = 1e12;

} /* namespace cg */

} /* namespace gatelib */

#endif /* _CG_META_HPP_ */
