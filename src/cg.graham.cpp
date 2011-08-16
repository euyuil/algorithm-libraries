#include "../include/cg.2.h"

#include <ctime>
#include <vector>
#include <cstdlib>
#include <iostream>

// #define GENERATE

using namespace std;

typedef vector<point>::iterator iter;

int main(int argc, char *argv[]) {

#ifdef GENERATE

	freopen("output.txt", "r", stdin);
	freopen("input.txt", "w", stdout);

	srand((unsigned int)time(NULL));

	for (size_t i = 0; i <= 16; ++i, cout << endl) {
		cout << i << endl;
		for (size_t j = 0; j < i; ++j)
			cout << rand() % 199 - 99 << ' ' << rand() % 199 - 99 << endl;
	}

#else

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	size_t n; vector<point> p, r;
	for ( ; cin >> n; cout << endl) {
		p.resize(n); r.resize(n);
		for (size_t i = 0; i < n; ++i)
			cin >> p[i].x >> p[i].y;
		graham<iter, iter> g(p.begin(), p.end(), r.begin());
		r.resize((iter)g - r.begin());
		for (size_t i = 0; i < r.size(); ++i)
			cout << r[i].x << ' ' << r[i].y << endl;
	}

#endif /* GENERATE */

	return EXIT_SUCCESS;
}
