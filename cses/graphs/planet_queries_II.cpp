#include<iostream>
#include<vector>

using namespace std;
using query = pair<int, int>;

vector<query> queries;
vector<int> results;
vector<int> adj;
vector<vector<int> > memo;

int travel(int from, int to, int p = -1) {
    if (from == to) return 0;
    
    // Cycle detection
    if (adj[from] == p or adj[from] == from) return -1;

    if (memo[from][to] == -2) {
        int dist = travel(adj[from], to, from);
        memo[from][to] = dist == -1 ? -1 : 1 + dist;
    }

    return memo[from][to];
}

void minimum_path() {
    for(query &q: queries) {
        cout << travel(q.first, q.second) << endl;
    }
}

int main() {
    int n, q;
    cin >> n >> q;

    adj.assign(n+1, -1);
    memo.assign(n+1, vector<int>(n+1, -2));

    for(int i = 1; i <= n; i++) {
        int v; cin >> v;
        adj[i] = v;
    }

    while(q--) {
        int x, k; cin >> x >> k;
        queries.push_back(make_pair(x,k));
    }

    minimum_path();

}