#include<iostream>
#include<vector>
#include<queue>

#define INF 1e9

// k caminos minimos

using namespace std;
using edge = pair<int,int>;

vector<int> costs;
vector<pair<long long, long long> > dist;
vector<vector<edge> > adj;
edge marked_edge;

// Dijkstra's algorithm O(E log V)
void dijkstra(int s) {
    priority_queue<pair<long long, int> > min_heap;
    vector<bool> visited(adj.size(), false);

    dist[s] = make_pair(0,1);
    min_heap.push(make_pair(0, s));
    
    while(!min_heap.empty()) {
        int u = min_heap.top().second; min_heap.pop();

        if(visited[u]) continue;
        visited[u] = true;

        for(edge e: adj[u]) {
            int w = e.first; int cost = e.second;
            if (dist[w].first == dist[u].first) dist[w].second += dist[u].second;
            else if (dist[w].first > dist[u].first + cost) {
                dist[w].first = dist[u].first + cost;
                dist[w].second = dist[u].second;
                min_heap.push(make_pair(-dist[w].first, w));
            }
        }
    }
}






int main() {
    int n, m, k; cin >> n >> m >> k;

    adj.assign(n, vector<edge>());

    while(m--) {
        int a, b;
        long long c; 
        cin >> a >> b >> c;
        a--; b--;
        adj[a].push_back(edge(b, c));
    }


    for(int i = 0; i < k; i++) {
        cout << costs[i] << " ";
    }
    cout << endl;
}