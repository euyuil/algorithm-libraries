#include <queue> 
#include <cstdio> 
#include <climits> 
#include <cstring> 
using namespace std;
const int N = 15;
const int M = 155;
const int inf = INT_MAX >> 1;
struct glist
{
    int we[M], fe[N], ne[M], he[M], m, n;
    bool seaside[N];
    inline void reset(int graph_size = 0) {
        memset(fe, -1, sizeof fe);
        memset(seaside, false, sizeof seaside);
        m = 0; n = graph_size;
    }
    inline void insert(int u, int v, int weight) {
        we[m] = weight;
        ne[m] = fe[u];
        he[m] = v;
        fe[u] = m++;
    }
};
struct spfa
{
    int dist[N]; bool inqu[N];
    inline void reset() {
        for (int i = 0; i < N; ++i)
            dist[i] = inf;
        memset(inqu, false, sizeof inqu);
    }
    inline void solve(const glist &g, int start)
    {
        queue<int> qu;
        qu.push(start); inqu[start] = true;
        dist[start] = 0;
        while (!qu.empty())
        {
            int u = qu.front();
            qu.pop(); inqu[u] = false;
            for (int e = g.fe[u]; e != -1; e = g.ne[e])
            {
                int v = g.he[e];
                int d = dist[u] + g.we[e];
                if (d < dist[v])
                {
                    dist[v] = d;
                    if (!inqu[v]) {
                        qu.push(v); inqu[v] = true;
                    }
                }
            }
        }
    }
};
glist graph;
spfa shortest_path;
int main()
{
    // freopen("input.txt", "r", stdin); 
    while (scanf("%d", &graph.n) != EOF)
    {
        graph.reset(graph.n);
        for (int i = 0; i < graph.n; ++i)
        {
            int m, p;
            scanf("%d %d", &m, &p);
            if (p == 0)
                graph.seaside[i] = false;
            else
                graph.seaside[i] = true;
            for (int j = 0; j < m; ++j)
            {
                int s, l;
                scanf("%d %d", &s, &l);
                graph.insert(i, s, l);
            }
        }
        shortest_path.reset();
        shortest_path.solve(graph, 0);
        int result = inf;
        for (int i = 0; i < graph.n; ++i)
            if (graph.seaside[i] && shortest_path.dist[i] < result)
                result = shortest_path.dist[i];
        printf("%d\n", result);
    }
    return 0;
}