/**
 * @brief Implementation of max heap in CLRS style.
 * @date 2011-08-18
 * @TODO This code is never tested. Be careful to use.
 */

#include <algorithm>
#include <stdexcept>

using namespace std;

template <typename I> inline void max_heapify(I b, I e, I j) {
    I a = b - 1; size_t s = e - b, g;
    size_t i = j - a, l = i << 1, r = (i << 1) + 1;
    if (l <= s && *(a + l) > *(a + i)) g = l; else g = i;
    if (r <= s && *(a + r) > *(a + g)) g = r;
    if (g != i) { swap(*(a + i), *(a + g)); max_heapify(b, e, g); }
}

template <typename I> inline void build_max_heap(I b, I e) {
    size_t s = e - b; I a = b - 1, j = a + (s >> 1);
    for ( ; j != a; --j) max_heapify(b, e, j);
}

template <typename I> inline void heap_sort(I b, I e) {
    build_max_heap(b, e);
    for (--e ; e != b; --e) {
        swap(*b, *e); max_heapify(b, e, b);
    }
}

template <typename T, typename I> inline T heap_maximum(I b, I e) {
    return *b;
}

template <typename T, typename I> inline T heap_extract_max(I b, I e) {
    if (b >= e) throw out_of_range("No element in heap.");
    T m = *b; --e; *b = *e; max_heapify(b, e, b); // *e = m;
    return m;
}

template <typename T, typename I>
inline void heap_increase_key(I b, I e, I j, T k) {
    if (k < *j)
        throw invalid_argument("New key is smaller than old key.");
    I a = b - 1; size_t s = e - b, i = j - a; *j = k;
    while (i > 1 && *(a + (i >> 1)) < *(a + i)) {
        swap(*(a + i), *(a + (i >> 1))); i = i >> 1;
    }
}

template <typename T, typename I>
inline void max_heap_insert(I b, I e, T k) {
    *e = k; ++e; heap_increase_key(b, e, e - 1, k);
}
