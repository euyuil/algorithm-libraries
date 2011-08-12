#include "str.kmp.hpp"
#include <iostream>
#include <cstdlib>

gatelib::str::kmp<std::string> k;

int main(int argc, char *argv[])
{

    std::string s("abbaabbabaabaaabcacacabaa");
    std::string::iterator it;
    std::cout << "Text: " << s << std::endl << std::endl;

    k.pattern("abaca");
    std::cout << "Pattern: " << k.pattern() << ' ';
    for (it = k.find(s.begin(), s.end()); it != s.end();
         it = k.find(++it, s.end()))
    {
        std::cout << size_t(it - s.begin()) << ' ';
    }
    std::cout << std::endl << std::endl;

    k.pattern("baa");
    std::cout << "Pattern: " << k.pattern() << ' ';
    for (it = k.find(s.begin(), s.end()); it != s.end();
         it = k.find(++it, s.end()))
    {
        std::cout << size_t(it - s.begin()) << ' ';
    }
    std::cout << std::endl << std::endl;

    return EXIT_SUCCESS;
}
