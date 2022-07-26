#include <iostream>
#include <cstring>
#include <map>
#include <vector>
using namespace std;

typedef struct Vertex {
    vector<int> adj;
    int v_id;
} vertex;

void addEdge(int v1, int v2, vertex **tree);
bool hasCycle_util(int vertex, int n);
bool hasCycle(int n);
void dfs(int vertex);
map<int, vector<int>> transpose(int n);
void result( int n, int size);

vertex *tree;
bool *v_visited;
vector<int> res;
int *vec_c;

int main() {
    int v1 = 0, v2 = 0, n = 0, m = 0, x = 0, y = 0;

    if(scanf("%d %d", &v1, &v2)) { ; }
    if(scanf("%d %d", &n, &m)) { ; }
    if (n < 0 || m < 0) {
        printf("0\n");
        return 0;
    } else {
        tree = new vertex[n];
        vec_c = new int[n];
        memset(vec_c, 0, sizeof(int) * n);
        v_visited = new bool[n];
        memset(v_visited, 0, sizeof(bool) * n);
        // Tree input
        for (int i = 0; i < m; i++) {
            if (cin.peek() == EOF) {
				break;
			}
            if (scanf("%d %d ", &x, &y) == 0) {
                ;
            }
            addEdge(y, x, &tree);
            if (cin.peek() == '\n')
				continue;
        }
        if (hasCycle(n)) {
            printf("0\n");
            return 0;
        }
        memset(vec_c, 0, sizeof(int) * n);
        dfs(v1);

        memset(v_visited, 0, sizeof(bool) * n);
        dfs(v2);

        memset(v_visited, 0, sizeof(bool) * n);
        for (int i = 0; i < n; i++) {
            if (vec_c[i] > 1) {
                res.push_back(i);
            } else {
                continue;
            }
        }
        if (res.size() == 0) {
            printf("-\n");
        } else {
            result(n, res.size());
        }
        return 0;
    }
}

bool hasCycle_util(int vertex, int n) {
    vec_c[vertex] = 1;
    for (int i = 0; i < (int) tree[vertex].adj.size(); i++) {
        if (vec_c[tree[vertex].adj[i] - 1] == 1) {
            return true;
        } else if (vec_c[tree[vertex].adj[i] - 1] == 0 && hasCycle_util(tree[vertex].adj[i] - 1, n)) {
            return true;
        } else {
            continue;
        }
    }
    vec_c[vertex] = 2;

    return false;
}

bool hasCycle(int n) {
    for (int i = 0; i < n; i++) {
        if (vec_c[i] == 0) {
            if (hasCycle_util(i, n)) {
                return true;
            } else {
                continue;
            }
        }
    }
    return false;
}

void addEdge(int v1, int v2, vertex **tree) {
    (*tree)[v2 - 1].v_id = v2;
    (*tree)[v1 - 1].v_id = v1;
    (*tree)[v1 - 1].adj.push_back(v2);
}

map<int, vector<int>> transpose(int n) {
    map<int, vector<int>> transposed;
    for (int i = 0; i < n; i++) {
        if ((int) tree[i].adj.size() == 0 && vec_c[i] > 1) {
            transposed[tree[i].v_id];
        }
        for (int j = 0; j < (int) tree[i].adj.size(); j++) {
            if (vec_c[tree[i].adj[j] - 1] > 1 && vec_c[i] > 1) {
                transposed[tree[i].v_id];
                transposed[tree[i].adj[j]].push_back(tree[i].v_id);
            }
        }
    }
    return transposed;
}

void result(int n, int size) {
    map<int, vector<int>> transposed;
    transposed = transpose(n);
   
    map<int, vector<int>>::iterator i;
    for (i = transposed.begin(); i != transposed.end(); i++) {
        if (i->second.empty()) {
            printf("%d ", i->first);
        }
    }
    printf("\n");
}

void dfs(int vertex) {
    vec_c[vertex - 1] = vec_c[vertex - 1] + 1;
    v_visited[vertex - 1] = true;
    for (int i = 0; i < (int) tree[vertex - 1].adj.size(); i++)
        if (!(v_visited[tree[vertex - 1].adj[i] - 1])) {
            dfs(tree[vertex - 1].adj[i]);
        }
}