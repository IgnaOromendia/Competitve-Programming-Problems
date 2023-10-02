#include<iostream>
#include<vector>
#include<queue>

#define INF 1e18

using namespace std;

struct edge {
    int to;
    long long cost;
    edge(int to, int cost) : to(to), cost(cost) {}
};

vector<vector<edge> > adj;
vector<long long> distances;

void dijkstra(int s) {
    priority_queue<pair<long long, int> > min_heap;
    vector<bool> visited(adj.size(), false);

    distances[s] = 0;
    min_heap.push(make_pair(0, s));

    while(!min_heap.empty()) {
        int u = min_heap.top().second; min_heap.pop();

        if(visited[u]) continue;
        visited[u] = true;

        for(edge e: adj[u]) {
            if (distances[e.to] > distances[u] + e.cost) {
                distances[e.to] = distances[u] + e.cost;
                min_heap.push(make_pair(-distances[e.to], e.to));
            }
        }
    }
}

int main() {
    int n, m; cin >> n >> m;

    adj       = vector<vector<edge> >(2*n);
    distances = vector<long long>(2*n, INF);

    while(m--) {
        int a, b;
        long long c; 
        cin >> a >> b >> c;
        a--; b--;
        adj[a].push_back(edge(b, c));       // Take a normal flight
        adj[a].push_back(edge(b+n, c/2));   // Take a discounted flight
        adj[a+n].push_back(edge(b+n, c));   // Take a normal flight
    }

    dijkstra(0);

    cout << distances[(2*n)-1] << endl;

    return 0;
}