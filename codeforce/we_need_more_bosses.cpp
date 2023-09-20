#include<iostream>
#include<vector>

using namespace std;

// judge: https://codeforces.com/contest/1000/problem/E

// Variables
int n, timer;
vector<vector<int> > adj;
vector<int> time_in, low;
vector<bool> visited;
int num_bridges = 0;

/// @param time_in = the time when we first visit v
/// @param low     = the lowest tin of any node that is reachable from v
/// for the node v,  low[v] = min(tin[v], tin[p] for all p that (v,p) is a back edge, low[u] for all (v,u) is a tree edge)

// **** The edge (v,u) is a bridge if and only if low[u] > tin[v] ****

void dfs(int v, int p = -1) {
    visited[v] = true;
    time_in[v] = low[v] = timer++;

    for(int u: adj[v]) {
        if (u == p) continue;
        if (visited[u]) {
            // (v,u) is a back edge
            low[v] = min(low[v], time_in[u]);
        } else {
            // (v,u) is a tree edge
            dfs(u, v);
            low[v] = min(low[v], low[u]);
            if (low[u] > time_in[v]) {
                // (v,u) is a bridge
                num_bridges++;
            }
        }
    }
}

void find_bridges() {
    timer = 0;
    for(int i = 0; i < n+1; i++) {
        if(!visited[i]) {
            dfs(i);
        }
    }
}

int main() {
    int m;
    cin >> n >> m;

    adj     = vector<vector<int> >(n+1);
    time_in = vector<int>(n+1, -1);
    low     = vector<int>(n+1, -1);
    visited = vector<bool>(n+1, false);
    

    while(m--) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    find_bridges();

    cout << num_bridges << endl;

}