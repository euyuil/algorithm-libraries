#ifndef _GRAPH_GLIST_H_
#define _GRAPH_GLIST_H_

#include <cstring>

using namespace std;

template <int V, int E>
struct glist
{
	int fe[V]; // First edge of a vertex.
	int he[E]; // Head vertex of an edge.
	int ne[E]; // Next edge of an edge.
	int n; // Number of vertices, maintained by users.
	int m; // Number of edges, maintained by this class.

	inline void reset() {
		memset(fe, -1, sizeof fe);
	}

	inline void insert(int u, int v) {
		ne[m] = fe[u];
		he[m] = v;
		fe[u] = m++;
	}
};

#endif /* _GRAPH_GLIST_H_ */
