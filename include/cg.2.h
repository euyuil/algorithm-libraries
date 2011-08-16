#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

// Frequently used functions.

#define eps 1e-8
#define inf 1e8

inline int sgn(double a) {
	return a > eps ? 1 : a < -eps ? -1 : 0;
}

inline bool lt(double a, double b) { return sgn(a - b) < 0; }
inline bool gt(double a, double b) { return sgn(a - b) > 0; }
inline bool eq(double a, double b) { return sgn(a - b) == 0; }

// Point structure and functions.

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

inline double cross(const point &a, const point &b) {
	return a.x * b.y - b.x * a.y;
}

inline double dot(const point &a, const point &b) {
	return a.x * b.x + a.y * b.y;
}

// Line structure.

struct line {
	point a, b;
	line() { }
	line(const point &_a, const point &_b) : a(_a), b(_b) { }
	line ray() const {
		point t = vec();
		return line(a, a + t * (inf / max(t.x, t.y)));
	}
	point vec() const { return b - a; }
	double len() const { return vec().mag(); }
};

// Relationship detecting.
// p: point; l: line; s: segment; o: polygon.
// raw: means the function will return original calculated value.

inline int relpl(const point &p, const line &l) {
	return sgn(cross(p - l.a, l.vec())); // 0: on; -1: .|; 1: |..
}

inline int relps(const point &p, const line &s) {
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

inline int relll(const line &la, const line &lb) {
	point u = la.vec(), v = lb.vec();
	double x = u.y * v.x, y = v.y * u.x;
	if (eq(x, y))
		if (!relpl(la.a, lb))
			return 2; // The same line.
		else return 0; // They are parallel.
	return 1; // The two lines intersect.
}

inline int rells(const line &l, const line &s) {
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

inline int relssraw(const line &sa, const line &sb) {
	int r; char (*p)[4] = (char (*)[4])(&r);
	(*p)[0] = relps(sa.a, sb);
	(*p)[1] = relps(sa.b, sb);
	(*p)[2] = relps(sb.a, sa);
	(*p)[3] = relps(sb.b, sa);
	return r;
}

inline int relss(const line &sa, const line &sb, int raw) {
	char r[4], s[4] = {0};
	*(int *)r = relssraw(sa, sb);
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
	return 8; // No intersection. Maybe parallel, same-line, or others.
}

inline int relss(const line &sa, const line &sb) {
	return relss(sa, sb, relssraw(sa, sb));
}

template <typename I> inline int relpo(const point &p, I b, I e) {
	if (b == e) return 2; // 2: Outside from the polygon.
	I next = b + 1;
	if (next == e) return p == *b ? 1 : 2; // 1: On the edge of the polygon.
	int count = 0; I it = b;
	line r = line(p, point(p.x + 1.0, p.y)).ray();
	for ( ; next != end; ++it, ++next) {
		line s(*it, *next); // For each edge s of the polygon...
		if (relps(p, s) < 2)
			return 1; // 1: The point is on an edge.
		if (sgn(s.vec().y)) { // If edge s isn't horizontal...
			int w = relssraw(s, r);
			int m = relss(s, r, w);
			if (m == 1) { // If one of the end-points is on the ray...
				bool u = ((w & 0xff) == 0); // Whether s.a is on the ray.
				bool v = gt(s.a.y, s.b.y); // Whether s.a is higher than s.b.
				if (!(u ^ v)) ++count; // If the end-points is on the ray and it's higher.
			} else if (m == 0) // Standard intersection.
				++count;
		}
	}
	return (count & 1) ? 0 : 2; // 0: In the polygon!
}

// Calculating.
// inp: intersection point; area: area; dis: distance.

inline point inpll(const line &la, const line &lb) {
	point x(la.b.x - la.a.x, la.b.y - la.a.y);
	point y(lb.a.x - lb.b.x, lb.a.y - lb.b.y);
	point b(lb.a.x - la.a.x, lb.a.y - la.a.y);
	double below = cross(x, y), above1 = cross(b, y);
	double f1 = above1 / below;
	return la.a + la.vec() * f1;
}

template <typename I> inline double areao(I b, I e) {
	if (b == e) return 0.0;
	I next = b + 1;
	if (next == e) return 0.0;
	double area = 0.0;
	I it = b;
	for ( ; next != e; ++it, ++next)
		area += it->cross(*next);
	area += it->cross(*b);
	return area / 2.0;
}

inline double dispp(const point &a, const point &b) {
    return (b - a).mag();
}

inline double displ(const point &p, const line &l) {
    return abs(cross(l.vec(), p - l.a)) / l.len();
}

/**
 * @brief This class can calculate the convex hull of the given point set.
 * @date 2011-08-15
 */

template <typename I, typename O> class graham {

private:

    O top;
    vector<bool> used;
    vector<size_t> stk;
    
public:

    graham(I b, I e, O o) : top(o) {
        sort(b, e, compare); I it;
        size_t i = 0, n = e - b; int k = 0;
        used.resize(n); stk.reserve(n);

        for (it = b; i < 2 && it != e; ++i, ++it)
            *(top++) = *it, used[i] = true, stk.push_back(i);
		if (it == e) return; used[0] = false;

        for ( ; it != e; ++it, ++i) {
            while (stk.size() > 1 && ( k = sgn(cross( *(top-1) - *(top-2), *it - *(top-2) )) ) < 0)
				--top, used[stk.back()] = false, stk.pop_back();
			if (k == 0) --top; *(top++) = *it; used[i] = true; stk.push_back(i);
        }

        for (it = e - 1, --i; i < used.size(); --it, --i) {
            if (used[i]) continue;
            while (( k = sgn(cross( *(top-1) - *(top-2), *it - *(top-2) )) ) < 0) --top;
			if (k == 0) --top; if (it == b) break; *(top++) = *it;
        }
    }

    operator O() const { return top; }

private:

    static bool compare(const point &a, const point &b) {
        int s = sgn(a.y - b.y);
        if (s) return s < 0;
        return lt(a.x, b.x);
    }
};
