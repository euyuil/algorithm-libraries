#ifndef _GRAPH_TARJAN_H_
#define _GRAPH_TARJAN_H_

#include <dtstc/dsu.h>
#include <graph/glist.h>

template <int N>
struct tarjan
{
    int dfn[N], low[N], stk[N], stksz, index;
    bool instk[N], vst[N];
    dsu_t comp;
    const glist *g;

    inline void reset(const glist &graph) {
        memset(instk, false, sizeof instk);
        memset(vst, false, sizeof vst);
        comp.reset();
        stksz = index = 0; g = &graph;
    }

    void recursive(int u) {
        int v;
        dfn[u] = low[u] = index++; vst[u] = true;
        stk[stksz++] = u; instk[u] = true;

        for (int e = g->fe[u]; e != -1; e = g->ne[e]) {
            v = g->he[e];
            if (!vst[v] || instk[v]) {
                if (!vst[v]) recursive(v);
                low[u] = min(low[u], low[v]);
            }
        }

        if (dfn[u] == low[u]) do {
            v = stk[--stksz]; instk[v] = false;
            comp.merge(u, v);
        } while (u != v);
    }

    inline void solve() {
        for (int i = 0; i < g->n; ++i)
            if (!vst[i])
                recursive(i);
    }
};

#endif /* _GRAPH_TARJAN_H_ */
