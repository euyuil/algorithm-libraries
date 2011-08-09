#ifndef _GT_GRAPH_ADJ_HPP_
#define _GT_GRAPH_ADJ_HPP_

/*****************************************************************/
/* GATeLib :: Graph Theory :: Graph Structure :: Adjacent Matrix */
/*****************************************************************/

#include <cstdlib>
#include <cstring>

namespace gatelib {
namespace gt {


/**
 * @brief Graph implementation of adjacent matrix. First used for network flow
 *        algorithm dinic.
 * @param typename Te - Type of the value of edge.
 * @param size_t In - Max number of the nodes.
 * @date 2011-08-08
 */

template <typename Te, size_t In> class graph_adj {

public:

	class node_t;
	class edge_t;
	class node_it;
	class edge_it;

public:

	class node_t {
	public:
		class outer_it {
		public:
			outer_it() : p(NULL), head(0) { }
			outer_it(node_t *_p, size_t _head) : p(_p), head(_head) {
				if (head >= p->pg->node_count)
					return;
				if (p->pg->matrix[p->index][head] <= 0)
					this->operator++();
			}
		public:
			bool operator==(const outer_it &foo) const {
				return p == foo.p && head == foo.head;
			}
			bool operator!=(const outer_it &foo) const {
				return !this->operator==(foo);
			}
			outer_it &operator++() {
				for (++head ; head < p->pg->node_count; ++head)
					if (p->pg->matrix[p->index][head] > 0)
						return *this;
				return *this;
			}
			edge_t operator*() const { return edge_t(p->pg, p->index, head); }
			edge_t operator->() const { return edge_t(p->pg, p->index, head); }
		protected:
			node_t *p;
			size_t head;
		};
	public:
		node_t(graph_adj *_pg, size_t _index) : pg(_pg), index(_index) { }
	public:
		bool operator==(const node_t &foo) const {
			return pg == foo.pg && index == foo.index;
		}
		bool operator!=(const node_t &foo) const {
			return !this->operator==(foo);
		}
		node_t *operator->() { return this; }
	public:
		outer_it outer_begin() { return outer_it(this, 0); }
		outer_it outer_end() { return outer_it(this, pg->node_count); }
	public:
		int &layer() const { return pg->layer[index]; }
		bool &visited() const { return pg->visited[index]; }
	protected:
		graph_adj *pg;
		size_t index;
	public:
		friend class graph_adj;
	};

	class edge_t {
	public:
		typedef Te value_t;
	public:
		edge_t() : pg(NULL), u(0), v(0) { }
		edge_t(graph_adj *_pg, size_t _u, size_t _v) : pg(_pg), u(_u), v(_v) { }
	public:
		bool operator==(const edge_t &foo) const {
			return pg == foo.pg && u == foo.u && v == foo.v;
		}
		bool operator!=(const edge_t &foo) const {
			return !this->operator==(foo);
		}
		edge_t *operator->() { return this; }
	public:
		Te &value() { return pg->matrix[u][v]; }
		node_t head() { return node_t(pg, v); }
		node_t tail() { return node_t(pg, u); }
		bool exists() { return pg->matrix[u][v]; }
	protected:
		graph_adj *pg;
		size_t u, v;
	};

public:

	class node_it {
	public:
		node_it(graph_adj *_pg, size_t _index) : pg(_pg), index(_index) { }
	public:
		bool operator==(const node_it &foo) const {
			return pg == foo.pg && index == foo.index;
		}
		bool operator!=(const node_it &foo) const {
			return !this->operator==(foo);
		}
		node_it &operator++() { ++index; return *this; }
		node_t operator*() const { return node_t(pg, index); }
		node_t operator->() const { return node_t(pg, index); }
	protected:
		graph_adj *pg;
		size_t index;
	};

	class edge_it { // TODO: Edge iterator.
	};
	
public:

	graph_adj(size_t _node_count) : node_count(_node_count) { reset(); }

public:

	void reset(size_t _node_count) {
		node_count = _node_count;
		memset(matrix, 0, sizeof(matrix));
		memset(visited, 0, sizeof(visited));
		memset(layer, 0, sizeof(layer));
	}

	void reset() { reset(node_count); }
	void reset_visited() { memset(visited, 0, sizeof(visited)); }
	void reset_layer() { memset(layer, 0, sizeof(layer)); }

public:

	node_it node_begin() { return node_it(this, 0); }
	node_it node_end() { return node_it(this, node_count); }

	node_t node(size_t id) { return node_t(this, id); }
	edge_t edge(size_t u, size_t v) { return edge_t(this, u, v); }
	edge_t edge(const node_t &u, const node_t &v) {
		return edge_t(this, u.index, v.index);
	}

protected:

	Te matrix[In][In];
	size_t node_count;
	bool visited[In]; // For algorithm gatelib::gt::nwf::dicnic.
	int layer[In]; // For algorithm gatelib::gt::nwf::dicnic.

public:
	friend class graph_adj::edge_t;
	friend class graph_adj::node_t;
	friend class graph_adj::node_t::outer_it;
};

} /* namespace gt */
} /* namespace gatelib */


#endif /* _GT_GRAPH_ADJ_HPP_*/
