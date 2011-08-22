#ifndef _GT_LIST_H_
#define _GT_LIST_H_

#include <cstring>

using namespace std;

namespace glib {

namespace gt {

const size_t mxe = 2500000;
const size_t mxn = 5000;

struct glist
{
	struct { double val; size_t ne, he; } ed[mxe];
	size_t fe[mxn], m, n;

	void insert(size_t u, size_t v, double val) {
		ed[m].ne = fe[u]; fe[u] = m;
        ed[m].he = v; ed[m++].val = val;
	}

    void reset() {
        memset(fe, -1, sizeof(fe));
        memset(ed, 0, sizeof(ed));
        m = n = 0;
    }
};

} // namespace gt

} // namespace glib

#endif /* _GT_LIST_H_ */
