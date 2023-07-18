#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const long long INF = 1e9;

// judge: https://www.spoj.com/problems/COCONUTS/

// Variables
int m, n, s, t;
vector<vector<int> > capacity;
vector<vector<int> > adj;

// Edmonds & Krap

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int> > q;
    q.push(make_pair(s, INF));

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
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
    vector<int> parent(n+2);
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
    while(true) {
        cin >> n >> m;
        if(n == 0 && m == 0) {
            break;
        }

        // Inicializo variables
        s = 0;
        t = n+1;
        adj      = vector<vector<int> >(n+2,vector<int>(0));
        capacity = vector<vector<int> >(n+2,vector<int>(n+2));

        // Leo que votan cada uno
        int i = 0;
        while(i < n) {
            int vote; scanf("%d", &vote);
            if (vote == 1) {
                adj[s].push_back(i+1);
                capacity[s][i+1] = 1;
            } else {
                adj[i+1].push_back(t);
                capacity[i+1][t] = 1;
            }
            i++;
        }

        // Leo el grafo
        i = 0;
        while(i < m) {
            int v, u; scanf("%d %d", &v, &u);
            adj[v].push_back(u);
            adj[u].push_back(v);
            capacity[v][u] = 1;
            capacity[u][v] = 1;
            i++;
        }

        int max_flow = maxflow(s,t);
        printf("%d\n",max_flow);
    }

    return 0;
}