#include <queue> 
#include <cstdio> 
#include <climits> 
#include <utility> 
#include <cstring> 
using namespace std;
const int N = 2555;
struct glist
{
    int va[N << 1]; // Edge weight value. 
    int ne[N << 1]; // Next edge of edge. 
    int he[N << 1]; // Head node of edge. 
    int fe[N]; // First edge of node. 
    int n; // Number of nodes, managed manually. 
    int m; // Number of edges, managed by insert(). 
    int dis; // Disabled edge. 
    inline void reset() {
        memset(fe, -1, sizeof fe);
        n = 0; m = 0; dis = -1;
    }
    inline void insert_single(int u, int v, int value) {
        va[m] = value;
        ne[m] = fe[u];
        he[m] = v;
        fe[u] = m++;
    }
    inline void insert(int u, int v, int value) {
        insert_single(u, v, value);
        insert_single(v, u, value);
    }
    inline static int reversed_edge(int e) {
        return e ^ 1;
    }
    inline int tail_vertex(int e) const {
        return he[reversed_edge(e)];
    }
    inline bool is_disabled_edge(int e) const {
        if (e == dis || e == reversed_edge(dis))
            return true;
        return false;
    }
};
struct tree_diameter
{
    int v1, v2, dist, prev[N];
    bool vst[N];
    inline void reset() {
        v1 = v2 = -1;
        dist = 0;
        memset(prev, -1, sizeof prev);
    }
    inline void find_max(const glist &g, int u, int &v, int &dist)
    {
        v = u; dist = 0;
        queue<pair<int, int> > qu;
        qu.push(make_pair(u, 0));
        memset(vst, false, sizeof vst);
        vst[u] = true;
        while (!qu.empty())
        {
            int x = qu.front().first;
            int d = qu.front().second;
            qu.pop();
            if (d > dist)
            {
                v = x;
                dist = d;
            }
            for (int e = g.fe[x]; e != -1; e = g.ne[e])
            {
                if (g.is_disabled_edge(e))
                    continue;
                int y = g.he[e];
                if (vst[y])
                    continue;
                vst[y] = true;
                int w = g.va[e];
                qu.push(make_pair(y, d + w));
                prev[y] = glist::reversed_edge(e);
            }
        }
    }
    inline void solve(const glist &g, int u = 0) {
        find_max(g, u, v1, dist);
        find_max(g, v1, v2, dist);
    }
};
struct tree_radius
{
    int v, dist;
    inline void reset() {
        v = -1; dist = 0;
    }
    inline void solve(const glist &g, const tree_diameter &diam)
    {
        int x = diam.v2, y = -1; v = diam.v2;
        for (int e = diam.prev[x]; e != -1; e = diam.prev[y])
        {
            if (g.is_disabled_edge(e))
                continue;
            y = g.he[e];
            dist += g.va[e];
            if ((dist << 1) >= diam.dist)
            {
                int dist2 = diam.dist - (dist - g.va[e]);
                if (dist < dist2) {
                    v = y;
                } else {
                    v = x;
                    dist = dist2;
                }
                return;
            }
            x = y;
        }
    }
};
glist graph;
tree_diameter diameter;
tree_radius radius;
int main()
{
    // freopen("input.txt", "r", stdin); 
    // freopen("output.txt", "w", stdout); 
    int T, result;
    scanf("%d", &T);
    for (int i = 1; i <= T; ++i)
    {
        graph.reset();
        scanf("%d", &graph.n);
        result = INT_MAX;
        int u, v, w;
        for (int j = 1; j < graph.n; ++j)
        {
            scanf("%d %d %d", &u, &v, &w);
            graph.insert(u, v, w);
        }
        int r1, r2, d1, d2, l;
        for (int e = 0; e < graph.m; e += 2)
        {
            v = graph.he[e];
            u = graph.tail_vertex(e);
            graph.dis = e;
            l = graph.va[e];
            diameter.reset();
            diameter.solve(graph, u);
            radius.reset();
            radius.solve(graph, diameter);
            d1 = diameter.dist;
            r1 = radius.dist;
            diameter.reset();
            diameter.solve(graph, v);
            radius.reset();
            radius.solve(graph, diameter);
            d2 = diameter.dist;
            r2 = radius.dist;
            int t = r1 + r2 + l;
            if (t < d1) t = d1;
            if (t < d2) t = d2;
            if (t < result) result = t;
        }
        printf("Case %d: %d\n", i, result);
    }
    return 0;
}