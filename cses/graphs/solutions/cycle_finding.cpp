#include<iostream>
#include<vector>
#include<algorithm>

#define INF 1e18
#define NO "NO"
#define YES "YES"

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

    if (x == -1) cout << NO << endl;
    else {
        for(int i = 0; i < n; i++) x = parents[x];

        vector<int> cycle;
        for(int v = x;; v = parents[v]) {
            cycle.push_back(v);
            if(v == x && cycle.size() > 1) break;
        }

        reverse(cycle.begin(), cycle.end());

        cout << YES << endl;
        for(int v: cycle) cout << v + 1 << " ";
        cout << endl;
    }
}

int main() {
    int a, b, c;
    cin >> n >> m;

    for(int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        edges.push_back(edge(a - 1, b - 1, c));
    }

    bellman_ford();
}