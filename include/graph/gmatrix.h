#ifndef _GRAPH_GMATRIX_H_
#define _GRAPH_GMATRIX_H_

#include <cstring>

using namespace std;

template <int V>
struct gmatrix
{
	int n; // The number of vertices.
	int w[V][V]; // The data of the graph.

	inline void reset() {
		memset(w, 0, sizeof w);
	}
};

#endif /* _GRAPH_GMATRIX_H_ */
