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
        typedef map<T, node *> elem_t;
        typedef typename elem_t::iterator iterator;
        node *prev; bool danger, target; elem_t elem;
        node() : prev(NULL), danger(false), target(false) { }
        node *rval(T c) const {
            iterator it = elem.find(c);
            if (it == elem.end()) return NULL;
            return *it;
        }
        node *&lval(T c) { return elem[c]; }
        iterator begin() { return elem.begin(); }
        iterator end() { return elem.end(); }
    };

public:

    void update()
    {
        tree.clear(); tree.resize(2);
        foreach (it, alphabet)
            tree[0].lval(*it) = &tree[1];
        tree[0].prev = NULL;
        tree[1].prev = &tree[0];

        deque<node *> qu;
        while (!qu.empty()) {
            node *root = qu.front(); qu.pop_front();
            foreach (it, *root) {
                node *prev = root->prev;
                while (prev) {
                    if (prev->rval(it->first) != NULL) {
                        it->second->prev = prev.rval(it->first);
                        it->second->danger = it->second->prev->danger;
                        break;
                    } else prev = prev->prev;
                }
                qu.push_back(it->second);
            }
        }
    }

public:

    template <typename I> void insert(node *root, I begin, I end) {
        for ( ; begin != end; ++begin) {
            if (root->rval(*begin) == NULL)
                root->lval(*begin) = create();
            root = root->rval(*begin);
            alphabet.add(*begin);
        }
        root->danger = root->target = true;
    }

    template <typename I> bool matches(I begin, I end) {
        node *p = &tree[1];
        for ( ; begin != end; ++begin) {
            while (p->rval(*begin) == NULL)
                p = p->prev;
            p = p->rval(*begin);
            if (p->danger) return true;
        }
        return false;
    }

private:

    node *create() {
        tree.push_back(node());
        return &tree.back();
    }

private:

    deque<node> tree;
    set<T> alphabet;
};

} // namespace str

} // namespace gatelib
