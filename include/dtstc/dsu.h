#ifndef _DTSTC_DSU_H_
#define _DTSTC_DSU_H_

template <int N>
struct dsu_t
{
    int r[N];

    inline void reset() {
        for (int i = 0; i < N; ++i)
            r[i] = i;
    }

    inline int root(int i) {
        return r[i] = (i == r[i] ? i : root(r[i]));
    }

    inline void join(int i, int j) {
        r[root(i)] = root(j);
    }
};

#endif /* _DTSTC_DSU_H_ */
