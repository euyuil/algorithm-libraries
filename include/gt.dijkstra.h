#include <gt.graph.h>

using namespace std;

template <size_t Nn, size_t Ne> struct dijkstra
{
    typedef graph<size_t, double, Nn, Ne> Tg;

    const double inf = 9999999.9;

    void initialize_single_source(Tg &g, size_t s) {
        for (size_t i = 1; i < g.nodes_count; ++i) {
            d[i] = inf;
            p[i] = 0;
        }
        d[s] = 0.0;
    }

    dijkstra(Tg &g, size_t s) {
        initialize_single_source(g, s);
        for (size_t c = 2; c < g.nodes_count; ++c) {
        }
    }
};
