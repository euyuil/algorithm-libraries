#include <iterator>
#include <cstring>
#include <vector>
#include <string>
#include <queue>

using namespace std;

class trie {
private:
    struct node {
        size_t prev, paid, edge[26];
        bool danger, target;
        node() { memset(this, 0, sizeof(*this)); }
        size_t &operator[](char a) { return edge[a - 'A']; }
    };
private:
    bool updated;
    vector<node> tree;
    vector<string> pats;
public:
    trie() { reset(512, 32); }
private:
    void reset(size_t tresv, size_t paresv) {
        tree.resize(2); pats.clear(); updated = false;
        tree.reserve(tresv); pats.reserve(paresv);
        for (char c = 'A'; c <= 'Z'; ++c)
            tree[0][c] = 1;
    }
    size_t create() {
        tree.push_back(node());
        return tree.size() - 1;
    }
public:
    template <typename I> size_t insert(I b, I e) {
        size_t r = 1, paid = pats.size();
        updated = false; pats.push_back(string());
        for ( ; b != e; ++b) {
            pats[paid] += *b;
            if (tree[r][*b] == 0)
                tree[r][*b] = create();
            r = tree[r][*b];
        }
        tree[r].danger = tree[r].target = true;
        tree[r].paid = paid;
        return paid;
    }
    void update() {
        if (updated) return;
        queue<size_t> qu; qu.push(1);
        while (!qu.empty()) {
            size_t r = qu.front(); qu.pop();
            for (char c = 'A'; c <= 'Z'; ++c) {
                if (tree[r][c] == 0) continue;
                size_t p = tree[r].prev;
                while (tree[p][c] == 0)
                    p = tree[p].prev;
                tree[r].prev = tree[p][c];
            }
        }
        updated = true;
    }
    template <typename I, typename F> size_t matches(I b, I e, F f) {
        // typedef bool F(I i, const string &p);
        size_t p, r = 1, co = 0;
        for ( ; b != e; ++b) {
            while (tree[r][*b] == 0)
                r = tree[r].prev;
            r = p = tree[r][*b];
            while (tree[p].danger) {
                if (tree[p].target) {
                    I i = b; ++co;
                    advance(i, 1 - pats[tree[p].paid].size());
                    if (f(i, pats[tree[p].paid])) return co;
                }
                p = tree[p].prev;
            }
        }
        return co;
    }
};
