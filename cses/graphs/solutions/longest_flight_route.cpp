#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

#define INF 1e9
#define IMP "IMPOSSIBLE"
#define NOT_VISITED -1
#define VISITING 0
#define VISITED 1

int n, m;
vector<vector<int> > adj;
vector<int> stack, state, dist, father, path;
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

void build_path() {
    int v = n;
    while(father[v] != -1) {
        path.push_back(v);
        v = father[v];
    }
    path.push_back(v);
    reverse(path.begin(), path.end());
}

void longest_path(int v) {
    topological_sort();

    dist[v] = 0;

    while(not stack.empty()) {
        int u = stack.front(); stack.erase(stack.begin());

        if(dist[u] != -INF) {
            for(int w: adj[u]) {
                if (dist[w] < dist[u] + 1) {
                    father[w] = u;
                    dist[w] = dist[u] + 1;
                }
            }
        }
    }

    build_path();
}

int main() {
    cin >> n >> m;
    
    adj.assign(n+1, vector<int>());
    father.assign(n+1, -1);
    state.assign(n+1, NOT_VISITED);
    dist.assign(n+1, -INF);

    while(m--) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
    }

    longest_path(1);

    if (path.size() == 1) {
        cout << IMP << endl;
    } else {
        cout << path.size() << endl;
        for(int i = 0; i < path.size(); i++) cout << path[i] << " ";
        cout << endl;
    }
    

}