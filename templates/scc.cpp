#include<iostream>
#include<vector>

using namespace std;

// Contants
#define NOT_VISITED -1
#define PROCESSING 0
#define VISITED 1
#define NO "NO"
#define YES "YES"

// Variables
vector<vector<int> > adj;
vector<vector<int> > adj_T;
vector<int> stack;
vector<int> state;
vector<int> strong_component;
int n;

void dfs(int v, vector<vector<int> > &adj) {
    for(int u: adj[v]) {
        if(state[u] == NOT_VISITED) {
            strong_component[u] = strong_component[v];
            dfs(u, adj);
        }
    }
    state[v] = VISITED;
    stack.push_back(v);
}

void find_strong_components() {
    for(int i = 0; i < n+1; i++) {
        if(state[i] == NOT_VISITED) {
            dfs(i, adj);
        }
    }

    state            = vector<int>(n+1, NOT_VISITED);
    strong_component = vector<int>(n+1, 0);
    int count = 0;

    while(!stack.empty()) {
        int v = stack.back(); stack.pop_back();
        if(state[v] == NOT_VISITED) {
            count++;
            strong_component[v] = count;
            dfs(v, adj_T);
        }
    }
}