/***************
ID:   31415926
LANG: C++
TASK: ride
DATE: 2011-09-27
***************/

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>

using namespace std;

inline int calc(const string &str)
{
    int result = 1;
    for (size_t i = 0; i < str.size(); ++i)
        result *= str[i] - 'A' + 1;
    return result % 47;
}

int main(int argc, char *argv[])
{
    freopen("ride.in", "r", stdin);
    freopen("ride.out", "w", stdout);

    string foo, bar;
    cin >> foo >> bar;
    if (calc(foo) == calc(bar))
        cout << "GO" << endl;
    else
        cout << "STAY" << endl;

    return EXIT_SUCCESS;
}
