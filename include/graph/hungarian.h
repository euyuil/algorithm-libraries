#include <set> 
#include <vector> 
#include <cstdio> 
#include <cstring> 
#include <algorithm> 
using namespace std;
typedef vector<vector<int> > graph_t;
typedef vector<int> int_array;
typedef set<int> int_set;
const int N = 111111; // Max rank. 
const int M = 100; // Students. 
graph_t graph;
int match_student[N];
int_set rank_occupied;
bool hungarian(int student)
{
    for (int i = 0; i < graph[student].size(); ++i)
    {
        int rank = graph[student][i];
        if (rank_occupied.find(rank) != rank_occupied.end())
            continue; // If rank occupied this time. 
        rank_occupied.insert(rank);
        if (match_student[rank] == -1 || // If the rank is not assigned. 
            hungarian(match_student[rank])) // Or someone can go elsewhere. 
        {
            match_student[rank] = student;
            return true;
        }
    }
    return false;
}
inline void init(int student_count)
{
    graph.clear();
    graph.resize(student_count + 1);
    memset(match_student, -1, sizeof match_student);
}
int main()
{
    // freopen("input.txt", "r", stdin); 
    int T, n;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n); init(n);
        for (int i = 0; i < n; ++i)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            for ( ; x <= y; ++x)
                graph[i].push_back(x);
        }
        int result = 0;
        for (int i = n - 1; i >= 0; --i)
        {
            rank_occupied.clear();
            if (hungarian(i))
                ++result;
        }
        int_array scheme; scheme.reserve(M);
        for (int i = 0; i < N; ++i)
            if (match_student[i] != -1)
                scheme.push_back(match_student[i]);
        sort(scheme.begin(), scheme.end());
        printf("%d\n", result);
        if (!scheme.empty())
            printf("%d", scheme[0] + 1);
        for (int i = 1; i < scheme.size(); ++i)
            printf(" %d", scheme[i] + 1);
        printf("\n");
    }
    return 0;
}