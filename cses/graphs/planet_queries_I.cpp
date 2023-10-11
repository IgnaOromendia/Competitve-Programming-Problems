#include<iostream>
#include<vector>

using namespace std;
using query = pair<int, int>;

vector<vector<int> > memo;
vector<query> queries;
vector<int> results;
vector<int> adj;

int travel(int v, int k) {
    if (k == 0) return v;

    if (adj[v] == v) return v;

    if (memo[v][k] == -1) {
        memo[v][k] = travel(adj[v], k - 1);
    }

    return memo[v][k];
}

void destinations() {
    for(query &q: queries)
        cout << travel(q.first, q.second) << endl;
}

int main() {
    int n, q;
    cin >> n >> q;

    adj.assign(n+1, -1);

    for(int i = 1; i <= n; i++) {
        int v; cin >> v;
        //cout << i << " -> " << v << endl;
        adj[i] = v;
    }

    int max_k = 0;
    while(q--) {
        int x, k; cin >> x >> k;
        if (k > max_k) max_k = k;
        // cout << x << " " << k << endl;
        queries.push_back(make_pair(x,k));
    }

    cout << max_k << endl;

    memo.assign(n+1, vector<int>(max_k+1,-1));

    destinations();

    // for(int i = 1; i <= n; i++) {
    //     for(int j = 0; j < max_k; j++) {
    //         cout << memo[i][j] << " ";
    //     }
    //     cout << endl;
    // }
}