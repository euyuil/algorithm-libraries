#ifndef _STR_TRIE_HPP_
#define _STR_TRIE_HPP_

/****************************************
 * GATeLib :: String Algorithms :: Trie *
 ****************************************/

#include <iterator>
#include <cstring>
#include <vector>
#include <string>
#include <queue>

using namespace std;

namespace gatelib {

namespace str {

/**
 * @brief Trie is an algorithm that can match multiple patterns from a
 *        given paragraph.
 * @date 2011-08-14
 */

class trie {

private:

    /**
     * @brief A structure of node that supports 26 letters' alphabet.
     * @date 2011-08-14
     */

	struct node {
		size_t prev, paid, edge[26];
		bool danger, target;
		node() { memset(this, 0, sizeof(*this)); }
		size_t &operator[](char a) { return edge[a - 'A']; }
	};

private:

	bool updated;
	vector<node> tree;
	vector<string> pats;

public:

	trie() { reset(512, 32); }

private:

	void reset(size_t tresv, size_t paresv)
    {
		tree.resize(2); pats.clear(); updated = false;
		tree.reserve(tresv); pats.reserve(paresv);
		for (char c = 'A'; c <= 'Z'; ++c)
			tree[0][c] = 1;
	}

	size_t create() {
		tree.push_back(node());
		return tree.size() - 1;
	}

	void update()
    {
		queue<size_t> qu; qu.push(1);
		while (!qu.empty()) {
			size_t r = qu.front(); qu.pop();
			for (char c = 'A'; c <= 'Z'; ++c) {
				if (tree[r][c] == 0) continue;
				size_t p = tree[r].prev;
				while (tree[p][c] == 0)
					p = tree[p].prev;
				tree[tree[r][c]].prev = tree[p][c];
				qu.push(tree[r][c]);
			}
		}
		updated = true;
	}

public:

    /**
     * @brief Return the i-th pattern of the trie object.
     * @return The i-th pattern.
     */

	const string &pattern(size_t i) {
		return pats[i];
	}

    /**
     * @brief Insert a pattern string to the trie object.
     * @param b The begin iterator to the string that being inserted.
     * @param e The end iterator to the string.
     * @return The index of the pattern string in the trie object. You can
     *         use this index to get the pattern string.
     */

	template <typename I> size_t insert(I b, I e)
    {
		size_t r = 1, paid = pats.size();
		updated = false; pats.push_back(string());
		for ( ; b != e; ++b) {
			pats[paid] += *b;
			if (tree[r][*b] == 0) {
                size_t t = create(); // If you don't use a temp var,
				tree[r][*b] = t;     // it will cause seg fault in g++.
            }
			r = tree[r][*b];
		}
		tree[r].danger = tree[r].target = true;
		tree[r].paid = paid;
		return paid;
	}

    /**
     * @brief Matches a paragraph with the trie patterns.
     * @param b The begin iterator to the paragraph.
     * @param e The end iterator to that paragraph.
     * @param f The callback function. When a pattern was found match with
     *          the paragraph, this callback function will be called. The
     *          function should be like bool f(I i, size_t s). Each invoke
     *          of this function means a pattern indexed s was found in the
     *          paragraph with the position iterator i in range [b, e). You
     *          should notice that this function should have return value
     *          whose type is bool. When the function return true, the
     *          matching progress will be ended even if there may be more
     *          patterns can be matched in future.
     * @return The number of matches. Or you can say the number of times
     *         that function f was called.
     * @date 2011-08-14
     */

	template <typename I, typename F> size_t matches(I b, I e, F f)
    {
		if (!updated) update();
		size_t p, r = 1, c = 0;
		for ( ; b != e; ++b) {
			while (r > 0 && tree[r][*b] == 0)
				r = tree[r].prev;
			r = p = tree[r][*b];
			while (tree[p].danger) {
				if (tree[p].target) {
					I i = b; ++c;
					advance(i, 1 - pats[tree[p].paid].size());
					if (f(i, tree[p].paid)) return c;
				}
				p = tree[p].prev;
			}
		}
		return c;
	}
};

} // namespace str

} // namespace gatelib

#endif /* _STR_TRIE_HPP_ */
