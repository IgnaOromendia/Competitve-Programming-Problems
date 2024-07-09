#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;

struct edge {
    int u;
    int v;
    int weight;
    edge(int u, int v, long long weight): u(u), v(v), weight(weight) {}
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

int min_rolls(int src, int dst) {
    int min_going_otherwise = min(abs(src - (dst - 10)),abs(dst - (src - 10)));
    return min(abs(dst - src), min_going_otherwise);
}

int rolls_needed(string src, string dst) {
    int sum = 0;
    for(int i = 0; i < 4; i++) {
        int right_unit = dst[i] - '0';
        int left_unit = src[i] - '0';
        sum += min_rolls(left_unit, right_unit);
    }
    return sum;
}

void add_edges_for_keys(vector<string>& keys, vector<edge>& edges) {
    for(int i = 0; i < keys.size() - 1; i++) {
        for(int j = i+1; j < keys.size(); j++) {
            if (i == j) continue;
            int weight = rolls_needed(keys[i],keys[j]);
            edges.push_back(edge(i,j,weight));
        }
    }
}

int kruskal_with(vector<edge>& edges, int amount_of_nodes) {
    int tree_weight = 0;
    sort(edges.begin(), edges.end(), [](edge a, edge b) { return a.weight < b.weight; });

    DSU dsu(amount_of_nodes);

    for(edge e: edges) {
        if(dsu.find(e.u) != dsu.find(e.v)) {
            dsu.unite(e.u, e.v);
            tree_weight += e.weight;
        }
    }

    return tree_weight;
}

int nearest_to_initial_point_of(vector<string>& keys) {
    int min_rolls = 100;

    for(int i = 0; i < keys.size();i++) 
        min_rolls = min(min_rolls,rolls_needed("0000",keys[i]));

    return min_rolls;
}

int main() { 
    int t; cin >> t;
    while(t--) {
        int number_of_keys; cin >> number_of_keys;

        vector<string> keys(number_of_keys);
        vector<edge> edges;
        
        for(int i = 0; i < number_of_keys; i++) cin >> keys[i];
        
        add_edges_for_keys(keys,edges);

        int rolls_from_all_keys = kruskal_with(edges, keys.size());

        int starting_roll = nearest_to_initial_point_of(keys);

        cout << rolls_from_all_keys + starting_roll << endl;
    }
}