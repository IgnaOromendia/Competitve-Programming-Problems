#include<iostream>
#include<vector>

using namespace std;

// Constants
const string IMPOSSIBLE = "IMPOSSIBLE";

// Variables    
int n, m;
vector<vector<int> > adj;
vector<int> father, cycle;
int cycle_start = -1, cycle_end = -1;

void dfs(int v, int p = -1) {
    for (int u : adj[v]) {
        if (father[u] == -1) {
            father[u] = v;
            dfs(u, v);
        } else if (father[u] != v and u != p) {
            // Cycle!
            cycle_start = v;
            cycle_end = u;
        }
    }
}

void find_trip() {
    for (int i = 1; i <= n; i++) {
        if (father[i] == -1) {
            father[i] = i;
            dfs(i);
        }
    }

    while(cycle_end != cycle_start) {
        cycle.push_back(cycle_end);
        cycle_end = father[cycle_end];
    }
    cycle.push_back(cycle_start);

    if (cycle.size() == 0 or cycle.size() == 1) {
        cout << IMPOSSIBLE << endl;
    } else {
        cout << cycle.size() + 1 << endl;
        for (int v : cycle) {
            cout << v << " ";
        }
        cout << cycle[0] << endl;
    }
}

int main() {
    cin >> n >> m;

    adj.resize(n+1);
    father.resize(n+1, -1);

    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    find_trip();
}