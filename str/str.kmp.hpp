/***********************************************
 * GATeLib :: String Algorithms :: KMP Pattern *
 ***********************************************/

#include <vector>
#include <iterator>

namespace gatelib {

namespace str {

/**
 * @brief A KMP implementation.
 * @date 2011-08-12
 */

template <typename T> class kmp {

public:

    kmp() { }
    kmp(const T &s) : pat(s) { update(); }

public:

    /**
     * @brief Find in range [begin, end) for pattern.
     * @param begin : Iterator to begin.
     * @param end : Iterator to finish.
     * @return The iterator that points to the first char of the matched
     *         string if found, otherwise it will return end.
     */

    template <typename it> it find(it begin, it end) {
        for (size_t i = 0; ; ++begin, ++i) {
            if (i == pat.size()) {
                advance(begin, -i);
                return begin;
            }
            if (begin == end) break;
            while (i != -1 && *begin != pat[i]) i = next[i];
        }
        return end;
    }

    const T &pattern() const { return pat; }
    const T &pattern(const T &s) { pat = s; update(); return pat; }

    void update() {
        next.resize(pat.size() + 1); next[0] = -1; 
        for (size_t i = 0; i < pat.size(); ++i) {
            size_t p = next[i];
            while (p != -1 && pat[i] != pat[p])
                p = next[p];
            next[i + 1] = p + 1;
        }
    }

protected:
    T pat;
    std::vector<size_t> next;
};

} // namespace str

} // namespace gatelib
