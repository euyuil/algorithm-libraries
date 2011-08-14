#include <iostream>
#include <cstdlib>
#include <utility>
#include <vector>
#include <string>
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
				size_t prev, patt; bool danger, target; elem_t elem;
				node() : prev(0), patt(0), danger(false), target(false) { }
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
				tree[0].prev = -1; tree[1].prev = 0; pat.clear();
			}

			void update()
			{
				deque<size_t> qu; qu.push_back(1);
				tree[0].prev = -1;
				while (!qu.empty()) {
					size_t ro = qu.front(); qu.pop_front();
					for (typename node::iterator it = tree[ro].begin(); it != tree[ro].end(); ++it) {
						size_t pr = tree[ro].prev, i = it->second;
						while (pr != -1) { // This code can make some tree node's prev = 0. wtf?!
							if (tree[pr].rval(it->first) != 0) {
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
/*
			void dump() {
				for (size_t i = 0; i < tree.size(); ++i) {
					printf("N%d,P%d:", i, tree[i].prev);
					for (typename node::iterator it = tree[i].begin(); it != tree[i].end(); ++it)
						printf(" %c%d", it->first, it->second);
					printf("\n");
				}
			}
*/
		public:

			template <typename it> void insert(it begin, it end) {
				size_t ro = 1; updated = false;
				pat.push_back(string());
				for ( ; begin != end; ++begin) {
					if (tree[ro].rval(*begin) == 0)
						tree[ro].lval(*begin) = create();
					ro = tree[ro].rval(*begin);
					tree[0].lval(*begin) = 1;
					pat[pat.size()-1] += *begin;
				}
				tree[ro].danger = tree[ro].target = true;
				tree[ro].patt = pat.size() - 1;
			}

			template <typename I> vector< pair<I, size_t> > find(I begin, I end) {
				size_t p = 1; if (!updated) update();
				vector< pair<I, size_t> > v;
				for ( ; begin != end; ++begin) {
					while (p > 0 && tree[p].rval(*begin) == 0)
						p = tree[p].prev;
					p = tree[p].rval(*begin);
					if (p < 1) p = 1;
					if (tree[p].danger) {
						size_t q = p;
						while (q && tree[q].danger) {
							if (tree[q].target)
								v.push_back(make_pair(begin, tree[q].patt));
							q = tree[q].prev;
						}
					}
				}
				return v;
			}

		private:

			size_t create() {
				tree.push_back(node());
				return tree.size() - 1;
			}

		private:

			deque<node> tree;
			bool updated;
			vector<string> pat;
		};

	} // namespace str

} // namespace gatelib

#include <string>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

class puzzle {
public:
    void reset(size_t r, size_t c) {
        memset(matrix, 0, sizeof(matrix));
        rows = r; cols = c;
    }
    size_t fi(char c, size_t i, size_t j) {
        switch (c) {
        case 'A': return rows-j+1;
        case 'B': return sl_rowid(i) - j + 1;
        case 'C': return i;
        case 'D': return bs_rowid(i) + j - 1;
        }
        if (1 & (c - 'A'))
            return fi(c - 4, i, len(i) - j + 1);
        return fi(c - 4, i, rows - j + 1);
    }
    size_t fj(char c, size_t i, size_t j) {
        switch (c) {
        case 'A': return i;
        case 'B': return sl_colid(i) + j - 1;
        case 'C': return j;
        case 'D': return bs_colid(i) + j - 1;
        }
        if (1 & (c - 'A'))
            return fj(c - 4, i, len(i) - j + 1);
        return fj(c - 4, i, rows - j + 1);
    }
    char &operator()(char dir, size_t i, size_t j) {
        return matrix[fi(dir, i, j)][fj(dir, i, j)];
    }
    size_t size(char ch) {
        if ((ch - 'A') % 2)
            return rows + cols - 1;
        if ((ch / 2) % 2)
            return cols;
        return rows;
    }
    size_t len(int j) {
        if (min(rows, cols) <= j && j <= max(rows, cols))
            return min(rows, cols);
        if (j > max(rows, cols))
            return min(rows, cols) - (j - max(rows, cols));
        return j;
    }
protected:
    size_t bs_rowid(size_t i) {
        if (i <= rows) return rows - i + 1;
        return 1;
    }
    size_t bs_colid(size_t i) {
        if (i <= rows) return 1;
        return i - rows + 1;
    }
    size_t sl_rowid(size_t i) {
        if (i <= rows) return i;
        return rows;
    }
    size_t sl_colid(size_t i) {
        if (i <= rows) return 1;
        return i - rows + 1;
    }
protected:
    char matrix[1111][1111];
    size_t rows, cols;
};

puzzle puz;
vector<string> pat;
size_t outx[1111], outy[1111];
char outchar[1111];

int main(int argc, char *argv[]) {

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    size_t l, c, w;
    scanf("%lu%lu%lu", &l, &c, &w);

    puz.reset(l, c);
    for (size_t i = 1; i <= l; ++i)
        for (size_t j = 1; j <= c; ++j)
            cin >> puz('C', i, j);

    gatelib::str::trie<char> tr;
    for (size_t i = 1; i <= w; ++i) {
        string str;
        cin >> str; pat.push_back(str);
        tr.insert(str.begin(), str.end());
    }clog << "Inserted." << endl;

    for (char ch = 'A'; ch <= 'H'; ++ch) {
        for (size_t i = 1; i <= puz.size(ch); ++i) {
            string str;
            for (size_t j = 1; puz(ch, i, j); ++j)
                str += puz(ch, i, j);
			clog << ch << ' ' << i <<  endl;
            vector< pair<string::iterator, size_t> > r;
            r = tr.find(str.begin(), str.end());
            for (size_t k = 0; k < r.size(); ++k) {
                size_t index = size_t(r[k].first - str.begin()) + 1;
                outx[r[k].second] = puz.fi(ch, i, index-pat[r[k].second].size()+1)-1;
                outy[r[k].second] = puz.fj(ch, i, index-pat[r[k].second].size()+1)-1;
				outchar[r[k].second] = ch;
            }
        }
		clog << ch << " matched." << endl;
    }

    for (size_t i = 0; i < pat.size(); ++i)
        cout << outx[i] << ' ' << outy[i] << ' ' << outchar[i] << endl;
    return EXIT_SUCCESS;
}
