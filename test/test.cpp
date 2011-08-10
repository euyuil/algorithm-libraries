#include <vector>
#include <string>
#include <queue>
#include <ctime>
#include <cstring>
#include <iostream>

using namespace std;

class MagicalGirlLevelTwoDivTwo {
protected:
	template <typename T, size_t I>
	class NegativeIndexMatrix {
	protected:
		T matrix[2*I][2*I];
	public:
		T &operator()(long i, long j) {
			return matrix[i+I][j+I];
		}
		void reset() {
			memset(matrix, 0, sizeof(matrix));
		}
	};
	NegativeIndexMatrix<bool, 1000> visited;

	struct point {
		int x, y;
		point(int _x, int _y) : x(_x), y(_y) { }
	};

	typedef pair<int, point> plan;

	friend bool operator<(const plan &a, const plan &b) {
		return a.first < b.first;
	}

	vector<point> jt;
	priority_queue<plan> pq;

protected:

	void make(const vector<int> &t) {
		for (size_t i = 0; i < t.size(); ++i) {
			jt.push_back(point( t[i], 1));
			jt.push_back(point( t[i],-1));
			jt.push_back(point(-t[i], 1));
			jt.push_back(point(-t[i],-1));
			jt.push_back(point( 1, t[i]));
			jt.push_back(point(-1, t[i]));
			jt.push_back(point( 1,-t[i]));
			jt.push_back(point(-1,-t[i]));
		}
	}

	static int abs(int a) {
		return a < 0 ? -a : a;
	}

public:

	string isReachable(vector<int> t, int x, int y) {

		visited.reset(); make(t);
		pq.push(plan(0, point(0, 0)));

		clock_t ticks = clock();
		while (!pq.empty())
		{
			if (clock() - ticks > 950) break;

			plan p = pq.top(); pq.pop();
			if (p.second.x == x && p.second.y == y)
				return string("YES");

			for (size_t i = 0; i < jt.size(); ++i) {
				int tx = p.second.x + jt[i].x;
				int ty = p.second.y + jt[i].y;
				if (visited(tx, ty)) continue;
				visited(tx, ty) = true;
				pq.push(plan(-(abs(tx-x) + abs(ty-y)), point(tx, ty)));
			}
		}
		return string("NO");
	}
};

MagicalGirlLevelTwoDivTwo m;

int main(int argc, char *argv[]) {
	vector<int> t;
	t.push_back(29);
	cout << m.isReachable(t, 29, 0) << endl;
	return EXIT_SUCCESS;
}
