#include <iostream>
#include <cstdlib>
#include <queue>
#include <map>
#include <set>

using namespace std;

#ifndef foreach
#define foreach(i,c) for (__typeof((c).begin()) i = \
    (c).begin(); i != (c).end(); ++i)
#endif

namespace gatelib {

namespace str {

template <typename T> class trie {

private:

    class node {
    public:
		typedef map<T, size_t> elem_t;
		typedef typename elem_t::iterator iterator;
		typedef typename elem_t::const_iterator const_iterator;
        size_t prev; bool danger, target; elem_t elem;
        node() : prev(0), danger(false), target(false) { }
        size_t rval(T c) const {
            const_iterator it = elem.find(c);
            if (it == elem.end()) return 0;
            return it->second;
        }
		size_t &lval(T c) { return elem[c]; }
		const_iterator begin() const { return elem.begin(); }
		const_iterator end() const { return elem.end(); }
		iterator begin() { return elem.begin(); }
		iterator end() { return elem.end(); }
    };

public:

    trie() : updated(false) { reset(); }

public:

    void reset()
    {
        tree.clear(); tree.resize(2); updated = false;
        tree[0].prev = -1; tree[1].prev = 0;
    }

    void update()
    {
        deque<size_t> qu; qu.push_back(1);
		tree[0].prev = -1;
        while (!qu.empty()) {
            size_t ro = qu.front(); qu.pop_front();
            for (node::iterator it = tree[ro].begin(); it != tree[ro].end(); ++it) {
                size_t pr = tree[ro].prev, i = it->second;
                while (pr != -1) {
                    if (tree[pr].rval(it->first) != -1) {
                        tree[i].prev = tree[pr].rval(it->first);
                        tree[i].danger = tree[i].danger || tree[tree[i].prev].danger;
                        break;
                    } else pr = tree[pr].prev;
                }
                qu.push_back(it->second);
            }
        }
        updated = true;
    }

    void dump() {
        for (size_t i = 0; i < tree.size(); ++i) {
            printf("N%d,P%d:", i, tree[i].prev);
            for (node::iterator it = tree[i].begin(); it != tree[i].end(); ++it)
				printf(" %c%d", it->first, it->second);
			printf("\n");
        }
    }

public:

	template <typename it> void insert(it begin, it end) {
		size_t ro = 1; updated = false;
		for ( ; begin != end; ++begin) {
            if (tree[ro].rval(*begin) == 0)
                tree[ro].lval(*begin) = create();
            ro = tree[ro].rval(*begin);
            tree[0].lval(*begin) = 1;
        }
        tree[ro].danger = tree[ro].target = true;
    }

    template <typename I> bool matches(I begin, I end) {
        size_t p = 1; if (!updated) update();
        for ( ; begin != end; ++begin) {
            while (p > 0 && tree[p].rval(*begin) == 0)
                p = tree[p].prev;
			p = tree[p].rval(*begin);
			if (p < 1) p = 1;
            if (tree[p].danger) return true;
        }
        return false;
    }

private:

    size_t create() {
        tree.push_back(node());
        return tree.size() - 1;
    }

private:

    deque<node> tree;
    bool updated;
};

} // namespace str

} // namespace gatelib
