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
vector<long long> distances;

void dijkstra(int s) {
    priority_queue<pair<long long, int> > min_heap;
    vector<bool> visited(adj.size(), false);

    distances[s] = 0;
    min_heap.push(make_pair(0, s));

    while(!min_heap.empty()) {
        int u = min_heap.top().second; min_heap.pop();

        if(visited[u]) continue;
        visited[u] = true;

        for(edge e: adj[u]) {
            if (distances[e.to] > distances[u] + e.cost) {
                distances[e.to] = distances[u] + e.cost;
                min_heap.push(make_pair(-distances[e.to], e.to));
            }
        }
        
    }

}