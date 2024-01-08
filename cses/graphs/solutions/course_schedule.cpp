#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

#define IMP "IMPOSSIBLE"
#define NOT_VISITED -1
#define VISITING 0
#define VISITED 1

int n, m;
vector<vector<int> > adj;
vector<int> stack, state;
bool cycle = false;

void dfs(int v) {
    state[v] = VISITING;
    for(int u: adj[v]) {
        if (state[u] == NOT_VISITED) dfs(u);
        else if (state[u] == VISITING) cycle = true;
    }
    stack.push_back(v);
    state[v] = VISITED;
}

void topological_sort() {
    for(int i = 1; i <= n; i++)
        if (state[i] == NOT_VISITED) dfs(i);
    
    reverse(stack.begin(), stack.end());
}

int main() {
    cin >> n >> m;
    
    adj.assign(n+1, vector<int>());
    state.assign(n+1, NOT_VISITED);

    while(m--) {
        int u, v; cin >> v >> u;
        adj[v].push_back(u);
    }

    topological_sort();

    if (cycle) cout << IMP << endl;
    else {
        for(int i = 0; i < n; i++) cout << stack[i] << " ";
        cout << endl;
    }
        

}