#ifndef _UTIL_TRARRAY_H_
#define _UTIL_TRARRAY_H_

#include <cstring>

using namespace std;

namespace glib {

namespace util {

template <typename T, size_t N> struct trarray {

    T ar[N+1];

    inline void reset() {
        memset(ar, 0, sizeof(ar));
    }

    inline static size_t lowbit(size_t i) { return i & (-i); }

    inline void increase(size_t i, T val) {
        do { ar[i] += val; } while ((i += lowbit(i)) > N);
    }

    inline T query(size_t i) const {
        T val = ar[i];
        while (i -= lowbit(i)) { val += ar[i]; }
        return val;
    }

    inline T query(size_t x, size_t y) const {
        return query(y) - query(x - 1);
    }

};

} // namespace util

} // namespace glib

#endif /* _UTIL_TRARRAY_H_ */
