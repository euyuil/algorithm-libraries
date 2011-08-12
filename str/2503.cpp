#include "str.trie.simp.hpp"
#include <cstdlib>
#include <cstring>
#include <cstdio>

using namespace std;

char buffer[1024];
gatelib::str::trie<char> tr;

int main(int argc, char *argv[]) {
    printf("Input patterns, without spaces, ends with 0: \n");
    while (scanf("%s", buffer)) {
        if (buffer[0] == '0') break;
        tr.insert(buffer, buffer + strlen(buffer));
    }
    printf("\nInput strings, without spaces, ends with 0: \n");
    while (scanf("%s", buffer)) {
        if (buffer[0] == '0') break;
        printf("%s\n", tr.matches(buffer, buffer + strlen(buffer)) ? "Found!" : "Not found!");
    }
    return EXIT_SUCCESS;
}
