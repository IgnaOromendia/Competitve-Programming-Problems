#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct edge {
    int u;
    int v;
    long long cost;
    edge(int u, int v, long long cost): u(u), v(v), cost(cost) {}
};

struct DSU {
    vector<int> p, rank;

    DSU(int n){
        p = vector<int>(n, -1);
        rank = vector<int>(n, 1);
        for(int i = 0; i < n; i++) p[i] = i;
    }

    void unionByRank(int u, int v){
        int du = find(u), dv = find(v);
        if(du == dv) return;
        if (rank[du] < rank[dv]) {
            p[du] = dv;
        } else if (rank[du] > rank[dv]) {
            p[dv] = du;
        } else {
            p[dv] = du;
            rank[du]++;
        }
    }
    
    int find(int u){
        if (u == p[u]) return u;
        return p[u] = find(p[u]);
    }

};


vector<vector<int> > adj;
vector<bool> visited;
vector<edge> edges;
int n, m;
long long cost;

void kruskal() {
    sort(edges.begin(), edges.end(), [](edge a, edge b) { return a.cost < b.cost; });

    DSU dsu(n+1);

    for(edge e: edges) {
        if(dsu.find(e.u) != dsu.find(e.v)) {
            dsu.unionByRank(e.u, e.v);
            cost += e.cost;
            adj[e.u].push_back(e.v);
            adj[e.v].push_back(e.u);
        }
    }
}