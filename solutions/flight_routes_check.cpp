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
int n, m;

void dfs(int v, vector<vector<int> > &adj) {
    state[v] = PROCESSING;
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

void check_flights() {
    find_strong_components();

    for(int i = 1; i < n; i++) {
        if (strong_component[i] != strong_component[i + 1]) {
            state = vector<int>(n+1, NOT_VISITED);
            dfs(i, adj);
            cout << NO << endl;
            if (state[i+1] == VISITED) cout << i+1 << " " << i << endl;
            else cout << i << " " << i+1 << endl;
            return;
        }
    }

    cout << YES << endl;
}

int main() {
    cin >> n >> m;

    adj.assign(n+1, vector<int>());
    adj_T.assign(n+1, vector<int>());
    state.assign(n+1, NOT_VISITED);
    strong_component.assign(n+1, -1);

    while(m--) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj_T[v].push_back(u);
    }

    check_flights();
}