#ifndef _CGEOM_RELPS_H_
#define _CGEOM_RELPS_H_

/**
 * @brief Calculates the relationship between a point and a segment.
 * @param p The point.
 * @param s The line segment.
 * @return  0 if the point is between the two end-points of the segment;
 *         -1 if the point is at the end-point a of the segment;
 *          1 if the point is at the end-point b of the segment;
 *         -2 if the point is on the line s and near the end-point a;
 *          2 if the point is on the line s and near the end-point b;
 *         -3 if the point is on the left of vector ab of segment s;
 *          3 if the point is on the right of vector ab of segment s.
 * @date 2011-08-10
 */

inline int relps(const point &p, const line &s) {
	// int rp = sgn(cross(p - s.a, s.vec())); // Rel between p and the line s.
	int rp = relpl(p, s); // Rel between p and the line s.
	if (rp) return rp * 3; // -3: .|; 3: |..
	point psa = s.a - p, psb = s.b - p;
	int r = sgn(dot(psa, psb));
	if (r < 0) return 0; // The point is on the segment between end-points.
	if (r == 0) {
		if (p == s.a) return -1; // The point is at s.a.
		else return 1; // The point is at s.b.
	}
	if (psa.magsqr() <= psb.magsqr())
		return -2; // The point is on the line s, near s.a.
	return 2; // The point is on the line s, near s.b.
}

/**
 * @brief Simpler function to calculate the relationship between a point and a
 *        segment.
 * @param p The point.
 * @param s The line segment.
 * @return  0 if the point is between the two end-points of the segment;
 *          1 if the point is at either end-point of the segment;
 *          2 if the point is on the line s;
 *         -3 if the point is on the left of vector ab of segment s;
 *          3 if the point is on the right of vector ab of segment s.
 * @date 2011-08-22
 */

inline int relpssimp(const point &p, const line &s) {
	// int rp = sgn(cross(p - s.a, s.vec())); // Rel between p and the line s.
	int rp = relpl(p, s); // Rel between p and the line s.
	if (rp) return rp * 3; // -3: .|; 3: |..
	point psa = s.a - p, psb = s.b - p;
	int r = sgn(dot(psa, psb));
	if (r < 0) return 0; // The point is on the segment between end-points.
	if (r == 0) return 1; // The point is at either end-point.
	return 2; // The point is on the line s.
}

#endif /* _CGEOM_RELPS_H_ */
