#include<iostream>
#include<vector>
#include<algorithm>

#define INF 1e18

using namespace std;

struct edge {
    int from;
    int to;
    long long cost;
    edge(int from, int to, int cost) : from(from), to(to), cost(cost) {}
};

int n, m;
vector<edge> edges;

// Bellman Ford
void bellman_ford() {
    vector<long long> distances(n, INF);
    vector<int> parents(n, -1);
    int x;

    for(int i = 0; i < n; i++) {
        x = -1;

        for(edge e: edges) {
            if(distances[e.from] + e.cost < distances[e.to]) {
                distances[e.to] = distances[e.from] + e.cost;
                parents[e.to] = e.from;
                x = e.to;
            }
        }
    }

    if (x != -1) cout << "negative cycle" << endl;
    
}

using Edge = pair<uint, long>;
using Graph = vector<vector<Edge>>;

inline uint& vertex(Edge& e) {return e.first;}
inline long& weight(Edge& e) {return e.second;}

pair<vector<long>, vector<bool>> bellmanFordEficiente(const Graph& G) {
    vector<uint> changed;  // vertices of shortest path that changed in the last iteration
    changed.push_back(0);
    vector<long> dist(G.size(), INF);  // minimum distance up to a given iteration
    dist[0] = 0;
    vector<uint> iter(G.size(), 0); // last iteration where a vertex was extended

    for(auto i = 1u; i <= G.size() and not changed.empty(); ++i) {
        vector<uint> extensions;
        for(auto v : changed)
        for(auto e : G[v]) 
        if(dist[v] + weight(e) < dist[vertex(e)])
        {
            if(iter[vertex(e)] != i) extensions.push_back(vertex(e));
            iter[vertex(e)] = i;
            dist[vertex(e)] = dist[v] + weight(e);
        }
        swap(extensions, changed);
    }

    vector<bool> neg_cycle(G.size(), false);
    for(auto v : changed) neg_cycle[v] = true;

    return make_pair(dist, neg_cycle);
}