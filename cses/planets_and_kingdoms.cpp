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
vector<int> state;
vector<int> color;
int different_colors = 0;

void dfs(int v) {
    state[v] = PROCESSING;
    for(int u: adj[v]) {
        if (state[u] == NOT_VISITED) {
            color[u] = color[v];
            dfs(u);
        }
    }
    state[v] = VISITED;
}

void determine_kingdoms() {
    for(int i = 0; i < adj.size(); i++) {
        if (state[i] == NOT_VISITED) {
            color[i] = i;
            dfs(i);
            different_colors++;
        }
    }
}

int main() {
    int n,m; cin >> n >> m;

    adj   = vector<vector<int> >(n+1);
    state = vector<int>(n+1, NOT_VISITED);
    color = vector<int>(n+1, 0);

    while(m--) {
        int a,b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    determine_kingdoms();

    cout << different_colors << endl;
    for(int i = 1; i < color.size(); i++) {
        cout << color[i] << " ";
    }
    cout << endl;

}

