#ifndef _CGEOM_RELSS_H_
#define _CGEOM_RELSS_H_

/**
 * @brief Calculates the original information about the relationship between
 *        two line segments.
 * @param sa One segment.
 * @param sb The other segment.
 * @return The raw information about the relationship between sa and sb. The
 *         return value has 4 bytes and the lowest byte is the info about sa.a,
 *         next is about sa.b and so on. Each byte is the return value of
 *         function relps (relationship between point and segment).
 * @date 2011-08-15
 */

inline int relssraw(const line &sa, const line &sb) {
	int r; signed char (*p)[4] = (signed char (*)[4])(&r);
	(*p)[0] = relps(sa.a, sb); (*p)[1] = relps(sa.b, sb);
	(*p)[2] = relps(sb.a, sa); (*p)[3] = relps(sb.b, sa);
	return r;
}

/**
 * @brief Calculates the relationship between two segments.
 * @param sa One segment.
 * @param sb The other segment.
 * @param raw The raw relationship information between sa and sb. This param
 *        is optional, or you can give the return value of function relssraw.
 * @return 0 if standard intersection;
 *         1~14 if nonstandard intersection, see the comments of the function
                implementation in detail.
 *         15 no intersection.
 * @date 2011-08-11
 */

inline int relssfull(const line &sa, const line &sb, int raw) {
	signed char r[4], s[4] = {0};
	*(int *)r = raw;
	if (r[0] * r[1] == -9 && r[2] * r[3] == -9)
		return 0; // Standard intersection (X).
	++s[abs(r[0])]; ++s[abs(r[1])]; ++s[abs(r[2])]; ++s[abs(r[3])];
	if (s[0] == 1 && s[3] == 3) return 1; // Nonstandard intersection (T).
	if (s[1] == 2 && s[3] == 2) return 2; // Nonstandard intersection (7).
	if (s[1] == 2 && s[2] == 2) return 3; // Nonstandard intersection (--).
	if (s[0] == 2 && s[2] == 2) return 4; // Nonstandard intersection (~=-).
	if (s[0] == 1 && s[1] == 2 && s[2] == 1) return 5; // n-std inters. (~=).
	if (s[0] == 2 && s[2] == 2) return 6; // n-std inters. (Long fully cover short).
	if (s[1] == 4) return 7; // Nonstandard intersection (=), same segment.
	// if (s[0] == 0 && s[1] == 0)
	return 15; // No intersection. Maybe parallel, same-line, or others.
}

/**
 * @date 2011-08-15
 */

inline int relss(const line &sa, const line &sb) {
	return relssfull(sa, sb, relssraw(sa, sb));
}

/**
 * @brief Simpler function to calculate the relationship between two segments.
 * @param sa One segment.
 * @param sb The other segment.
 * @return 0 if they intersect each other standardly;
 *         15 otherwise.
 * @date 2011-08-22
 */

inline int relsssimp(const line &sa, const line &sb) {
	if (relpl(sa.a, sb) ^ relpl(sa.b, sb) == -2 &&
		relpl(sb.a, sa) ^ relpl(sb.b, sa) == -2)
		return 0;
	return 15;
}

#endif /* _CGEOM_RELSS_H_ */
