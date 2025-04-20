#include<iostream>
#include<vector>
#include <algorithm>

using namespace std;

// judge: https://codeforces.com/problemset/problem/1245/D

// Structs
struct node {
    int x;
    int y;
    long long cost_plant;
    long long cost_wire;
    node(int x, int y): x(x), y(y) {}
};

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

// Variables
int n, m, amount_plants = 0;
long long final_cost = 0;
vector<edge> edges;
vector<int> plants;
vector<edge> wires;

void kruskal() {
    sort(edges.begin(), edges.end(), [](edge a, edge b) { return a.cost < b.cost; });

    DSU dsu(n+1);

    for(edge e: edges) {
        if(dsu.find(e.u) != dsu.find(e.v)) {
            if (e.v == 0) {
                amount_plants++;
                plants.push_back(e.u);
            } else {
                wires.push_back(e);
            }
            dsu.unite(e.u, e.v);
            final_cost += e.cost;        
        }
    }
}

void find_best_plan() {
    kruskal();

    // Cost
    cout << final_cost << endl;

    // Amount of plants
    cout << amount_plants << endl;

    // Plants
    for(int i = 0; i < plants.size(); i++) {
        cout << plants[i] << " ";
    }
    cout << endl;

    // Wires
    cout << wires.size() << endl;
    for(int i = 0; i < wires.size(); i++) {
        cout << wires[i].u << " " << wires[i].v << endl;
    }

}

int main() {
    cin >> n;

    vector<node> nodes;

    // Reading nodes
    for(int i = 0; i < n; i++) {
        int x,y; cin >> x >> y;
        nodes.push_back(node(x,y));
    }

    // Reading plant costs
    for(int i = 0; i < n; i++) {
        long long c; cin >> c;
        nodes[i].cost_plant = c;
    }

    // Reading wire costs
    for(int i = 0; i < n; i++) {
        long long k; cin >> k;
        nodes[i].cost_wire = k;
    }

    // Creating edges between cities
    for(int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            // ki + kj * |xi - xj| + |yi - yj|
            edges.push_back(edge(i+1,j+1, (nodes[i].cost_wire + nodes[j].cost_wire ) * (abs(nodes[i].x - nodes[j].x) + abs(nodes[i].y - nodes[j].y))));
        }
    }

    // Creating edges between cities and plants
    for(int i = 0; i < n; i++) {
        edges.push_back(edge(i+1, 0, nodes[i].cost_plant));
    }

    find_best_plan();
}