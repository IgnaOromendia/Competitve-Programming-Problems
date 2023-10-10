#include<vector>
#include<iostream>

using namespace std;

// judge: https://cses.fi/problemset/task/1683

// Contants
const int NOT_VISITED = -1;
const int PROCESSING = 0;
const int VISITED = 1;

// Variables
vector<vector<int> > adj;
vector<vector<int> > adj_T;
vector<int> stack;
vector<int> state;
vector<int> kingdom;
int n, m, num_kingdoms = 0;

void dfs(int v, vector<vector<int> > &adj) {
    state[v] = PROCESSING;
    for(int u: adj[v]) {
        if(state[u] == NOT_VISITED) {
            kingdom[u] = kingdom[v];
            dfs(u, adj);
        }
    }
    state[v] = VISITED;
    stack.push_back(v);
}

void determine_kingdoms() {
    // Run dfs on the graph
    for(int i = 0; i < n+1; i++) {
        if(state[i] == NOT_VISITED) {
            dfs(i, adj);
        }
    }

    // Reset state and kingdoms
    state   = vector<int>(n+1, NOT_VISITED);
    kingdom = vector<int>(n+1, 0);

    // Run dfs on the transpose graph
    while(!stack.empty()) {
        int v = stack.back(); stack.pop_back();
        if(state[v] == NOT_VISITED) {
            num_kingdoms++;
            kingdom[v] = num_kingdoms;
            dfs(v, adj_T);
        }
    }
}


int main() {
    cin >> n >> m;

    adj   = vector<vector<int> >(n+1);
    adj_T = vector<vector<int> >(n+1);
    state = vector<int>(n+1, NOT_VISITED);
    kingdom = vector<int>(n+1, 0);


    while(m--) {
        int a,b; cin >> a >> b;
        adj[a].push_back(b);
        adj_T[b].push_back(a);
    }

    determine_kingdoms();

    cout << num_kingdoms - 1 << endl;
    for(int i = 1; i < n+1; i++) {
        cout << kingdom[i] << " ";
    }
    cout << endl;


}

