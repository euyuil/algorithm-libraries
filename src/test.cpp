#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;

const double inf = 1e+8;
const double eps = 0.0;
const size_t mxn = 5000;
const size_t mxe = 250000;

struct point {
	double x, y;
	inline point() { }
	inline point(double a, double b) : x(a), y(b) { }
	inline point operator-(const point &p) const {
		return point(x - p.x, y - p.y);
	}
	inline double magsqr() const { return x * x + y * y; }
	inline double mag() const { return sqrt(magsqr()); }
};

struct line {
	point a, b;
	inline line() { }
	inline line(const point &x, const point &y) : a(x), b(y) { }
	inline line(double x, double y, double z, double w) : a(x, y), b(z, w) { }
	inline point vec() const { return b - a; }
	inline double len() const { return vec().mag(); }
};

struct gmatrix {
	double w[mxn][mxn]; size_t n;
	void reset() { memset(w, 0, sizeof(w)); }
	void reset(double val) {
		for (size_t i = 0; i < n; ++i)
			for (size_t j = 0; j < n; ++j)
				w[i][j] = val;
	}
};

struct dijkstra {
	double dist[mxn]; bool vs[mxn];
	void reset(gmatrix &g, size_t s) {
		memset(vs, 0, sizeof(vs));
		for (size_t i = 0; i < g.n; ++i)
			dist[i] = inf;
		dist[s] = 0.0; vs[s] = true;
	}
	double solve(gmatrix &g, size_t s, size_t t) {
		reset(g, s);
		for(size_t i = 1; i < g.n; ++i) {
			double val = inf; size_t k = -1;
			for (size_t j = 0; j < g.n; ++j) {
				if (vs[j]) continue;
				if (dist[j] > g.w[s][j] + dist[s])
					dist[j] = g.w[s][j] + dist[s];
				if (val > dist[j]) {
					val = dist[j]; k = j;
				}
			}
			if (k == -1) break;
			s = k; vs[k] = true;
		}
		return dist[t];
	}
};

inline int sgn(double a) {
	return a > eps ? 1 : a < -eps ? -1 : 0;
}

inline double cross(const point &a, const point &b) {
	return a.x * b.y - b.x * a.y;
}

inline int relps(const point &p, const line &s) {
	return sgn(cross(p - s.a, s.vec()));
}

inline int relss(const line &sa, const line &sb) {
	int a = relps(sa.a, sb), b = relps(sa.b, sb);
	int c = relps(sb.a, sa), d = relps(sb.b, sa);
	if (a * b == -1 && c * d == -1)
		return 0;
	return 1;
}

point ps[555]; size_t pc = 2;
line ls[999]; size_t lc = 0;
gmatrix gr; dijkstra dij;

bool test() {
    size_t n; scanf("%lu", &n); if (n == -1) return false;
    pc = 2; ps[0] = point(0.0, 5.0); ps[1] = point(10.0, 5.0); lc = 0;
    while (n--) {
        double x, a, b, c, d;
        scanf("%lf%lf%lf%lf%lf", &x, &a, &b, &c, &d);
        ps[pc++] = point(x, a); ps[pc++] = point(x, b);
        ps[pc++] = point(x, c); ps[pc++] = point(x, d);
        if (sgn(a)) ls[lc++] = line(x, 0, x, a);
        if (sgn(d - 10.0)) ls[lc++] = line(x, d, x, 10.0);
        ls[lc++] = line(x, b, x, c);
    }
	gr.n = pc; gr.reset(inf);
    for (size_t i = 0; i < pc; ++i) {
        for (size_t j = i + 1; j < pc; ++j) {
            line seg(ps[i], ps[j]);
            for (size_t k = 0; k < lc; ++k)
                if (relss(seg, ls[k]) == 0)
					goto invalid_segment;
            gr.w[i][j] = gr.w[j][i] = seg.len();
invalid_segment:
			; // Notice to add this.
        }
    }
    double result = dij.solve(gr, 0, 1);
    printf("%0.2f\n", result);
    return true;
}

int main(int, char *[]) {
    while (test());
    return EXIT_SUCCESS;
}
