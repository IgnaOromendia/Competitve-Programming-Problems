#include<iostream>
#include<vector>

using namespace std;

// Constants
const string IMPOSSIBLE = "IMPOSSIBLE";

// Variables
int n, m;
vector<vector<int> > adj;
vector<bool> visted;
vector<int> color;

void dfs(int v, int p = -1) {
    visted[v] = true;
    for (int u : adj[v]) {
        if (!visted[u]) {
            color[u] = 1 - color[v];
            dfs(u, v);
        } else if (color[u] == color[v]) {
            cout << IMPOSSIBLE << endl;
            exit(0);
        }
    }
}

void build_teams() {
    for (int i = 1; i <= n; i++) {
        if (!visted[i]) {
            dfs(i);
        }
    }
}

int main() {
    cin >> n >> m;

    adj.resize(n+1);
    visted.resize(n+1);
    color.resize(n+1,0);

    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    build_teams();



    for (int i = 1; i <= n; i++) {
        cout << color[i] + 1 << " ";
    }
    cout << endl;
}