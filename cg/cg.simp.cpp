#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

#define eps 1e-8
#define inf 1e8

inline int sgn(double a) {
	if (a < -eps) return -1;
	else if (a > eps) return 1;
	return 0;
}

inline bool lt(double a, double b) { return sgn(a - b) < 0; }
inline bool gt(double a, double b) { return sgn(a - b) > 0; }
inline bool eq(double a, double b) { return sgn(a - b) == 0; }

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
	double sqrmag() const { return x * x + y * y; }
	double mag() const { return sqrt(sqrmag()); }
};

inline double cross(const point &a, const point &b) {
	return a.x * b.y - b.x * a.y;
}

inline double dot(const point &a, const point &b) {
	return a.x * b.x + a.y * b.y;
}

struct line {
	point a, b;
	line() { }
	line(const point &_a, const point &_b) : a(_a), b(_b) { }
	point dir() const { return b - a; }
	double len() const { return dir().mag(); }
};

// Whether line intersects segment.
inline bool intersects(const line &l, const line &s) {
	double a = cross(s.a - l.a, l.b - l.a);
	double b = cross(s.b - l.a, l.b - l.a);
	return sgn(a * b) <= 0;
}

// Intersection point of two lines.
inline point intersection_point(const line &la, const line &lb) {
	point x(la.b.x - la.a.x, la.b.y - la.a.y);
	point y(lb.a.x - lb.b.x, lb.a.y - lb.b.y);
	point b(lb.a.x - la.a.x, lb.a.y - la.a.y);
	double below = cross(x, y), above1 = cross(b, y);
	double f1 = above1 / below;
	return la.a + (la.b - la.a) * f1;
}

inline bool is_point_on_line(const point &p, const line &l) {
	return !sgn(cross(l.dir(), p - l.b));
}

// 0 parallel; 1 intersects; 2 same.
inline int line_line_relationship(const line &la, const line &lb) {

	point u = la.dir(), v = lb.dir();
	double x = u.y * v.x, y = v.y * u.x;

	if (eq(x, y))
		if (is_point_on_line(la.a, lb))
			return 2;
		else return 0;
	return 1;
}
