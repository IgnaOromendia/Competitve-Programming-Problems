#include<iostream>
#include<vector>
#include<algorithm>

#define INF 1e18

using namespace std;

struct edge {
    int from;
    int to;
    long long cost;
    edge(int from, int to, int cost) : from(from), to(to), cost(cost) {}
};

int n, m;
vector<edge> edges;

// Bellman Ford
void bellman_ford() {
    vector<long long> distances(n, INF);
    vector<int> parents(n, -1);
    int x;

    for(int i = 0; i < n; i++) {
        x = -1;

        for(edge e: edges) {
            if(distances[e.from] + e.cost < distances[e.to]) {
                distances[e.to] = distances[e.from] + e.cost;
                parents[e.to] = e.from;
                x = e.to;
            }
        }
    }

    if (x != -1) cout << "negative cycle" << endl;
    
}