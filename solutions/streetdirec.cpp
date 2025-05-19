#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > mat;
typedef pair<int,int> pi;
typedef pair<double,double> pd;

#define pb push_back
#define mp make_pair

#define forn(i,from,to) for (int i = from; i < to; i++)

constexpr int INF  = 1e9;
constexpr int MAXN = 1000;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

int n, timer; 
mat adj; 
vi tin, low, visited;

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    for (int to : adj[v]) {
        if (to == p) continue;
        if (visited[to]) {
            // Chequeamos que sea backedge
            if(tin[to] > tin[v]) cout << to + 1 << " " << v + 1 << "\n";
            low[v] = min(low[v], tin[to]);
        } else {
            // Treeedge
            cout << v + 1 << " " << to + 1 << "\n";
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            // Chequeamos que sea puente
            if (low[to] > tin[v]) cout << to + 1 << " " << v + 1 << "\n";
        }
    }
}

void find_bridges() {
    timer = 0;
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    forn(i, 0, n) {
        if (!visited[i]) dfs(i);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int m, t = 1;

    while(cin >> n >> m, n+m != 0) {
        adj.assign(n,vi());

        while(m--) {
            int u,v; cin >> u >> v;
            u--;v--;
            adj[u].pb(v);
            adj[v].pb(u);
        }

        cout << t++ << "\n\n";

        find_bridges();

        cout << "#\n";

    }
}