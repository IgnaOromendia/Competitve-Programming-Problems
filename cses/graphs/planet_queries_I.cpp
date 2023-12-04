#include<iostream>
#include<vector>
#include<math.h>
#include<algorithm>
 
#define INF 1e8;
#define NOT_VISITED -1
#define VISITING 0
#define VISITED 1
 
using namespace std;
typedef pair<int, int> query;
 
int n, q, cycle_tag = 0, current = -1, end_c = -1, i, size_c;;
vector<query> queries;
vector<int> adj, state, path;
vector<pair<int, int> > cycle_id;
vector<bool> is_root;
vector<pair<int, int> > dist_to_root;
vector<vector<int> > dist_from_root, cycles;
 
/// @brief Update the distance to the root r of u coming from v
/// O(1)
void update_distance_root(int u, int v, int r) {
    // Set the root
    dist_to_root[u].first = r;

    // Update the distance
    dist_to_root[u].second = dist_to_root[v].second + 1;
 
    // Set into the matrix 
    dist_from_root[r].push_back(u);
}

/// @brief Process the graph updating distances and building cycles
/// @param v 
void dfs(int v, int r) {
    state[v] = VISITING;
    int u = adj[v];
 
    if (state[u] == NOT_VISITED) {
        update_distance_root(u, v, r);
        dfs(u, r);
    } else if (state[u] == VISITING) {
        current = u;
        end_c = v;
        size_c = dist_to_root[end_c].second - dist_to_root[current].second + 1;
        path = vector<int>(size_c);
    } else {
        update_distance_root(u, v, r);
        if (cycle_id[u].first == -1) dfs(u, r);
    }

    if (current != end_c and i < size_c) {
        // Saving in cycle data
        cycle_id[current].first = cycle_tag;
        cycle_id[current].second = i;
        path[i] = current;
        current = adj[current];
        i++;
    } else if (current == end_c and i == size_c - 1) {
        // Saving in data and reseting variables
        cycle_id[end_c].first = cycle_tag;
        cycle_id[end_c].second = i;
        path[i] = end_c;
        cycles.push_back(path);
        cycle_tag++;
        i = 0;
        size_c = 0;
        current = -1;
        end_c = -1;
        path.clear();
    }
 
    state[v] = VISITED;
}
 
void cycles_and_distances() {
    for(int v = 1; v <= n; v++)
        if (state[v] == NOT_VISITED) {
            dist_to_root[v].first = v;
            dist_to_root[v].second = 0;
            dfs(v, v);
        }
}
 
// O(1)
int process_cycle(int v, int k) {
    int position = cycle_id[v].second;
    int id       = cycle_id[v].first;
    int size     = cycles[id].size();
    return cycles[id][(k + position) % size];
}
 
// O(1)
int process_query(int v, int k) {
    if (cycle_id[v].first != -1) return process_cycle(v, k);
 
    // Values assuming v is a root
    int teleports = k;
    int root      = v;
 
    if (!is_root[v]) {
        root      = dist_to_root[v].first;
        teleports = k + dist_to_root[v].second;
    } 
 
    int size = dist_from_root[root].size();
 
    if (teleports < size) return dist_from_root[root][teleports];
 
    int from = dist_from_root[root][size - 1];
    teleports -= (size - 1);
 
    if (cycle_id[from].first == -1) from = adj[from];
    
    return process_cycle(from, teleports);
}
 
int main() {
    cin >> n >> q;
 
    adj.assign(n+1, 0);
    state.assign(n+1, NOT_VISITED);
    is_root.assign(n+1, true);
    cycle_id.assign(n+1, make_pair(-1,-1));
    dist_to_root.assign(n+1, make_pair(-1,-1));
    dist_from_root.assign(n+1, vector<int>(1, -1));
 
    for(int i = 1; i <= n; i++) {
        int v; cin >> v;
        is_root[v] = false;
        adj[i] = v;
    }
 
    while(q--) {
        int x, k; cin >> x >> k;
        queries.push_back(make_pair(x,k));
    }
 
    cycles_and_distances(); // O(n)
 
    for(query &q: queries)
        cout << process_query(q.first, q.second) << endl;
}