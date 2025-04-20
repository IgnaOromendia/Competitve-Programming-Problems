#include<iostream>
#include<vector>
#include<queue>

using namespace std;

const int INF = 1e9;

int n, m, k, N;
vector<vector<int> > net, capacity; 

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
    vector<int> parent(N);
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

int main() {
    cin >> n >> m >> k;

    N = n + m + 2;

    int t = N - 1;

    net.assign(N, vector<int>());
    capacity.assign(N, vector<int>(N,0));

    // boys -> girls
    for(int q = 0; q < k; q++) {
        int v,u; cin >> v >> u;
        u += n;
        if (capacity[v][u] == 1) continue;
        net[v].push_back(u);
        net[u].push_back(v);
        capacity[v][u] = 1;
    }

    // s -> boys
    for(int i = 1; i <= n; i++) {
        net[0].push_back(i);
        net[i].push_back(0);
        capacity[0][i] = 1;
    }

    // girls -> t
    for(int j = 0; j < m; j++) {
        net[j + n + 1].push_back(t);
        net[t].push_back(j+ n + 1);
        capacity[j + n + 1][t] = 1;
    }

    int flow = maxflow(0, t);

    cout << flow << endl;

    for(int v = 1; v <= n; v++) {
        for(int u: net[v]) {
            if (capacity[u][v] == 1 and capacity[t][u] == 1) cout << v << " " << u - n << endl;
        }
    }
}