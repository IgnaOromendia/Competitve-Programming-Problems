#include<iostream>
#include<vector>
#include<queue>

#define INF 1e18

using namespace std;

struct edge {
    int to;
    long long cost;
    edge(int to, int cost) : to(to), cost(cost) {}
};

vector<vector<edge> > adj;
vector<long long> dist;

void sparseDijkstra(int s) {
    priority_queue<pair<long long, int> > heap;
    vector<bool> visited(adj.size(), false);

    dist[s] = 0;
    heap.push(make_pair(0, s));

    while(!heap.empty()) {
        int u = heap.top().second; heap.pop();

        if(visited[u]) continue;
        visited[u] = true;

        for(edge e: adj[u]) {
            if (dist[e.to] > dist[u] + e.cost) {
                dist[e.to] = dist[u] + e.cost;
                heap.push(make_pair(-dist[e.to], e.to));
            }
        }
        
    }

}

void denseDijkstra(int s) {
    int n = adj.size();
    vector<int> p(n, -1);
    vector<bool> u(n, false);

    dist[s] = 0;
    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int j = 0; j < n; j++) {
            if (!u[j] && (v == -1 || dist[j] < dist[v]))
                v = j;
        }

        if (dist[v] == INF) break;

        u[v] = true;
        for (auto e : adj[v]) {
            if (dist[v] + e.cost < dist[e.to]) {
                dist[e.to] = dist[v] + e.cost;
                p[e.to] = v;
            }
        }
    }
}