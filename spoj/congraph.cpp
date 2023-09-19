#include <iostream>
#include <vector>

using namespace std;

// judge: https://www.spoj.com/problems/CONGRAPH/

int n, m;
vector<vector<int> > edges;
vector<int> state;

const int NOT_VISITED = -1;
const int PROCESSING = 0;
const int VISITED = 1;

// O(n + m)
void dfs(int v) {
    state[v] = PROCESSING;
    for(int u: edges[v]) {
        if(state[u] == NOT_VISITED) {
            dfs(u);
        }
    }
    state[v] = VISITED;
}

// O(n + m)
int number_of_roads() { 
    int counter = 0;
    for(int i = 0; i <= n; i++) {
        if (state[i] == NOT_VISITED) {
            dfs(i);
            counter++;
        }
    }
    return counter - 1;
}

int main() {
    cin >> n >> m;

    edges = vector<vector<int> >(n, vector<int>(0));
    state = vector<int>(n, NOT_VISITED);

    while(m--) {
        int u, v; cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }

    cout << number_of_roads() << endl;
}