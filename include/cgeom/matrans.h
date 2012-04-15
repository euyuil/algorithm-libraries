#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;
const double pi = acos(-1.0);
template <int M, int N>
struct matrix
{
    double w[M][N];
    inline double &operator()(int i, int j)
    {
        return w[i][j];
    }
    inline const double &operator()(int i, int j) const
    {
        return w[i][j];
    }
    template <int R>
    inline matrix<M, R> operator*(const matrix<N, R> &b) const
    {
        matrix<M, R> r;
        memset(&r, 0, sizeof r);
        for (int i = 0; i < M; ++i)
            for (int j = 0; j < R; ++j)
                for (int k = 0; k < N; ++k)
                    r(i, j) += w[i][k] * b(k, j);
        return r;
    }
};
template <int N>
inline matrix<N, N> identity()
{
    matrix<N, N> r;
    memset(&r, 0, sizeof r);
    for (int i = 0; i < N; ++i)
        r(i, i) = 1.0;
    return r;
}
inline matrix<4, 1> vector3(double x, double y, double z)
{
    matrix<4, 1> r;
    memset(&r, 0, sizeof r);
    r(0, 0) = x; r(1, 0) = y; r(2, 0) = z; r(3, 0) = 1.0;
    return r;
}
inline matrix<4, 4> translate3(double x, double y, double z)
{
    matrix<4, 4> r;
    memset(&r, 0, sizeof r);
    r(0, 0) = 1.0; r(1, 1) = 1.0; r(2, 2) = 1.0;
    r(0, 3) = x; r(1, 3) = y; r(2, 3) = z; r(3, 3) = 1.0;
    return r;
}
inline matrix<4, 4> scale3(double x, double y, double z)
{
    matrix<4, 4> r;
    memset(&r, 0, sizeof r);
    r(0, 0) = x; r(1, 1) = y; r(2, 2) = z; r(3, 3) = 1.0;
    return r;
}
inline void normalize(double &x, double &y, double &z)
{
    double below = sqrt(x * x + y * y + z * z);
    x /= below; y /= below; z /= below;
}
inline matrix<4, 4> rotate3(double x, double y, double z, double a)
{
    matrix<4, 4> r; normalize(x, y, z);
    double cosa = cos(a), mcsa = 1.0 - cosa, sina = sin(a);
    double xy = x * y, yz = y * z, zx = z * x;
    double x2 = x * x, y2 = y * y, z2 = z * z;
    double xsna = x * sina, ysna = y * sina, zsna = z * sina;
    r(0, 0) = cosa + mcsa * x2; r(0, 1) = mcsa * xy - zsna;
    r(0, 2) = mcsa * zx + ysna; r(0, 3) = 0.0;
    r(1, 0) = mcsa * xy + zsna; r(1, 1) = cosa + mcsa * y2;
    r(1, 2) = mcsa * yz - xsna; r(1, 3) = 0.0;
    r(2, 0) = mcsa * zx - ysna; r(2, 1) = mcsa * yz + xsna;
    r(2, 2) = cosa + mcsa * z2; r(2, 3) = 0.0;
    r(3, 0) = 0.0; r(3, 1) = 0.0; r(3, 2) = 0.0; r(3, 3) = 1.0;
    return r;
}
template <int N> // Assumes t > 1. 
inline matrix<N, N> self_multiply(const matrix<N, N> &a, int t)
{
    matrix<N, N> r = a;
    int u = t, n = 0, i;
    while (u >>= 1) ++n;
    for (i = n - 1; i >= 0; --i)
    {
        r = r * r;
        if ((t >> i) & 1)
            r = r * a;
    }
    return r;
}
char buffer[64];
double px, py, pz, pa;
int pt;
matrix<4, 4> repeat(int t)
{
    matrix<4, 4> r = identity<4>();
    while (scanf("%s", buffer))
    {
        if (!strcmp(buffer, "end"))
            break;
        else if (!strcmp(buffer, "translate"))
        {
            scanf("%lf %lf %lf", &px, &py, &pz);
            r = translate3(px, py, pz) * r;
        }
        else if (!strcmp(buffer, "scale"))
        {
            scanf("%lf %lf %lf", &px, &py, &pz);
            r = scale3(px, py, pz) * r;
        }
        else if (!strcmp(buffer, "rotate"))
        {
            scanf("%lf %lf %lf %lf", &px, &py, &pz, &pa);
            r = rotate3(px, py, pz, pa / 180.0 * pi) * r;
        }
        else if (!strcmp(buffer, "repeat"))
        {
            scanf("%d", &pt);
            r = repeat(pt) * r;
        }
    }
    if (t <= 0)
        return identity<4>();
    if (t > 1)
        return self_multiply<4>(r, t);
    return r;
}
inline void preprocess(double &a)
{
    static char buf[32];
    sprintf(buf, "%0.2lf", a);
    if (!strcmp(buf, "-0.00")) a = 0.0;
}
inline void print_vector3(const matrix<4, 1> &v)
{
    double x = v(0, 0), y = v(1, 0), z = v(2, 0);
    preprocess(x); preprocess(y); preprocess(z);
    printf("%0.2lf %0.2lf %0.2lf", x, y, z);
}
inline void calculate(const matrix<4, 4> &m, int n)
{
    while (n--)
    {
        scanf("%lf %lf %lf", &px, &py, &pz);
        print_vector3(m * vector3(px, py, pz));
        printf("\n");
    }
}
int main()
{
    // freopen("input.txt", "r", stdin); 
    int n;
    while (scanf("%d", &n))
    {
        if (n == 0)
            break;
        calculate(repeat(1), n);
        printf("\n");
    }
    return 0;
}
