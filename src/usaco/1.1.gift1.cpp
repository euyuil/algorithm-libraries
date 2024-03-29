/***************
ID:   31415926
LANG: C++
TASK: gift1
DATE: 2011-09-27
***************/

#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cstdio>

using namespace std;

struct person_t {
    char name[16];
    int money, remain, obtain;
    person_t() {
        money = remain = obtain = *name = 0;
    }
    operator int() const {
        return remain + obtain - money;
    }
    friend ostream &operator<<(ostream &os, const person_t &per) {
        os << (int)per;
    }
};

struct person_set_t {
    person_t *person; size_t n;
    person_set_t(size_t count) {
        n = count;
        person = new person_t[n];
    }
    ~person_set_t() {
        delete [] person;
    }
    person_t &operator[](const char *name) {
        for (size_t i = 0; i < n; ++i)
            if (!strcmp(name, person[i].name))
                return person[i];
        return *person;
    }
    person_t &operator[](size_t i) {
        return person[i];
    }
};

ifstream fin("gift1.in");
ofstream fout("gift1.out");

int main(int argc, char *argv[])
{
    size_t n, t; char subj[16], obj[16];
    fin >> n; person_set_t person(n);

    for (size_t i = 0; i < n; ++i)
        fin >> person[i].name;

    while (fin >> subj) {
        person_t &one = person[subj];
        fin >> one.money >> t;
        if (t == 0) {
            one.remain = one.money;
        } else {
            one.remain = one.money % t;
            for (size_t i = 0; i < t; ++i) {
                fin >> obj; person_t &other = person[obj];
                other.obtain += one.money / t;
            }
        }
    }

    for (size_t i = 0; i < n; ++i)
        fout << person[i].name << ' ' << person[i] << endl;

    return EXIT_SUCCESS;
}
