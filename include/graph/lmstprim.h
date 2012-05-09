// Less Minimum Spanning Tree (Prim).

#include <algorithm> 
#include <cstring> 
#include <cstdio> 
#include <vector> 
#include <queue> 
#include <cmath> 
using namespace std;
const int N = 1000;
struct edge_t
{
    int u, v;
    inline edge_t() { }
    inline edge_t(int u, int v) : u(u), v(v) { }
};
double graph[N][N], max_edge[N][N];
int n, population[N], posx[N], posy[N];
class length_greater {
public:
    inline bool operator()(const edge_t &a, const edge_t &b) {
        return graph[a.u][a.v] > graph[b.u][b.v];
    }
};
inline void init_and_input()
{
    memset(max_edge, 0, sizeof max_edge);
    memset(graph, 0, sizeof graph);
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d %d %d", posx + i, posy + i, population + i);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            int dx = posx[j] - posx[i];
            int dy = posy[j] - posy[i];
            graph[i][j] = graph[j][i] = sqrt((double)(dx * dx + dy * dy));
        }
    }
}
inline double less_prim()
{
    priority_queue<edge_t, vector<edge_t>, length_greater> edges;
    vector<bool> intree(n, false);
    int last_node = 0; double result = 0;
    for (int i = 1; i < n; ++i)
    {
        intree[last_node] = true;
        // For each edge from last_node. 
        for (int j = 0; j < n; ++j)
            if (!intree[j])
                edges.push(edge_t(last_node, j));
        // Get max valid edge. 
        edge_t edge;
        do {
            edge = edges.top(); edges.pop();
        } while (intree[edge.u] && intree[edge.v]);
        double current_length = graph[edge.u][edge.v];
        result += current_length;
        int intree_node, newly_node;
        if (intree[edge.u]) {
            intree_node = edge.u;
            newly_node = edge.v;
        } else {
            intree_node = edge.v;
            newly_node = edge.u;
        }
        for (int j = 0; j < n; ++j)
        {
            if (intree[j])
            {
                double current_max = max(current_length, max_edge[j][intree_node]);
                max_edge[j][newly_node] = max_edge[newly_node][j] = current_max;
            }
        }
        last_node = newly_node;
    }
    return result;
}
int main()
{
    // freopen("input.txt", "r", stdin); 
    int T;
    scanf("%d", &T);
    while (T--)
    {
        init_and_input();
        double mst = less_prim();
        double max_ratio = 0.0f;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (i == j) continue;
                int pop = population[i] + population[j];
                double non_magic = mst - max_edge[i][j];
                double ratio = (double)pop / non_magic;
                max_ratio = max_ratio > ratio ? max_ratio : ratio;
            }
        }
        printf("%0.2lf\n", max_ratio);
    }
    return 0;
}