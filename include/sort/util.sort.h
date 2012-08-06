#ifndef _UTIL_SORT_H_
#define _UTIL_SORT_H_

template <typename I> void insertion_sort(I b, I e)
{
    I i, j, k = b - 1;
    for (j = b + 1; j != e; ++j) {
        for (i = j - 1; i != k && *i > *j; --i)
            *(i + 1) = *i;
        *(i + 1) = *j;
    }
}

template <typename T, typename I> class merge_sort
{
    merge_sort(I b, I e) {
        if (b + 1 >= e) return;
        I m = (b + e) / 2 + 1;
        merge_sort(b, m);
        merge_sort(m, e);
    }
};

#endif /* _UTIL_SORT_H_ */
