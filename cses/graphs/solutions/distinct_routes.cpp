#include<iostream>
#include<vector>
#include<queue>

using namespace std;

const int INF = 1e9;

int n, m;
vector<vector<int> > net, adj, capacity; 
vector<bool> visited;

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int> > q;
    q.push(make_pair(s, INF));

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : net[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push(make_pair(next, new_flow));
            }
        }
    }

    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(n+1);
    int new_flow;

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

int longest_path(int v) { 
    if (v == n) return 0;

    int length = 0;
    for(int u: adj[v]) {
        if (capacity[u][v] == 0) continue;
        int new_length = 1 + longest_path(u);
        length = max(length, new_length);
    }
    
    return length;
}

void dfs(int v, vector<int>& path) {
    path.push_back(v);
    visited[v] = true;

    if (v == n) return;

    for(int u: adj[v]) {
        if (visited[n]) return;
        if (!visited[u] and capacity[u][v] == 1) {
            // cout << v << " - " <<  u << " c: " << capacity[u][v] << endl;
            capacity[u][v] = 0;
            dfs(u, path);
        }
    }
}

void build_paths(int k) {
    vector<vector<int> > paths;
    vector<int> path;

    for(int i = 0; i < k; i++) {
        visited = vector<bool>(n+1, false);
        int dist = longest_path(1);
        dfs(1, path);
        paths.push_back(path);
        path.clear();
    }

    cout << k << endl;

    for(int i = 0; i < paths.size(); i++) {
        cout << paths[i].size() << endl;
        for(int j = 0; j < paths[i].size(); j++) {
            cout << paths[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    cin >> n >> m;

    net.assign(n+1, vector<int>());
    adj.assign(n+1, vector<int>());
    capacity.assign(n+1, vector<int>(n+1, 0));

    while(m--) {
        int v,u; cin >> v >> u;
        adj[v].push_back(u);
        net[v].push_back(u);
        net[u].push_back(v);
        capacity[v][u] = 1;
    }

    int flow = maxflow(1,n);

    for(int v = 1; v <= n; v++) {
        cout << v << ": ";
        for(int u: net[v]) {
            cout << "( " << u << ", " << capacity[v][u] << " ) ";
        }
        cout << endl;
    }

    build_paths(flow);
}