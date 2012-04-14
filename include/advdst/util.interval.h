#ifndef _UTIL_INTERVAL_H_
#define _UTIL_INTERVAL_H_

#include <cstring>

using namespace std;

namespace glib {

namespace util {

/**
 * @brief Implementation of interval tree [X, Y].
 * @todo This code is never tested.
 * @date 2011-08-22
 */

template <int X, int Y> struct interval {

    struct { int x, y; int data; } ns[(Y-X)<<1];

    /**
     * @brief Reset the interval information. Must call this at least once
     *        Before use.
     * @param x Optioanl. Left value of the interval.
     * @param y Optional. Right value of the interval.
     * @param i Optional. The ID of the root node.
     * @date 2011-08-22
     */

    void reset(int x = X, int y = Y, size_t i = 1) {
        if (x > y) return;
        memset(ns[i].data, 0, sizeof(ns[i].data));
        ns[i].x = x; ns[i].y = y; int m = (x + y) >> 1;
        reset(x, m, i << 1); reset(m + 1, y, (i << 1) + 1);
    }

    /**
     * @brief Query an interval of the interval tree.
     * @param x Left value of the interval.
     * @param y Right value of the interval.
     * @param f The callback function.
     * @param i Optional. The ID of the root node.
     * @date 2011-08-22
     */

    template <typename F> void query(int x, int y, F f, size_t i = 1)
    {
        if (x > y) return;
        if (ns[i].x == x && ns[i].y == y) f(this, i);

        int m = (ns[i].x + ns[i].y) >> 1; // L: x ~ m; R: m+1 ~ y.
        if (y <= m)
            query(x, y, f, i << 1);
        else if (x > m)
            query(x, y, f, (i << 1) + 1);
        else {
            query(x, m, f, i << 1);
            query(m + 1, y, f, (i << 1) + 1);
        }
    }

};

} // namespace util

} // namespace glib

#endif /* _UTIL_INTERVAL_H_ */
