#include<iostream>
#include<vector>

using namespace std;

struct DSU {
    vector<int> p;
    vector<int> weight;
    int components;
    int max_weight;

    DSU(int n){
        components = n - 1;
        max_weight = 1;
        p.assign(n, -1);
        weight.assign(n, 1);
    }

    void unite(int u, int v){
        int c1, c2;
        c1 = find(u); c2 = find(v);
        if(c1 == c2) return;
        if(weight[c2] > weight[c1]) swap(c1, c2);
        p[c2] = c1;
        weight[c1] += weight[c2];
        if (max_weight < weight[c1]) max_weight = weight[c1];
        components--;
    }
    
    int find(int u){
        if(p[u] == -1) return u;
        int rep = find(p[u]);
        p[u] = rep;
        return rep;
    }

};

int main() {
    int n, m; cin >> n >> m;

    DSU dsu(n+1);
    vector<pair<int, int> > edges;

    while(m--){ 
        int u, v; cin >> u >> v;
        edges.push_back(make_pair(u,v));
    }

    for(int i = 0; i < edges.size(); i++) {
        dsu.unite(edges[i].first, edges[i].second);
        cout << dsu.components << " " << dsu.max_weight << endl;
    }
}