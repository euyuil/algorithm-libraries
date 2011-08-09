#include <queue>
#include <map>

using namespace std;

namespace gatelib {

class trie {

public:

	class node {
	public:
		node() :
			edgeOthers(NULL),
			previous(NULL),
			dangerous(false)
		{ }
	public:
		node &child(char ch) {
			map<char, node>::iterator it;
			it = edges.find(ch);
			if (it == edges.end() && edgeOthers)
				return *edgeOthers;
			return it->second;
		}
		/* bool has_child(char ch) {
			if (edgeOthers)
				return true;
			map<char, node>::iterator it;
			it = edges.find(ch);
			if (it == edges.end())
				return false;
			return true;
		} */
		iterator find_child(char ch) {
			map<char, node>::iterator it;
			it = edges.find(ch);
			if (it == edges.end() && edgeOthers)
				return edgeOthers;
			return &it->second;
		}
	protected:
		map<char, node> edges;
		node *edgeOthers; // Needs destruction? Probably not.
		node *previous;
		bool dangerous;
	};

	typedef node *iterator, *pointer;
	typedef const node *const_iterator, *const_pointer;

public:

	trie() {
		zero.edgeOthers = &root;
		root.previous = &zero;
	}

public:

	iterator insert(const char *str) {
		node *p = &root;
		for ( ; *str; ++str)
			p = p->child(*str);
		p->dangerous = true;
		return p;
	}

	trie &build() {
		queue<node *> q;
		q.push(&root);
		while (!q.empty()) {
			node *parent = q.front(); q.pop();
			map<char, node>::iterator it;
			for (it = parent->begin(); it != parent->end(); ++it) {
				node *previous = it->second.previous;
				while (previous) {
					pointer iu = previous->find_child(it->first);
					if (iu != previous->edges.end()) {
						it->second.previous = &iu->second;
						it->second.dangerous = iu->second.dangerous;
						break;
					}
					previous = previous->previous;
				}
				q.push(&it->second);
			}
		}
	}

	iterator search(const char *str) {
		const_pointer const_this = this;
		const_iterator it = const_this->search(str);
		return const_cast<iterator>(it);
	}

	const_iterator search(const char *str) const {
		pointer p = &root;
		map<char, node>::iterator it;
		while (*str && (it = p->edges.find(*str)) != p->edges.end()) {
			p = &it->second;
			++str;
		}
		if (!*str)
			return p;
		return NULL;
	}

	iterator begin() {
		return &root;
	}

	const_iterator begin() const {
		return &root;
	}

	iterator end() {
		return NULL;
	}

	const_iterator end() const {
		return NULL;
	}

protected:

	node zero, root;
};

} /* namespace gatelib */
