#include "str.trie.simp.hpp"
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
    }

    for (char ch = 'A'; ch <= 'H'; ++ch) {
        for (size_t i = 1; i <= puz.size(ch); ++i) {
            string str;
            for (size_t j = 1; puz(ch, i, j); ++j)
                str += puz(ch, i, j);
            pair< string::iterator, vector<size_t> > r;
            r = tr.find(str.begin(), str.end());
            if (!r.second.empty()) {
                size_t index = size_t(r.first - str.begin()) + 1;
                vector<size_t> v = r.second;
                for (size_t j = 0; j < v.size(); ++j) {
                    outx[v[j]] = puz.fi(ch, i, index-pat[v[j]].size()+1)-1;
                    outy[v[j]] = puz.fj(ch, i, index-pat[v[j]].size()+1)-1;
                    outchar[v[j]] = ch;
                }
            }
        }
    }

    for (size_t i = 0; i < pat.size(); ++i)
        cout << outx[i] << ' ' << outy[i] << ' ' << outchar[i] << endl;
    return EXIT_SUCCESS;
}
