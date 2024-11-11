#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

string any = "any";
string alo = "at least one";
string none = "none";

struct edge {
    int u;
    int v;
    int w;
    int idx;
    edge(): u(0), v(0), w(0), idx(0) {}
    edge(int u, int v, int w, int i): u(u), v(v), w(w), idx(i) {}
};

struct DSU {
    vector<int> p, rank;

    DSU(int n){
        int p[n];
        int rank[n];
        for(int i = 0; i < n; i++) {
            p[i] = i;
            rank[i] = 1;
        }
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

int n,m; 
unordered_map<int, vector<pair<int, int> > > adj; 
unordered_map<int, bool> visited;
unordered_map<int, int> tin, low;
int timer;

void dfs(int* status, int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    bool parent_skipped = false;

    for (auto& [to, edgeID] : adj[v]) { 
        if (to == p && !parent_skipped) {
            parent_skipped = true;
            continue;
        }
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(status, to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v]) status[edgeID] = 2;
        }
    }
}

void find_bridges(int* status) {
    timer = 0;
    visited.clear();
    tin.clear();
    low.clear();
    for (auto& [u, id]: adj) 
        if (!visited[u])
            dfs(status, u);
}

void classify_edges(int* status, edge* edges) {
    sort(edges, edges + m, [](edge a, edge b) { return a.w < b.w; });

    DSU dsu(n);

    for(int i = 0; i < m;) {
        int j = i;

        for(; edges[i].w == edges[j].w; j++) {
            int dv = dsu.find(edges[j].v);
            int du = dsu.find(edges[j].u);

            // Agregamos arsitas a G'
            if (dv != du) {
                // Asignamos at least one
                status[edges[j].idx] = 1;
                adj[dv].push_back(make_pair(du, edges[j].idx));
                adj[du].push_back(make_pair(dv, edges[j].idx));
            }
        }

        // Encontramos puente
        find_bridges(status);

        // Limpiamos G' 
        adj.clear();

        // Unimos las componentes conexas O(m)
        for(j = i; edges[i].w == edges[j].w; j++)
            if (dsu.find(edges[j].u) != dsu.find(edges[j].v))
                dsu.unionByRank(edges[j].u, edges[j].v);
            
        i = j;
    }

}

int main() {
    cin >> n >> m;

    int status[m];
    edge edges[m];

    for(int i = 0; i < m; i++) {
        int a,b,c; cin >> a >> b >> c; a--;b--;
        edges[i]  = edge(a,b,c,i);
        status[i] = 0;
    }

    classify_edges(status, edges);

    for(int i = 0; i < m; i++) {
        if (status[i] == 1) cout << alo << endl;
        else if (status[i] == 2) cout << any << endl;
        else cout << none << endl;
    }
}