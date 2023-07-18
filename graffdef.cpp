#include<iostream>
#include<vector>
#include<iomanip> 
#include<math.h>

using namespace std;

// judge: https://www.spoj.com/problems/GRAFFDEF/

// Variables
vector<vector<int> > edges;
vector<vector<int> > no_bridge_edges;
vector<vector<int> > treeEdges; 
vector<int> backedge_lower_limite_on;
vector<int> backedge_upper_limite_on;
vector<int> tagCC;
vector<int> nodesXcc;
vector<int> state;
vector<int> memo;
long long n, m;

const int NOT_VISITED = -1;
const int PROCESSING = 0;
const int VISITED = 1;

// AUXILIARS
void reset_variables() {
    state    = vector<int>(n+1,NOT_VISITED);
    nodesXcc = vector<int>(n,0);
    tagCC    = vector<int>(n+1,-1);
}

// MAIN

// Fin backedges O(n + m)
void dfs(int v, int parent = -1) {
    state[v] = PROCESSING;
    for(int u: edges[v]) {
        if (state[u] == NOT_VISITED) {
            // Generating a tree
            treeEdges[v].push_back(u);
            dfs(u, v);
        } else if (u != parent and state[u] == PROCESSING) {
            backedge_lower_limite_on[v]++;
            backedge_upper_limite_on[u]++;
        }
    }

    state[v] = VISITED;
}

void dfs_without_bridges(int v, int cc = 0) {
    state[v] = PROCESSING;
    for(int u: no_bridge_edges[v]) {
        if (state[u] == NOT_VISITED) {
            tagCC[u] = cc;
            dfs_without_bridges(u, cc);
        } else {
            // It means I m in the same componenet
            tagCC[v] = tagCC[u];
        }
    }

    state[v] = VISITED;
}

// Finding the backedges O(n + m)
int coverd(int v, int parent = -1) {
    if(memo[v] != -1) return memo[v];
    int res = backedge_lower_limite_on[v];
    res    -= backedge_upper_limite_on[v];
    for(int son: treeEdges[v]) {
        if (son != parent) res += coverd(son, v);
    }
    memo[v] = res;
    return res;
}

// Finding the bridges O(n + m)
void get_bridges() {
    // Backedges
    for(int i = 0; i < n+1; i++) {
        if(state[i] == NOT_VISITED){
            dfs(i);
        } 
    }

    for(int i = 0; i < n+1; i++) {
       coverd(i);
    }

    for(int v = 1; v < n+1; v++) {
        for (int u: treeEdges[v]) {
            if (memo[u] != 0) {
                // Graph without bridges
                no_bridge_edges[v].push_back(u); 
                no_bridge_edges[u].push_back(v);
            }
        }
    }
}

void node_count_per_connected_component() { 
    reset_variables();
    int cc = 0;  // connected component count
    for(int i = 1; i < n+1; i++) {
        if (state[i] == NOT_VISITED) {
            tagCC[i] = cc;
            dfs_without_bridges(i,cc);
            cc++;
        } 
    }

    // Counting the amount of nodes per connected component
    for(int i = 1; i < tagCC.size(); i++) {
        nodesXcc[tagCC[i]]++;
    }
}

double losing_porb() {
    double winning_prob = 0;
    long long winning_ways = 0;
    for(int i = 0; i < nodesXcc.size(); i++) {
        if (nodesXcc[i] < 2) continue;
        long long nCC = nodesXcc[i];
        winning_ways += (nCC * (nCC-1)) / 2;
    }
    long long all_w_ways = (n*(n-1))/2;                           // All the ways of winning
    winning_prob = double(winning_ways) / double(all_w_ways);     // La probabilidad de ganar
    return  1.0 - winning_prob;                                   // P(perder) = 1 - P(ganar)
}

int main() {
    cin >> n >> m;

    edges                  = vector<vector<int> >(n+1,vector<int>(0));
    treeEdges                = vector<vector<int> >(n+1,vector<int>(0));
    no_bridge_edges        = vector<vector<int> >(n+1,vector<int>(0));
    state                   = vector<int>(n+1,NOT_VISITED);
    memo                     = vector<int>(n+1,-1);
    tagCC                    = vector<int>(n+1,-1);
    backedge_lower_limite_on = vector<int>(n+1,0);
    backedge_upper_limite_on = vector<int>(n+1,0);

    while (m--){
        int v,u; cin >> v >> u;
        edges[v].push_back(u);
        edges[u].push_back(v);
    }

    get_bridges();
    node_count_per_connected_component();
    cout << fixed << setprecision(5) << losing_porb() << endl;
    return 0;
}