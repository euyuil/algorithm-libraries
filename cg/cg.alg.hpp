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
	T area = T(0);
	Iterator next = begin + 1;

	if (begin == end || next == end)
		return area;

	Iterator it = begin;

	for ( ; next != end; ++it, ++next)
		area += vector2<T>::cross(*it, *next);
	area += vector2<T>::cross(*it, *begin);

	return area / T(2);
}

} /* namespace cg */

} /* namespace gatelib */

#endif /* _CG_ALG_HPP_ */
