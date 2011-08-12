/************************************************
 * GATeLib :: String Algorithms :: Trie Pattern *
 ************************************************/

#include <cstring>
#include <vector>
#include <string>
#include <ctype>
#include <deque>

using namespace std;

namespace gatelib {

namespace str {


/**
 * @brief An implementation for Trie Tree.
 */

class trie {

protected:

    struct node {
        node *prev, oper[26];
        bool danger, target;
        node() : prev(NULL), danger(false), target(false) {
            memset(oper, 0, sizeof(oper));
        }
        node *&operator[](char c) { return oper[std::tolower(c)]; }
        void set_oper(node *p) {
            node **begin = oper, **end = oper + 26;
            for ( ; begin != end; ++begin)
                *begin = p;
        }
        class iterator {
        public:
            iterator() : cur('a') { }
            iterator(node *p) : ptr(p), cur('a') { }
        public:
            iterator &operator++() {
                for (++cur; cur != 'z'+1; ++cur)
                    if ((*p)[cur] != NULL)
                        return *this;
            }
            node *&operator*() const {
                return (*p)[cur];
            }
        protected:
            char cur;
            node *p;
        };
    };

public:

    trie() : updated(false) { }

public:

    void add_pattern(const std::string &p) { pat.push_back(p); updated = false; }
    bool has_pattern(const std::string &p) {
        return find(pat.begin(), pat.end(), p) != pat.end();
    }
    bool erase_pattern(const std::string &p) {
        std::vector<std::string>::iterator it;
        it = find(pat.begin(), pat.end(), p);
        if (it == pat.end()) return false;
        pat.erase(it);
        updated = false;
        return true;
    }

    std::vector<std::string>::const_iterator begin() const { return pat.begin(); }
    std::vector<std::string>::const_iterator end() const { return pat.end(); }

protected:

    node *update_new() {
        nod.push_back(node());
        return &nod.back();
    }

    void update_insert(node &root, const std::string str) {
        std::string::iterator it; node *p = &root;
        for (it = str.begin; it != str.end(); ++it) {
            if ((*p)[*it] == NULL)
                (*p)[*it] = update_new();
            p = p[*it];
        }
        p->danger = p->target = true;
    }

public:

    void update() {
        if (updated) return;

        nod.clear(); nod.push_back(node());
        for (size_t i = 0; i < pat.size(); ++i)
            update_insert(nod[0], pat[i]);

        node v; v.prev = NULL;
        v.set_oper(nod[0]);
        nod[0].prev = &v;

        deque<node *> q;
        q.push_back(nod[0]);
        while (!q.empty()) {
            node *p = q.front(); q.pop_front();
            for (node::iterator
        }

        updated = true;
    }

protected:

    std::vector<std::string> pat;
    std::deque<node> nod;
    bool updated;

};


} // str

} // gatelib
