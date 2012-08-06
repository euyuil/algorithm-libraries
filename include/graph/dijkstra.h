#ifndef _GT_MAT_DIJKSTRA_H_
#define _GT_MAT_DIJKSTRA_H_

#include <gt.mat.base.h>
#include <cstring>

using namespace std;

namespace glib {

namespace gt {

struct dijkstra
{
    double dist[mxn]; bool vs[mxn];

    void reset(gmatrix &g, size_t s) {
        memset(vs, 0, sizeof(vs));
        for (size_t i = 0; i < g.n; ++i)
            dist[i] = inf;
        dist[s] = 0.0; vs[s] = true;
    }

    double solve(gmatrix &g, size_t s, size_t t) {
        reset(g, s);
        for (size_t i = 1; i < g.n; ++i) {
            double val = inf; size_t k = -1;
            for (size_t j = 0; j < g.n; ++j) {
                if (vs[j]) continue;
                if (dist[j] > g.w[s][j] + dist[s])
                    dist[j] = g.w[s][j] + dist[s];
                if (val > dist[j]) {
                    val = dist[j]; k = j;
                }
            }
            if (k == -1) break; // No more accessible nodes.
            s = k; vs[k] = true;
        }
        return dist[t];
    }
};

} // namespace gt

} // namespace glib

#endif /* _GT_MAT_DIJKSTRA_H_ */
