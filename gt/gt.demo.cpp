/**
 * @brief Demo source for dinic algorithm. Solution to POJ 1273.
 * @date 2011-08-08
 */

#include "gt.graph.adj.hpp"
#include "gt.nwf.alg.hpp"

#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

typedef gatelib::gt::graph_adj<int, 10> graph_t;
typedef gatelib::gt::nwf::dinic<graph_t> dinic_t;

int main(int argc, char *argv[]) {

	freopen("gt.input.txt", "r", stdin);
	freopen("gt.output.txt", "w", stdout);

	size_t v, e;
	graph_t graph(5);

	cin >> e >> v;
	for (size_t i = 0; i < e; ++i) {
		size_t u, v, w;
		cin >> u >> v >> w;
		--u; --v;
		graph.edge(u, v).value() = w;
	}

	dinic_t dinic(graph, graph.node(0), graph.node(v-1));

	cout << dinic.result() << endl;

	return EXIT_SUCCESS;
}
