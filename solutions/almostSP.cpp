#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <queue>

using namespace std;

struct Edge {
    int to, cost;
    bool belongs_to_sp = false;
    Edge(int to, int cost) : to(to), cost(cost) {}
    Edge() : to(0), cost(0) {}
};

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > mat;
typedef vector<vector<Edge> > wgraph;
typedef pair<int,int> pi;
typedef pair<double,double> pd;

#define pb push_back
#define mp make_pair

#define forn(i,from,to) for (int i = from; i < to; i++)

constexpr int INF  = 1e9;
constexpr int MAXN = 0;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

void sparseDijkstra(int s, vi& dist, wgraph& adj) {
    priority_queue<pi> heap;
    vi visited(adj.size(), 0);

    dist[s] = 0;
    heap.push(mp(0, s));

    while(!heap.empty()) {
        int u = heap.top().second; heap.pop();

        if(visited[u]) continue;
        visited[u] = true;

        for(Edge e: adj[u])
            if (dist[e.to] > dist[u] + e.cost and !e.belongs_to_sp) {
                dist[e.to] = dist[u] + e.cost;
                heap.push(mp(-dist[e.to], e.to));
            }
    }
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int n, m, s, t;

    while(cin >> n >> m, n + m > 0) {
        cin >> s >> t;

        wgraph adj(n), adjT(n);
        vi distS(n, INF), distT(n, INF);

        while(m--) {
            int u,v,w; cin >> u >> v >> w;
            adj[u].emplace_back(v, w);
            adjT[v].emplace_back(u, w);
        }

        sparseDijkstra(s, distS, adj);
        sparseDijkstra(t, distT, adjT);

        // Verificamos st-eficiente para cada arista
        forn(v,0,n) 
            for(Edge& e: adj[v]) 
                e.belongs_to_sp = distS[v] + e.cost + distT[e.to] == distS[t];
        
        // Volvemos a correr dijkstra pero sin tomar las st-eficiente
        distS.assign(n, INF);
        sparseDijkstra(s, distS, adj);

        cout << (distS[t] == INF ? -1 : distS[t]) << "\n";

    }


}