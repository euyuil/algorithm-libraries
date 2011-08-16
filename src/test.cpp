#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstdio>
#include <cmath>

using namespace std;

#define inf 1e8
#define eps 1e-12

inline int sgn(double a) {
	return a > eps ? 1 : a < -eps ? -1 : 0;
}

inline bool eq(double a, double b) { return sgn(a - b) == 0; }

struct point {
	double x, y;
	point() : x(0.0), y(0.0) { }
	point(double _x, double _y) : x(_x), y(_y) { }
	double &operator[](bool i) { return i ? y : x; }
	point operator+(const point &p) const {
		return point(x + p.x, y + p.y);
	}
	point operator-(const point &p) const {
		return point(x - p.x, y - p.y);
	}
	point operator*(double k) const {
		return point(x * k, y * k);
	}
	point operator/(double k) const {
		return point(x / k, y / k);
	}
	bool operator==(const point &p) const {
		return !sgn(x - p.x) && !sgn(y - p.y);
	}
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
	line(double x1, double y1, double x2, double y2) :
	a(point(x1, y1)), b(point(x2, y2)) { }
	point &operator[](bool i) { return i ? b : a; }
	point vec() const { return b - a; }
};

inline int relps(const point &p, const line &s) {
	int rp = sgn(cross(p - s.a, s.vec()));
	if (rp) return rp * 3;
	point psa = s.a - p, psb = s.b - p;
	int r = sgn(dot(psa, psb));
	if (r < 0) return 0;
	if (r == 0) return 1;
	return 2;
}

inline int rells(const line &l, const line &s) {
	double a = cross(s.a - l.a, l.b - l.a);
	double b = cross(s.b - l.a, l.b - l.a);
	int sab = sgn(a * b), sa = sgn(a), sb = sgn(b);
	if (sab > 0) return 3;
	if (sab < 0) return 0;
	if (sa || sb) return 1;
	return 2;
}

inline int relssraw(const line &sa, const line &sb) {
	int r; signed char (*p)[4] = (signed char (*)[4])(&r);
	(*p)[0] = relps(sa.a, sb); (*p)[1] = relps(sa.b, sb);
	(*p)[2] = relps(sb.a, sa); (*p)[3] = relps(sb.b, sa);
	return r;
}

inline int relss(const line &sa, const line &sb, int raw) {
	signed char r[4], s[4] = {0};
	*(int *)r = raw;
	if (r[0] * r[1] == -9 && r[2] * r[3] == -9)
		return 0;
	++s[abs(r[0])]; ++s[abs(r[1])]; ++s[abs(r[2])]; ++s[abs(r[3])];
	if (s[0] == 1 && s[3] == 3) return 1;
	if (s[1] == 2 && s[3] == 2) return 2;
	return 8;
}

inline int relss(const line &sa, const line &sb) {
	return relss(sa, sb, relssraw(sa, sb));
}

inline point inpll(const line &la, const line &lb) {
	double u = cross(la.vec(), point(lb.b - la.b));
	double v = cross(la.vec(), point(lb.a - la.b));
	return (lb.b * v - lb.a * u) / (v - u);
}

int main(int argc, char *argv[]) {

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	size_t t; cin >> t;
	while (t--) {
		line u, v; line *ls[2]; ls[0] = &u; ls[1] = &v;
		cin >> u.a.x >> u.a.y >> u.b.x >> u.b.y;
		cin >> v.a.x >> v.a.y >> v.b.x >> v.b.y;
		if (relss(u, v) < 3) {
			point w = inpll(u, v); double area = 0.0;

			for (size_t i = 0; i < 2; ++i) {
				line &tl = *ls[i]; // This line.
				line &al = *ls[!i]; // Another line.
				for (size_t j = 0; j < 2; ++j) {
					point &tp = tl[j]; // This point.
					line hor(min(al.a.x, al.b.x)-1.0, tp.y, max(al.a.x, al.b.x)+1.0, tp.y);
					line ver(tp.x, tp.y, tp.x, max(tp.y, max(al.a.y, al.b.y))+1.0);
					if (tp.y > w.y && rells(hor, al) < 2 && relss(ver, al) > 7) {
						point z;
						z.x = al.a.x + (tp.y-al.a.y) * (al.b.x-al.a.x) / (al.b.y-al.a.y);
						z.y = tp.y;
						//point z = inpll(hor, al); // It's not so precise. Why?
						area = max(area, fabs(cross(w - tp, z - tp)) / 2.0);
					}
				}
			}

			printf("%0.2lf\n", area);
		} else
			cout << "0.00" << endl;
	}

	return EXIT_SUCCESS;
}
