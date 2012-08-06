#ifndef _GT_NWF_ALG_HPP_
#define _GT_NWF_ALG_HPP_

/*********************************************************
 * GATeLib :: Graph Theory :: Network Flow :: Algorithms *
 *********************************************************/

#include <queue>
#include <deque>

#include <cassert>

namespace gatelib {
namespace gt {
namespace nwf {


/**
 * @brief Class for algorithm dinic. It is used for calculating the maximum
 *        flow of a network.
 * @date 2011-08-08
 */

template <class Tg> class dinic {

public:

	/**
	 * @brief Construct a dinic algorithm.
	 * @param g - Graph object reference.
	 * @param source - The source node of the graph.
	 * @param sink - The sink node of the graph.
	 * @date 2011-08-08
	 */

	dinic(Tg &g, typename Tg::node_t source, typename Tg::node_t sink) : res(0)
	{
		std::deque<Tg::node_t> dq;
		while (count_layers(g, source, sink))
		{
			dq.push_back(source);
			g.reset_visited();
			source.visited() = true;
			while (!dq.empty())
			{
				Tg::node_t u = dq.back();
				if (u == sink)
				{
					assert(dq.size() > 1);
					Tg::edge_t edge_min = g.edge(dq[0], dq[1]);
					for (size_t i = 2; i < dq.size(); ++i) {
						Tg::edge_t edge = g.edge(dq[i-1], dq[i]);
						if (edge.exists() && edge_min.value() > edge.value())
							edge_min = edge;
					}

					Tg::edge_t::value_t value = edge_min.value(); res += value;
					for (size_t i = 1; i < dq.size(); ++i) {
						Tg::edge_t positive = g.edge(dq[i-1], dq[i]);
						Tg::edge_t negative = g.edge(dq[i], dq[i-1]);
						positive.value() -= value;
						negative.value() += value;
					}

					Tg::node_t tail = edge_min.tail();
					while (!dq.empty() && (dq.back() != tail))
						dq.pop_back();
				}
				else
				{
					Tg::node_t::outer_it it = u.outer_begin();
					for ( ; it != u.outer_end(); ++it)
					{
						Tg::node_t v = it->head();
						if (u.layer() + 1 != v.layer() || v.visited()) continue;
						v.visited() = true; // It's not efficient... Use an iterator stack? Or pair?
						dq.push_back(v);
						break;
					}
					if (it == u.outer_end())
						dq.pop_back();
				}
			}
		}
	}

public:

	/**
	 * @brief Get the dinic algorithm result.
	 * @return The result.
	 * @date 2011-08-08
	 */

	typename Tg::edge_t::value_t result() const { return res; }

protected:

	bool count_layers(Tg &g, typename Tg::node_t source, typename Tg::node_t sink)
	{
		Tg::node_it s = g.node_begin();
		Tg::node_it e = g.node_end();

		for (Tg::node_it it = s; it != e; ++it)
			it->layer() = -1;

		source.layer() = 0;
		std::queue<Tg::node_t> qu; qu.push(source);
		while (!qu.empty())
		{
			Tg::node_t u = qu.front(); qu.pop();
			for (Tg::node_t::outer_it it = u.outer_begin();
				it != u.outer_end(); ++it)
			{
				Tg::node_t v = it->head();
				if (v.layer() != -1)
					continue;
				v.layer() = u.layer() + 1;
				if (v == sink) return true;
				else qu.push(v);
			}
		}
		return false;
	}

protected:

	typename Tg::edge_t::value_t res;
};

class hungarian {
};


} /* namespace nwf */
} /* namespace gt */
} /* namespace gatelib */

#endif /* _GT_NWF_ALG_HPP_ */
