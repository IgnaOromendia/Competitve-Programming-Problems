#include<iostream>
#include<vector>
#include<queue>

using namespace std;

const int INF = 1e9;

int n, m;
vector<vector<long long> > capacity; 
vector<vector<int> > net;

long long bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, long long> > q;
    q.push(make_pair(s, INF));

    while (!q.empty()) {
        int cur = q.front().first;
        long long flow = q.front().second;
        q.pop();

        for (int next : net[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                long long new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push(make_pair(next, new_flow));
            }
        }
    }

    return 0;
}

long long maxflow(int s, int t) {
    long long flow = 0;
    vector<int> parent(n+1);
    long long new_flow;

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

void find_min_cut() {
    long long flow = maxflow(1,n);
    vector<int> distance(n+1, INF);
    vector<int> visited(n+1, false);
    vector<pair<int, int> > frontier;
    queue<int> q;
    q.push(1);
    distance[1] = 0;

    while(!q.empty()) {
        int v = q.front(); q.pop();

        for(int u: net[v]) {
            if (!visited[u]) {
                if (capacity[v][u] == 0) continue;
                distance[u] = distance[v] + 1;
                visited[u] = true;
                q.push(u);
            }
        }
    }

    for(int v = 1; v <= n; v++) {
        if (distance[v] == INF) continue;
        for(int u: net[v]) {
            if (distance[u] == INF) frontier.push_back(make_pair(v,u));
        }
    }

    cout << flow << endl;
    for(int i = 0; i < frontier.size(); i++)
        cout << frontier[i].first << " " << frontier[i].second << endl;

}

int main() {
    cin >> n >> m;

    net.assign(n+1, vector<int>());
    capacity.assign(n+1, vector<long long>(n+1, 0));

    while(m--) {
        int v,u; cin >> v >> u;
        net[v].push_back(u);
        net[u].push_back(v);
        capacity[v][u] = 1;
        capacity[u][v] = 1;
    }

    find_min_cut();
}