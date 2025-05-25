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
constexpr int MAXN = 5 * 1e4;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

int n; 
mat adj; 
vi tin, low, visited, children, iscutpoint;
int timer;

// Contar solo los q estan adyacentes a exactamente uno de los pts de art

void dfs_cutpoints(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    for (int to : adj[v]) {
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs_cutpoints(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] >= tin[v] && p!=-1) iscutpoint[v] = true;
            children[v]++;
        }
    }
    if(p == -1 && children[v] > 1) iscutpoint[v] = true;
}

void find_cutpoints() {
    timer = 0;
    visited.assign(n, 0);
    tin.assign(n, -1);
    low.assign(n, -1);
    forn(i, 0, n) 
        if (!visited[i])
            dfs_cutpoints (i);   
}

int dfs(int v) {
    visited[v] = true;
    int nodes = 1;
    for(int to: adj[v])
        if (!visited[to] and !iscutpoint[to])
            nodes += dfs(to);
    return nodes;
}

pair<ll, int> count_ways_shaft() {
    visited.assign(n, 0);
    ll nodes = 1;
    int shafts = 0;

    forn(i,0,n)
        if (!visited[i] and !iscutpoint[i]) {
            shafts++;
            nodes *= dfs(i);
        }
            
    return mp(nodes, shafts);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int t = 1, shafts;
    ll ways;

    while(cin >> n, n) {
        adj.assign(MAXN, vi());
        children.assign(MAXN, 0);
        iscutpoint.assign(MAXN,0);

        forn(i, 0, n) {
            int u,v; cin >> u >> v; u--;v--;
            adj[u].pb(v);
            adj[v].pb(u);
        }

        find_cutpoints();

        tie(ways, shafts) = count_ways_shaft();

        forn(v, 0, n) shafts += iscutpoint[v];
        

        cout << "Case " << t++ << ": " << shafts << " " << ways << "\n";

    }
}