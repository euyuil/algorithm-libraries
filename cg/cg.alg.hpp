#ifndef _CG_ALG_HPP_
#define _CG_ALG_HPP_

/************************************************************
 * GATeLib :: Computational Geometry :: Template Algorithms *
 ************************************************************/

namespace gatelib {

namespace cg {

/**
 * @brief Calculate the area of a given polygon. The polygon should be
 *        presented as a point sequence. The points should be ordered
 *        counter-clockwise, or you will get negative area.
 * @param begin : The first point in the sequence.
 * @param end : The (last + 1) point of the sequence.
 * @return The area of the polygon [begin, end).
 * @date 2011-07-28
 */

template <typename T, typename Iterator>
T area_of_polygon(Iterator begin, Iterator end)
{
	if (begin == end) return T(0);

	Iterator next = begin + 1;
	if (next == end) return T(0);

	T area = T(0);

	Iterator it = begin;

	for ( ; next != end; ++it, ++next)
		area += it->cross(*next);
	area += it->cross(*begin);

	return area / T(2);
}


/**
 * @brief To know whether a point is in a polygon or not.
 * @param p : The point.
 * @param begin : The begin iterator of the polygon.
 * @param end : The end iterator of the polygon.
 * @return Whether the point is in the polygon or not.
 * @date 2011-08-09
 */

template <typename T, typename Iterator>
bool is_point_in_polygon(const vector2 &p, Iterator begin, Iterator end)
{
	if (begin == end) return false;

	Iterator next = begin + 1;
	if (next == end) return p == *begin;

	int count = 0; Iterator it = begin;
	ray2<T> r(p.x, p.y, T(1), T(0)); r.make();

	for ( ; next != end; ++it, ++next) {
		lineseg2<T> l(*it, *next);
		if (l.rel(p) == 1) return true;
		if (meta<T>::sgn(l.dir().y)) {
			int m = r.rel(l);
			if (m == 1)
				++count;
			else if (m >= 2) {
				if (meta<T>::eq(l.a.y, p.y)) {
					if (meta<T>::gt(l.b.y, p.y))
						++count;
				} else {
					if (meta<T>::gt(l.a.y, p.y))
						++count;
				}
			}
		}
	}

	return count & 1;
}


/**
 * @date 2011-08-09
 */

template <typename T>
bool graham_scan_lt(const vector2<T> &a, const vector2<T> &b) {
	if (meta<T>::eq(a.y, b.y))
		return meta<T>::lt(a.x, b.x);
	return meta<T>::lt(a.y, b.y);
}

template <typename T, typename IIter, typename OIter>
OIter graham_scan(IIter ibegin, IIter iend, OIter obegin)
{
	sort(ibegin, iend, graham_scan_lt);
}



} /* namespace cg */

} /* namespace gatelib */

#endif /* _CG_ALG_HPP_ */
