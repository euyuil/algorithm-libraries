#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <ctime>

using namespace std;

const string DEF_INPUT  = "input.txt";
const string DEF_OUTPUT = "output.txt";
const string DEF_MYPR   = "program";
const string DEF_STDPR  = "standard";
const string DEF_GEN    = "generator";

struct PARAM {
	string inp, outp, mypr, stdpr, gen, mout, sout;
	size_t stdms, myms;
};

/**
 * @brief Generate input data using user provided generator.
 * @param p The parameter which indicates the paths of the files.
 */

void generate(const PARAM &p) {
	system(p.gen.c_str());
}

/**
 * @brief Run my program and standard program, then compare their output.
 *        Notice that it will not generate input file.
 * @param p The parameter which indicates the paths of the files.
 * @return The first line number where the two outputs are different, or -1 if
 *         they are the same.
 * @date 2011-08-16
 */

size_t compare(PARAM &p)
{
	clock_t cl = clock();
	system(p.stdpr.c_str());
	p.stdms = clock() - cl;

	remove(p.sout.c_str());
	rename(p.outp.c_str(), p.sout.c_str());

	cl = clock();
	system(p.mypr.c_str());
	p.myms = clock() - cl;

	remove(p.mout.c_str());
	rename(p.outp.c_str(), p.mout.c_str());

	FILE *fs = fopen(p.sout.c_str(), "r");
	FILE *fm = fopen(p.mout.c_str(), "r");

	int cs, cm; size_t r = 0;
	while (true) {
		cs = fgetc(fs); cm = fgetc(fm);
		if (cs != cm) break;
		if (cs == EOF) { r = -1; break; }
		if (cs == '\n') ++r;
	}

	fclose(fs); fclose(fm);
	return r;
}

char buffer[1024];

int main(int argc, char *argv[])
{
	PARAM param;
	param.gen   = DEF_GEN;
	param.mypr  = DEF_MYPR;
	param.stdpr = DEF_STDPR;
	param.inp   = DEF_INPUT;
	param.outp  = DEF_OUTPUT;

	param.sout  = "s_" + param.outp;
	param.mout  = "m_" + param.outp;

	size_t t, l, c = 0;
	printf("How many times would you like to try? ");
	scanf("%lu", &t); printf("\n");

	while (t--) {
		generate(param);
		l = compare(param);
		if (l != -1) {
			sprintf(buffer, "%lu_%lu_", c + 1, l + 1);
			string nu = buffer; ++c;
			rename(param.sout.c_str(), ("diff_" + nu + "s_" + param.outp).c_str());
			rename(param.mout.c_str(), ("diff_" + nu + "m_" + param.outp).c_str());
			rename(param.inp.c_str(), ("diff_" + nu + "i_" + param.inp).c_str());
		}
		printf("%lu case(s) remaining, %lu case(s) found different. std %lums, my %lums.\n",
			t, c, param.stdms, param.myms);
	}

	return EXIT_SUCCESS;
}
