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
vector<vector<long long> > distances;
vector<pair<int,int> > queries;

// Floyd-Warshall algorithm O(n^3)
void floy_warshall() {
    int n = adj.size();
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                distances[i][j] = min(distances[i][j], distances[i][k] + distances[k][j]);
            }
        }
    }
}

int main() {
    int n, m, q; cin >> n >> m >> q;

    adj       = vector<vector<edge> >(n);
    distances = vector<vector<long long> >(n, vector<long long>(n, INF));

    for(int i = 0; i < n; i++) distances[i][i] = 0;

    while(m--) {
        int a, b;
        long long c; 
        cin >> a >> b >> c;
        a--; b--;
        adj[a].push_back(edge(b, c));
        adj[b].push_back(edge(a, c));
        distances[a][b] = min(distances[a][b], c);
        distances[b][a] = min(distances[b][a], c);
    }

    int i = 0;
    while(i < q) {
        int a, b; cin >> a >> b;
        a--; b--;
        queries.push_back(make_pair(a, b));
        i++;
    }

    floy_warshall();

    for(int i = 0; i < q; i++) {
        int a = queries[i].first;
        int b = queries[i].second;

        if(distances[a][b] == INF) cout << -1 << endl;
        else cout << distances[a][b] << endl;
    }
}