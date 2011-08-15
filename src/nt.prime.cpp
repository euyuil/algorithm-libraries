#include <cstdlib>
#include <cstdio>
#include <ctime>

using namespace std;

int prime[10000000];
int *p = prime;

int main(int argc, char *argv[]) {

	clock_t c = clock();
	*(p++) = 2;
	int sr = 1, s = 1, nsr = 2, ns = 4;
	for (int i = 3; i <= 100000000; ++i) {
		if (i >= ns) {
			sr = nsr; s = ns; ++nsr; ns = nsr * nsr;
		}
		int *q = prime;
		for ( ; q < p && *q <= sr; ++q)
			if (!(i % *q)) break;
		if (*q > sr)
			*(p++) = i;
		if (!(i % 10000000))
			printf("%d\n", i);
	}
	printf("Calculated %d primes in %dms\n\n", p - prime, clock() - c);

	printf("The first 100 primes are:\n");
	for (int i = 0; i < 100; ++i)
		printf("%d\n", prime[i]);

	system("pause");
	return EXIT_SUCCESS;
}
