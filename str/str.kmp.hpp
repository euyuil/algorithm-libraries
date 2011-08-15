#ifndef _STR_KMP_HPP_
#define _STR_KMP_HPP_

/***********************************************
 * GATeLib :: String Algorithms :: KMP Pattern *
 ***********************************************/

#include <vector>
#include <iterator>

using namespace std;

namespace gatelib {

namespace str {

/**
 * @brief A KMP implementation.
 * @date 2011-08-12
 */

class kmp {

public:

    kmp() { }

    kmp(const string &s) :
        pat(s) { update(); }

    template <typename I> kmp(I b, I e) :
        pat(b, e) { update(); }

public:

    /**
     * @brief Find in range [b, e) for pattern.
     * @param b Iterator to begin.
     * @param e Iterator to finish.
     * @return The iterator that points to the first char of the matched
     *         string if found, otherwise it will return end.
     * @date 2011-08-12
     */

    template <typename I> I find(I b, I e)
    {
        for (size_t i = 0; ; ++b, ++i) {
            if (i == pat.size()) {
                advance(b, -i);
                return b;
            }
            if (b == e)
                break;
            while (i != -1 && *b != pat[i])
                i = next[i];
        }
        return end;
    }

    /**
     * @brief Get the pattern of the KMP object.
     * @return The const reference to the pattern.
     * @date 2011-08-12
     */

    const string &pattern() const { return pat; }

    /**
     * @brief Set the pattern of the KMP object.
     * @param s The new pattern of the KMP object.
     * @return The const reference to the pattern.
     * @date 2011-08-12
     */

    const string &pattern(const string &s) {
        pat = s; update(); return pat; }

private:

    void update()
    {
        next.resize(pat.size() + 1); next[0] = -1;
        for (size_t i = 0; i < pat.size(); ++i) {
            size_t p = next[i];
            while (p != -1 && pat[i] != pat[p])
                p = next[p];
            next[i + 1] = p + 1;
        }
    }

private:
    string pat;
    vector<size_t> next;
};

} // namespace str

} // namespace gatelib

#endif /* _STR_KMP_HPP_ */
