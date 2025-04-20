#include<vector>
#include<iostream>

using namespace std;
using arista = pair<int, int>;

// judge: https://cses.fi/problemset/task/1666

// Variables
int n, m;
vector<vector<int>> adj;
vector<bool> visited;
vector<arista> roads;

void dfs(int v) {
    visited[v] = true;
    for (int u : adj[v]) {
        if (!visited[u]) {
            dfs(u);
        }
    }
}

int number_of_roads() {
    int count = 0;
    int u = -1;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i);
            count++;
            if (u == -1) {
                u = i;
            } else {
                roads.push_back({u, i});
            }
        }
    }
    return count - 1;
}

int main() {
    cin >> n >> m;

    adj.resize(n + 1);
    visited.resize(n + 1);

    while(m--) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    cout << number_of_roads() << endl;

    for (arista a : roads) {
        cout << a.first << " " << a.second << endl;
    }


    
}