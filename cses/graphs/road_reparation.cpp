#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

#define IMP "IMPOSSIBLE"

struct edge {
    int u;
    int v;
    long long cost;
    edge(int u, int v, long long cost): u(u), v(v), cost(cost) {}
};

struct DSU {
    vector<int> p;
    vector<int> rank;

    DSU(int n){
        p = vector<int>(n, -1);
        rank = vector<int>(n, 1);
    }

    void unite(int u, int v){
        int c1, c2;
        c1 = find(u); c2 = find(v);
        if(c1 == c2) return;
        if(rank[c2] > rank[c1]) swap(c1, c2);
        p[c2] = c1;
        rank[c1] = max(rank[c1], rank[c2]+1);
    }
    
    int find(int u){
        if(p[u] == -1) return u;
        int rep = find(p[u]);
        p[u] = rep;
        return rep;
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
            dsu.unite(e.u, e.v);
            cost += e.cost;
            adj[e.u].push_back(e.v);
            adj[e.v].push_back(e.u);
        }
    }
}

void dfs(int v) {
    visited[v] = true;
    for(int u: adj[v]) {
        if(!visited[u]) dfs(u);
    }
}

void repair_cost() {
    kruskal();

    int count = 0;
    for(int i = 1; i <= n; i++) {
        if(!visited[i]) {
            dfs(i);
            count++;
        }
    }

    if (count == 1) cout << cost << endl;
    else cout << IMP << endl;
}

int main() {
    cin >> n >> m;

    adj.assign(n+1, vector<int>());
    visited.assign(n+1, false);

    while(m--) {
        int u,v;
        long long c;
        cin >> u >> v >> c;
        edges.push_back(edge(u,v,c));
    }

    repair_cost();
}

