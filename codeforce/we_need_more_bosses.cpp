#include<iostream>
#include<vector>

using namespace std;

// judge: https://codeforces.com/contest/1000/problem/E

// Constants
const int NOT_VISITED = -1;
const int PROCESSING = 0;
const int VISITED = 1;

// Variables
vector<vector<int> > adj;
vector<vector<int> > treeEdges;
vector<int> backedge_lower_limite_on;
vector<int> backedge_upper_limite_on;
vector<int> state;
vector<int> memo;
int n, m;

void dfs(int v, int parent = -1) {
    state[v] = PROCESSING;
    for(int u: adj[v]) {
        if (state[u] == NOT_VISITED) {
            // Generating a tree
            treeEdges[v].push_back(u);
            dfs(u, v);
        } else if (u != parent and state[u] == PROCESSING) {
            backedge_lower_limite_on[v]++;
            backedge_upper_limite_on[u]++;
        }
    }

    state[v] = VISITED;
}

int covered(int v, int parent = -1) {
    if (memo[v] != -1) return memo[v];
    int res = 0;
    for (int son : treeEdges[v]) {
        if (son != parent) {
            res += covered(son, v);
        }
    }
    res -= backedge_upper_limite_on[v];
    res += backedge_lower_limite_on[v];

    return memo[v] = res;
}

int maximum_boses() {
    int components = 0;
    for(int i = 0; i <= n; i++) {
        if (state[i] == NOT_VISITED) {
            dfs(i);
            components++;
        }
    }

    int bridges = 0;
    for(int i = 0; i <= n; i++) {
        if (covered(i) == 0) bridges++;
    }

    return bridges - components;
}


int main() {
    cin >> n >> m;

    adj       = vector<vector<int> >(n+1);
    treeEdges = vector<vector<int> >(n+1);

    backedge_lower_limite_on = vector<int>(n+1, 0);
    backedge_upper_limite_on = vector<int>(n+1, 0);

    state = vector<int>(n+1, NOT_VISITED);
    memo  = vector<int>(n+1, -1);

    while(m--) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    cout << maximum_boses() << endl;
}