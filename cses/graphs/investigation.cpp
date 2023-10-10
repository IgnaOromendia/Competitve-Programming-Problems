#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<limits>

using namespace std;

const long long INF = 1e14;

struct edge {
    int to;
    long long cost;
    edge() {}
    edge(int to, int cost) : to(to), cost(cost) {}
};

vector<vector<edge> > adj;
vector<pair<long long, long long> > dist;
vector<long long> min_edges, max_edges;
int n, m;

long long mod(long long x) {
    long long m = 1000000007LL;
    long long result = x % m;
    return result;
}

void dijkstra(int s) {
    priority_queue<pair<long long, int> > min_heap;
    vector<bool> visited(n+1, false);

    dist[s] = make_pair(0,1);
    min_edges[s] = 0;
    max_edges[s] = 0;
    min_heap.push(make_pair(0, s));

    while(!min_heap.empty()) {
        int u = min_heap.top().second; min_heap.pop();

        if(visited[u]) continue;
        visited[u] = true;

        for(edge e: adj[u]) {
            if (dist[e.to].first >= dist[u].first + e.cost) {
                // When cost is strictly lower we have to replace it
                if (dist[e.to].first > dist[u].first + e.cost) {
                    // Min amount of edges
                    min_edges[e.to] = min_edges[u] + 1;
                    
                    // Max amount of edges
                    max_edges[e.to] = max_edges[u] + 1;

                    dist[e.to].second = dist[u].second;
                } else { 
                    // When the costos are equal we might not replace it
                    dist[e.to].second = mod(dist[e.to].second + dist[u].second);

                    // Min amount of edges
                    if (min_edges[e.to] > min_edges[u] + 1) 
                        min_edges[e.to] = min_edges[u] + 1;
                    
                    // Max amount of edges
                    if (max_edges[e.to] < max_edges[u] + 1)
                        max_edges[e.to] = max_edges[u] + 1;
                }

                // Paths that use this node
                

                // Minimum distance
                dist[e.to].first = dist[u].first + e.cost;
                min_heap.push(make_pair(-dist[e.to].first, e.to));
            }
        }   
    }
}

int main() {
    cin >> n >> m;

    adj.assign(n+1, vector<edge>());
    dist.assign(n+1, make_pair(INF,0));
    min_edges.assign(n+1, INF);
    max_edges.assign(n+1, -1);

    while(m--) {
        int u, v; cin >> u >> v;
        long long c; cin >> c;
        adj[u].push_back(edge(v, c));
    }

    dijkstra(1);

    cout << dist[n].first << " ";
    cout << dist[n].second << " ";
    cout << min_edges[n] << " ";
    cout << max_edges[n] << endl;
}