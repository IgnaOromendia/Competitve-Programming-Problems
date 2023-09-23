#include<iostream>
#include<vector>
#include<queue>

using namespace std;
using edge = pair<int, int>;

// judge: https://codeforces.com/contest/1000/problem/E

// Variables
int n, timer, num_bridges = 0;
vector<vector<int> > adj, blocks, tree_edges;
vector<edge> bridges;
vector<int> color, time_in, low, visited;

/// @param time_in = the time when we first visit v
/// @param low     = the lowest tin of any node that is reachable from v
/// for the node v,  low[v] = min(tin[v], tin[b] for all b that (v,b) is a back edge, low[u] for all (v,u) is a tree edge)

// **** The edge (v,u) is a bridge if and only if low[u] > tin[v] ****

// DFS to find bridges and generate a tree
void dfs(int v, int p = -1) {
    visited[v] = true;
    time_in[v] = low[v] = timer++;

    for(int u: adj[v]) {
        if (u == p) continue;
        if (visited[u]) {
            // (v,u) is a back edge
            low[v] = min(low[v], time_in[u]);
        } else {
            // (v,u) is a tree edge
            tree_edges[v].push_back(u);
            dfs(u, v);
            low[v] = min(low[v], low[u]);
            if (low[u] > time_in[v]) {
                // (v,u) is a bridge
                bridges.push_back(make_pair(v, u));
            }
        }
    }
}

// DFS to find blocks
void dfs_color(int v) {
    visited[v] = true;
    for(int u: adj[v]) {
        if (not visited[u]) {
            color[u] = color[v];
            dfs_color(u);
        }
    }
}

// Find bridges
void find_bridges() {
    timer = 0;
    for(int i = 1; i < n+1; i++) {
        if(not visited[i]) {
            dfs(i);
        }
    }
}

// Cut the bridges
void cut_bridges() {
    // Reset adj
    adj = vector<vector<int> >(n+1);

    // Remove bridges
    for(int v = 1; v < n+1; v++) {
        for(int u: tree_edges[v]) {
            if (low[u] <= time_in[v]) {
                // (i,u) is not a bridge
                adj[v].push_back(u);
                adj[u].push_back(v);
            }
        }
    }
}

// Paint with colors all connected components
int coloring() {
    visited = vector<int>(n+1, false);

    int last_color = 1;
    for(int i = 1; i < n+1; i++) {
        if(not visited[i]) {
            color[i] = last_color;
            dfs_color(i);
            last_color++;
        }
    }
    return last_color;
}

// Generate the block graph
void generate_block_graph(int c) {
    blocks = vector<vector<int> >(c);

    for(edge b: bridges) {
        int u = color[b.first];
        int v = color[b.second];
        blocks[u].push_back(v);
        blocks[v].push_back(u);
    }
}

// BFS
/// @param u the starting node
/// @return the farthest node from u and its distance
pair<int, int> bfs(int u) {
    queue<int> q;
    vector<int> dist(n+1, -1);

    dist[u] = 0;
    q.push(u);

    while(not q.empty()) {
        int v = q.front(); q.pop();
        for(int u: blocks[v]) {
            if(dist[u] == -1) {
                dist[u] = dist[v] + 1;
                q.push(u);
            }
        }
    }

    int max_dist = 0, node = 0;
    for(int i = 1; i < n+1; i++) {
        if (dist[i] > max_dist) {
            max_dist = dist[i];
            node = i;
        }
    }
    return make_pair(node, max_dist);
}

// Find the longest path in a tree
void longest_path() {
    // first = node, second = distance
    pair<int, int> p = bfs(1);
    pair<int, int> q = bfs(p.first);
    cout << q.second << endl;
}

int main() {
    int m;
    cin >> n >> m;

    tree_edges = vector<vector<int> >(n+1);
    visited = vector<int>(n+1, false);
    color   = vector<int>(n+1, -1);
    adj     = vector<vector<int> >(n+1);
    time_in = vector<int>(n+1, -1);
    low     = vector<int>(n+1, -1);
    
    while(m--) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    find_bridges();
    cut_bridges();
    int amount_of_cc = coloring();
    generate_block_graph(amount_of_cc);
    longest_path();
}