#include<vector>

using namespace std;

#define forn(i,from,to) for (int i = from; i < to; i++)

void IS_BRIDGE(int v,int to); 
void IS_BACKEDGE(int to,int v);
int n; 
vector<vector<int>> adj; 

vector<bool> visited;
vector<int> tin, low;
int timer;

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    for (int to : adj[v]) {
        if (to == p) continue;
        if (visited[to]) {
            if (tin[to] > tin[v]) IS_BACKEDGE(to,v);
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v])
                IS_BRIDGE(v, to);
        }
    }
}

void find_bridges() {
    timer = 0;
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    forn(i, 0, n) {
        if (!visited[i])
            dfs(i);
    }
}