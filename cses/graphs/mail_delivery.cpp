#include<iostream>
#include<vector>

using namespace std;

#define IMP "IMPOSSIBLE"

int n, m;
vector<vector<bool> > adj;
vector<int> path;



void find_eulerian_path(int v) {
    for(int u = 1; u <= n; u++) {
        if (!adj[v][u]) continue;
        adj[v][u] = adj[u][v] = false;
        find_eulerian_path(u);
    }
    path.push_back(v);
}

int main() {
    cin >> n >> m;

    adj.assign(n+1, vector<bool>(n+1, false));

    while(m--) {
        int v, u; cin >> v >> u;
        adj[v][u] = adj[u][v] = true;
    }

    find_eulerian_path(1);

    if (path.front() == path.back()) {
        for(int i = 0; i < path.size(); i++) {
            cout << path[i] << " ";
        }
        cout << endl;
    } else {
        cout << IMP << endl;
    }
}