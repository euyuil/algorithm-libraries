/***************
ID:   31415926
LANG: C++
TASK: gift1
DATE: 2011-09-27
***************/

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct person_t {
    int money, remain, obtain;
    person_t() {
        money = remain = obtain = 0;
    }
    operator int() const {
        return remain + obtain - money;
    }
    friend ostream &operator<<(ostream &os, const person_t &per) {
        os << (int)per;
    }
};

typedef map <string, person_t> person_set_t;
typedef vector <string> string_array_t;

int main(int argc, char *argv[])
{
    freopen("gift1.in", "r", stdin);
    freopen("gift1.out", "w", stdout);

    person_set_t person;
    string_array_t name;

    size_t n, t; string subj, obj;
    cin >> n;

    for (size_t i = 0; i < n; ++i) {
        cin >> subj; name.push_back(subj);
        person[subj] = person_t();
    }

    while (cin >> subj) {
        cin >> person[subj].money >> t;
        if (t == 0) {
            person[subj].remain = person[subj].money;
        } else {
            person[subj].remain = person[subj].money % t;
            for (size_t i = 0; i < t; ++i) {
                cin >> obj;
                person[obj].obtain += person[subj].money / t;
            }
        }
    }

    for (size_t i = 0; i < name.size(); ++i)
        cout << name[i] << ' ' << person[name[i]] << endl;

    return EXIT_SUCCESS;
}
