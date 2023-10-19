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

int n, q, cycle_tag = 0;
vector<query> queries;
vector<int> adj, state;
vector<pair<int, int> > cycle_id;
vector<bool> is_root;
vector<pair<int, int> > dist_to_root;
vector<vector<int> > dist_from_root, cycles;

/// @brief Update the distance to the root of u coming from v
void update_distance_root(int u, int v) {
    // Set the root
    int r =  dist_to_root[v].first;
    dist_to_root[u].first = r;
    
    // Update the distance
    dist_to_root[u].second = dist_to_root[v].second + 1;

    // Set into the matrix if is the logaritmic distance
    double log_dist = log2(dist_to_root[u].second);

    if (log_dist < dist_from_root[r].size() and log_dist == floor(log_dist))
        dist_from_root[r][log_dist] = u;
}

void dfs(int v) {
    state[v] = VISITING;
    int u = adj[v];

    if (state[u] == NOT_VISITED) {
        update_distance_root(u, v);
        dfs(u);
    } else if (state[u] == VISITING) {
        int start = u;
        int end = v;

        // Building the cycle
        vector<int> path;
        while(start != end) {
            cycle_id[start].first  = cycle_tag;
            cycle_id[start].second = path.size();
            path.push_back(start);
            start = adj[start];
        }
        cycle_id[end].first = cycle_tag;
        cycle_id[end].second = path.size();
        path.push_back(end);

        // Saving the length of the cycle
        cycles.push_back(path);

        // Incrementing cycle tag
        cycle_tag++;
    } else {
        update_distance_root(u, v);
        if (cycle_id[u].first == -1) dfs(u);
    }

    state[v] = VISITED;
}

void cycles_and_distances() {
    for(int v = 1; v <= n; v++)
        if (state[v] == NOT_VISITED) {
            dist_to_root[v].first = v;
            dist_to_root[v].second = 0;
            dfs(v);
        }
}


int process_cycle(int v, int k) {
    int position = cycle_id[v].second;
    int id       = cycle_id[v].first;
    int size     = cycles[id].size();
    return cycles[id][(k + position) % size];
}

int travel(int v, int limit) {
    if (limit == 0)              return v;
    if (cycle_id[v].first == -1) return travel(adj[v],limit-1);
    else                         return process_cycle(v, limit);
}

int process_query(int v, int k) {
    if (cycle_id[v].first != -1) return process_cycle(v, k); // O(1)

    // Values assuming v is a root
    int teleports = k;
    int root      = v;

    if (!is_root[v]) { // O(1)
        root      = dist_to_root[v].first;
        teleports = k + dist_to_root[v].second;
    } 

    int pw_2  = floor(log2(teleports));
    int last  = dist_from_root[root].size() - 1;
    int i     = min(pw_2, last);
    int limit = last >= 0 ? teleports - pow(2,i) : k;
    int from  = last >= 0 ? dist_from_root[root][i] : v;

    while(from == -1) { // O(log k)
        i--;
        limit += pow(2,i);
        from = dist_from_root[root][i]; 
    } 

    return travel(from, limit); // O(n)
}

void destinations() {
    for(query &q: queries)
        cout << process_query(q.first, q.second) << endl;
}

int main() {
    cin >> n >> q;

    adj.assign(n+1, int());
    state.assign(n+1, NOT_VISITED);
    is_root.assign(n+1, true);
    cycle_id.assign(n+1, make_pair(-1,-1));
    dist_to_root.assign(n+1, make_pair(-1,-1));

    for(int i = 1; i <= n; i++) {
        int v; cin >> v;
        is_root[v] = false;
        adj[i] = v;
    }

    int max_k = 0;
    while(q--) {
        int x, k; cin >> x >> k;
        if (k > max_k) max_k = k;
        queries.push_back(make_pair(x,k));
    }

    max_k = round(log2(max_k));

    dist_from_root.assign(n+1, vector<int>(max_k, -1));

    cycles_and_distances(); // O(n)

    // for(int i = 0; i < cycles.size(); i++) {
    //     if (!cycles[i].empty()) {
    //         cout << i << ": ";
    //         for(int j = 0; j < cycles[i].size(); j++) {
    //             cout << cycles[i][j] << " ";
    //         }
    //         cout << endl;
    //     }
    // }

    for(int r = n+1; r <= n; r++) {
        if (is_root[r]) {
            cout << r << ": ";
            for(int i = 0; i < dist_from_root[r].size(); i++) {
                cout << i << " ";
            }
            cout << endl;
        }
    }

    destinations(); // O(n)
}