#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>

using namespace std;

const size_t N = 100;

double vert[5 + N << 1];
size_t verc = 0;

struct line_t {
    double x, y1, y2; size_t v1, v2; int flag;
    bool operator<(const line_t &l) const {
        return x < l.x;
    }
};

struct node_t {
    int l, r, flag;
    double area, width, left;
    double height() const {
        return vert[r + 1] - vert[l];
    }
};

struct tree_t
{
    node_t node[5 + N << 1];

    void init(size_t ro, int l, int r)
    {
        node[ro].l = l; node[ro].r = r; node[ro].flag = 0;
        node[ro].area = node[ro].width = 0.0;

        if (l == r) return;

        int m = (l + r) >> 1;
        size_t c = ro << 1;

        init(c, l, m);
        init(c + 1, m + 1, r);
    }

    void insert(size_t ro, int l, int r, double x, int flag)
    {
        if (node[ro].l == l && node[ro].r == r) {
            if (node[ro].flag == 0) {
                node[ro].left = x;
            } else if (node[ro].flag + flag == 0) {
                node[ro].width += x - node[ro].left;
            }
            node[ro].flag += flag;
            return;
        }
        int m = (l + r) >> 1;
        size_t c = ro << 1;
        node[c].flag += node[ro].flag;
        node[c + 1].flag += node[ro].flag;
    }
};

line_t line[5 + N << 1];
size_t linc = 0;

tree_t tree;
size_t trec = 0;

inline void init() {
    memset(line, 0, sizeof(line));
    memset(vert, 0, sizeof(vert)); verc = 0;
}

inline void dump_discrete() {
    clog << "vert:";
    for (size_t i = 0; i < verc; ++i)
        clog << ' ' << vert[i];
    clog << endl;
    clog << "line:";
    for (size_t i = 0; i < linc; ++i) {
        clog << ' ' << '(' << line[i].x << ':';
        clog << line[i].y1 << ',' << line[i].y2 << ';';
        clog << line[i].v1 << ',' << line[i].v2 << '|' << line[i].flag;
        clog << ')';
    }
    clog << endl;
}

int main(int argc, char *argv[])
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    size_t n, T = 0;
    while (scanf("%u", &n) != EOF) {
        if (!n) break; init(); linc = n << 1;
        for (size_t i = 0; i < n; ++i) {
            double x1, y1, x2, y2;
            size_t m = i << 1;
            scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
            line[m].x = x1; line[m + 1].x = x2;
            line[m].y1 = line[m + 1].y1 = y1;
            line[m].y2 = line[m + 1].y2 = y2;
            line[m].flag = 1; line[m + 1].flag = -1;
            vert[verc++] = y1; vert[verc++] = y2;
        }
        sort(vert, vert + verc);
        verc = unique(vert, vert + verc) - vert;
        sort(line, line + linc);
        for (size_t i = 0; i < linc; ++i) {
            line[i].v1 = lower_bound(vert, vert + verc, line[i].y1) - vert;
            line[i].v2 = lower_bound(vert, vert + verc, line[i].y2) - vert;
        }
        // dump_discrete();
        trec = verc - 1;
        tree.init(1, 0, trec - 1);
        for (size_t i = 0; i < linc; ++i)
            tree.insert(1, line[i].v1, line[i].v2 - 1, line[i].x,
                    line[i].flag);
        printf("Test case #%u\n", ++T);
        printf("Total explored area: %0.2f\n\n",
                tree.query(1, 0, trec - 1));
    }
    return EXIT_SUCCESS;
}
