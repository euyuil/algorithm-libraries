#include <cg.2.base.h>

namespace glib {

namespace cg {

    /**
     * @brief For Each Segment of POlygon.
     * @param s Output segment.
     * @param i Iterator of the first end-point of the segment.
     * @param b The begin iterator of the polygon.
     * @param e The end iterator of the polygon.
     * @return True if succeeded.
     */

    template <typename I> bool fespo(line &s, I &i, I b, I e)
    {
        if (i == e) return false;
        I j = i; ++j;
        if (j == e) s = line(*i, *b);
        else s = line(*i, *j);
        i = j; return true;
    }

}

}
