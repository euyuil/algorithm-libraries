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
	const string &pattern(size_t i) {
		return pats[i];
	}
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
		queue<size_t> qu; qu.push(1);
		while (!qu.empty()) {
			size_t r = qu.front(); qu.pop();
			for (char c = 'A'; c <= 'Z'; ++c) {
				if (tree[r][c] == 0) continue;
				size_t p = tree[r].prev;
				while (tree[p][c] == 0)
					p = tree[p].prev;
				tree[tree[r][c]].prev = tree[p][c];
				qu.push(tree[r][c]);
			}
		}
		updated = true;
	}
	template <typename I, typename F> size_t matches(I b, I e, F f) {
		// typedef bool F(I i, size_t p);
		if (!updated) update();
		size_t p, r = 1, co = 0;
		for ( ; b != e; ++b) {
			while (r > 0 && tree[r][*b] == 0)
				r = tree[r].prev;
			r = p = tree[r][*b];
			while (tree[p].danger) {
				if (tree[p].target) {
					I i = b; ++co;
					advance(i, 1 - pats[tree[p].paid].size());
					if (f(i, tree[p].paid)) return co;
				}
				p = tree[p].prev;
			}
		}
		return co;
	}
};

#include <string>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <ctime>

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
        if ((ch - 'A') & 1) return rows + cols - 1;
        if ((ch / 2)  & 1) return cols;
        return rows;
    }
    size_t len(size_t j) {
		size_t mi = min(rows, cols), ma = max(rows, cols);
        if (mi <= j && j <= ma) return mi;
        if (j > ma) return mi - (j - ma);
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
public:
    char matrix[1111][1111];
    size_t rows, cols;
};

puzzle puz;
size_t outx[1111], outy[1111];
char outchar[1111];

class addone {
public:
	addone(char *b, char d, size_t t) :
		begin(b), direction(d), lineid(t) { }
	bool operator()(char *it, size_t id) {
		size_t index = size_t(it - begin) + 1;
		outx[id] = puz.fi(direction, lineid, index)-1;
		outy[id] = puz.fj(direction, lineid, index)-1;
		outchar[id] = direction;
		return false;
	}
private:
	char *begin;
	char direction;
	size_t lineid;
};

char buffer[9999];

int main(int argc, char *argv[]) {

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    size_t l, c, w;
    scanf("%lu%lu%lu", &l, &c, &w);

    puz.reset(l, c);
    for (size_t i = 1; i <= l; ++i)
        scanf("%s", puz.matrix[i] + 1);

    trie tr;
    for (size_t i = 1; i <= w; ++i) {
		scanf("%s", buffer);
		char *bend = buffer + strlen(buffer);
        tr.insert(buffer, bend);
    }

    for (char ch = 'A'; ch <= 'H'; ++ch) {
        for (size_t i = 1; i <= puz.size(ch); ++i) {
            char *bend = buffer;
            for (size_t j = 1; puz(ch, i, j); ++j)
                *(bend++) = puz(ch, i, j);
			*bend = '\0';
            tr.matches(buffer, bend, addone(buffer, ch, i));
        }
    }

    for (size_t i = 0; i < w; ++i)
        cout << outx[i] << ' ' << outy[i] << ' ' << outchar[i] << endl;

    return EXIT_SUCCESS;
}
