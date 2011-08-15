#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

struct node {
	size_t edge[26];
	size_t &operator[](size_t i) {
		clog << "OPERATOR" << endl;
		return edge[i - 'A'];
	}
};

vector<node> tree(1);

size_t create() {
	clog << "CREATE" << endl;
	size_t i = tree.size();
	tree.push_back(node());
	return i;
}

int main(int argc, char *argv[]) {
	size_t n = tree.capacity() + 1;
	for (size_t i = 0; i < n; ++i)
		tree[i]['A'] = create();
	return EXIT_SUCCESS;
}
