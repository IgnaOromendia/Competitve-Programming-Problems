#include<vector>
#include<queue>

using namespace std;

constexpr int INF = 1e9;

struct Edge {
    int to;
    double weight;
    Edge(int to, int weight) : to(to), weight(weight) {}
};

int n;
vector<vector<int> > adj;
vector<int> parent;

void bfs(int s) {
    vector<bool> visited(n + 1, false);
    visited[s] = true;
    queue<int> q;
    q.push(s);

    while(!q.empty()) {
        int u = q.front(); q.pop();

        for (int w : adj[u]) {
            if (!visited[w]) {
                visited[w] = true;
                parent[w] = u;
                q.push(w);
            }
        }
    }
}

void bfs01(int s) {
    vector<vector<Edge> > adj;
    vector<int> d(n, INF);
    d[s] = 0;
    deque<int> q;
    q.push_front(s);

    while (!q.empty()) {
        int v = q.front();
        q.pop_front();

        for (auto edge : adj[v]) {
            int u = edge.to;
            int w = edge.weight;
            if (d[v] + w < d[u]) {
                d[u] = d[v] + w;
                if (w == 1) q.push_back(u);
                else q.push_front(u);
            }
        }

    }
}