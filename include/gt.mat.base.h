#ifndef _GT_MAT_H_
#define _GT_MAT_H_

#include <cstring>

using namespace std;

namespace glib {

namespace gt {

const size_t mxn = 5000;
const double inf = 9999999.9;

struct gmatrix
{
    double w[mxn][mxn]; size_t n;

    void reset() {
        memset(w, 0, sizeof(w));
    }

	void reset(double val) {
		for (size_t i = 0; i < n; ++i)
			for (size_t j = 0; j < n; ++j)
				w[i][j] = val;
	}
};

} // namespace gt

} // namespace glib

#endif /* _GT_MAT_H_ */
