#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

#define eps 1e-8
#define inf 1e8

// Basic structures.

struct point {
	double x, y;
	point() : x(0.0), y(0.0) { }
	point(double _x, double _y) : x(_x), y(_y) { }
	point operator+(const point &p) const {
		return point(x + p.x, y + p.y);
	}
	point operator-(const point &p) const {
		return point(x - p.x, y - p.y);
	}
	point operator*(double k) const {
		return point(x * k, y * k);
	}
	bool operator==(const point &p) const {
		return !sgn(x - p.x) && !sgn(y - p.y);
	}
	double magsqr() const { return x * x + y * y; }
	double mag() const { return sqrt(magsqr()); }
};

struct line {
	point a, b;
	line() { }
	line(const point &_a, const point &_b) : a(_a), b(_b) { }
	point vec() const { return b - a; }
	double len() const { return vec().mag(); }
};

// Utility functions.

inline int sgn(double a) {
	return a > eps ? 1 : a < -eps ? -1 : 0;
}

inline bool lt(double a, double b) { return sgn(a - b) < 0; }
inline bool gt(double a, double b) { return sgn(a - b) > 0; }
inline bool eq(double a, double b) { return sgn(a - b) == 0; }

inline double cross(const point &a, const point &b) {
	return a.x * b.y - b.x * a.y;
}

inline double dot(const point &a, const point &b) {
	return a.x * b.x + a.y * b.y;
}

// Relationship detecting.

inline int relationship_point_line(const point &p, const line &l) {
	return sgn(cross(p - l.a, l.vec())); // 0: on; -1: .|; 1: |..
}

inline int relationship_point_segment(const point &p, const line &s) {
	int rp = sgn(cross(p - s.a, s.vec())); // Rel between p and the line s.
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

inline int relationship_line_line(const line &la, const line &lb) {
	point u = la.vec(), v = lb.vec();
	double x = u.y * v.x, y = v.y * u.x;
	if (eq(x, y))
		if (!relationship_point_line(la.a, lb))
			return 2; // The same line.
		else return 0; // They are parallel.
	return 1; // The two lines intersect.
}

inline int relationship_line_segment(const line &l, const line &s) {
	double a = cross(s.a - l.a, l.b - l.a);
	double b = cross(s.b - l.a, l.b - l.a);
	int sab = sgn(a * b), sa = sgn(a), sb = sgn(b);
	if (sab > 0)
		return 0; // No intersection point.
	if (sab < 0)
		return 1; // Standard intersection.
	if (sa || sb)
		return 2; // One of the end-points of the segment intersects the line.
	return 3; // The segment is a part of the line.
}

inline int relationship_segment_segment(const line &sa, const line &sb) {
	int saa = relationship_point_segment(sa.a, sb);
	int sab = relationship_point_segment(sa.b, sb);
	int sba = relationship_point_segment(sb.a, sa);
	int sbb = relationship_point_segment(sb.b, sa);
	if (saa * sab == -9 && sba * sbb == -9)
		return 0; // Standard intersection (X).
	char s[4] = {0};
	++s[abs(saa)]; ++s[abs(sab)];
	++s[abs(sba)]; ++s[abs(sbb)];
	if (s[0] == 1 && s[3] == 3) return 1; // Nonstandard intersection (T).
	if (s[1] == 2 && s[3] == 2) return 2; // Nonstandard intersection (7).
	if (s[1] == 2 && s[2] == 2) return 3; // Nonstandard intersection (--).
	if (s[0] == 2 && s[2] == 2) return 4; // Nonstandard intersection (~=-).
	if (s[0] == 1 && s[1] == 2 && s[2] == 1) return 5; // n-std inters. (~=).
	if (s[0] == 2 && s[2] == 2) return 6; // n-std inters. (Long fully cover short).
	if (s[1] == 4) return 7; // Nonstandard intersection (=).
	// if (s[0] == 0 && s[1] == 0)
	return 8; // No intersection. Maybe parallel, same-line, or others.
}

// Calculating.

inline point intersection_point_line_line(const line &la, const line &lb) {
	point x(la.b.x - la.a.x, la.b.y - la.a.y);
	point y(lb.a.x - lb.b.x, lb.a.y - lb.b.y);
	point b(lb.a.x - la.a.x, lb.a.y - la.a.y);
	double below = cross(x, y), above1 = cross(b, y);
	double f1 = above1 / below;
	return la.a + (la.b - la.a) * f1;
}
