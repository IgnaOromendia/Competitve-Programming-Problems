#include<iostream>
#include<vector>
#include<queue>

#define INF 1e16

using namespace std;

struct edge {
    int v, w;
    long long cost;
    edge() {}
    edge(int v, int w, long long c): v(v), w(w), cost(c) {}
};


int n;
vector<vector<int> > adj;
vector<vector<int> > adj_T;
vector<edge> edges;
vector<bool> visited;
vector<int> father, marked;


void dfs(int v, vector<vector<int> >& adj) {
    marked[v]++; 
    visited[v] = true;
    for(int &u: adj[v]) {
        if (!visited[u]) dfs(u, adj);
    }
}

void remove_unreachables() {
    dfs(1, adj);
    visited.assign(n+1, false);
    dfs(n, adj_T);
}

long long find_max_score() {
    vector<long long> dist(n+1, INF);

    int x;
    dist[1] = 0;
    for(int i = 0; i < n; i++) {
        x = -1;
        for(edge &e: edges) {
            if (marked[e.v] < 2 or marked[e.w] < 2) continue;
            if(dist[e.v] + e.cost < dist[e.w]) {
                dist[e.w] = dist[e.v] + e.cost;
                father[e.w] = e.v;
                x = e.w;
            }
        }
    }

    // if x == -1 there is no negative cycle
    return x == -1 ? -dist[n] : -1;
}

int main() {
    int m; cin >> n >> m;

    adj.assign(n+1, vector<int>());
    adj_T.assign(n+1, vector<int>());
    visited.assign(n+1, false);
    marked.assign(n+1, false);
    father.assign(n+1, -1);

    while(m--) {
        int a, b;
        long long c; 
        cin >> a >> b >> c;
        adj[a].push_back(b);
        adj_T[b].push_back(a);
        edges.push_back(edge(a,b,-c));
    }

    remove_unreachables();

    cout << find_max_score() << endl;

}