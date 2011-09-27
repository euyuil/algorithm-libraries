/***************
ID:   31415926
LANG: C++
TASK: test
DATE: 2011-09-27
***************/

#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

int main(int argc, char *argv[])
{
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);

    int a, b;
    cin >> a >> b;
    cout << a + b << endl;

    return EXIT_SUCCESS;
}
