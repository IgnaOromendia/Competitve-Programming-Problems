#include<vector>
#include<iostream>
#include<queue>
#include<string>
#include<algorithm>

using namespace std;

// judge: https://cses.fi/problemset/task/1667

// Variables
const string IMPOSSIBLE = "IMPOSSIBLE";
int n, m;
vector<vector<int>> adj;
vector<int> routes;
vector<int> final_route;

void bfs() {
    vector<bool> visited(n + 1, false);
    visited[1] = true;
    queue<int> q;
    q.push(1);

    while(!q.empty()) {
        int u = q.front(); q.pop();

        for (int w : adj[u]) {
            if (!visited[w]) {
                visited[w] = true;
                routes[w] = u;
                q.push(w);
            }
        }
    }
}

void build_path() {
    int u = n;
    while (u != -1) {
        final_route.push_back(u);
        u = routes[u];
    }
}

int main() {
    cin >> n >> m;

    adj.resize(n+1, vector<int>());
    routes.resize(n+1, -1);

    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    bfs();

    build_path();

    if (final_route.size() == 1) {
        cout << IMPOSSIBLE << endl;
        return 0;
    }

    cout << final_route.size() << endl;
    for(int i = final_route.size() - 1; i >= 0; i--) {
        cout << final_route[i] << " ";
    }

    cout << endl;
    return 0;
}

