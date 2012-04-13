#ifndef _CG_2_GRAHAM_H_
#define _CG_2_GRAHAM_H_

#include <cg.2.base.h>

/**
 * @brief Graham is an algorithm which can calculate the convex hall out of a
 *        disordered point set.
 * @param typename I Type of input iterator of the points.
 * @param typename O Type of output iterator of the output container.
 * @return The end iterator of the output container. The type of the iterator
 *         is typename O.
 * @date 2011-08-15
 */

template <typename I, typename O> class graham {

private:

    O top;
    vector<bool> used;
    vector<size_t> stk;
    
public:

	/**
	 * @brief Construct a graham object and calculate the convex hall.
	 * @param b The begin iterator for input points. The iterator should be
	 *          bidirectioanl ierator.
	 * @param e The end iterator for input points. The iterator should be
	 *          bidirectional iterator.
	 * @param o The output iterator. This iterator should be random access
	 *          iterator and bidirectional iterator.
	 * @date 2011-08-15
	 */

    graham(I b, I e, O o) : top(o) {
        sort(b, e, compare); I it;
        size_t i = 0, n = e - b; int k = 0;
        used.resize(n); stk.reserve(n);

        for (it = b; i < 2 && it != e; ++i, ++it)
            *(top++) = *it, used[i] = true, stk.push_back(i);
		if (it == e) return; used[0] = false;

        for ( ; it != e; ++it, ++i) {
            while (stk.size() > 1 && ( k = sgn(cross( *(top-1) - *(top-2), *it - *(top-2) )) ) < 0)
				--top, used[stk.back()] = false, stk.pop_back();
			if (k == 0) --top; *(top++) = *it; used[i] = true; stk.push_back(i);
        }

        for (it = e - 1, --i; i < used.size(); --it, --i) {
            if (used[i]) continue;
            while (( k = sgn(cross( *(top-1) - *(top-2), *it - *(top-2) )) ) < 0) --top;
			if (k == 0) --top; if (it == b) break; *(top++) = *it;
        }
    }

	/**
	 * @brief If you cast graham object to the output iterator type, this
	 *        function will be called and the end iterator of the output
	 *        container will be returned.
	 * @return The end iterator of the output container.
	 * @date 2011-08-15
	 */

    operator O() const { return top; }

private:

    static bool compare(const point &a, const point &b) {
        int s = sgn(a.y - b.y);
        if (s) return s < 0;
        return lt(a.x, b.x);
    }
};

#endif /* _CG_2_GRAHAM_H_ */
