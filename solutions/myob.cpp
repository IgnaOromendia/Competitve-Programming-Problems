#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <tuple>
#include <set>

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
constexpr int MAXN = 5 * 1e4 + 1;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

int n; 
mat adj; 
vi tin, low, visited, color, isCutPoint;
int timer;

// Contar solo los q estan adyacentes a exactamente uno de los pts de art

void dfs_cutpoints(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    int children = 0;
    for (int to : adj[v]) {
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs_cutpoints(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] >= tin[v] && p!=-1) isCutPoint[v] = true;
            children++;
        }
    }
    if(p == -1 && children > 1) isCutPoint[v] = true;
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

int dfs(int v, set<int>& cutPoints) {
    visited[v] = true;
    int nodes = 1;
    for(int to: adj[v]) {
        if (isCutPoint[to]) cutPoints.insert(to);
        if (!visited[to] and !isCutPoint[to]) nodes += dfs(to, cutPoints);
    }
        
    return nodes;
}

pair<ll, int> count_ways_shaft() {
    visited.assign(n, 0);
    int shafts = 0, nodes;
    ll ways = 1;
    set<int> cutPoints;

    forn(i,0,n)
        if (!visited[i] and !isCutPoint[i]) {
            cutPoints.clear();
            nodes = dfs(i, cutPoints);
            if (cutPoints.size() == 1) {
                shafts++;
                ways *= nodes;
            }
        }

    if (shafts == 0) {
        ways   = 1LL * n * (n - 1) / 2;
        shafts = 2;
    }
            
    return mp(ways, shafts);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int t = 1, shafts, m;
    ll ways;

    while(cin >> m, m) {
        adj.assign(MAXN, vi());
        isCutPoint.assign(MAXN, 0);

        n = 0;

        forn(i, 0, m) {
            int u,v; cin >> u >> v; u--;v--;
            n = max(n, max(u,v) + 1);
            adj[u].pb(v);
            adj[v].pb(u);
        }

        find_cutpoints();

        auto [ways, shafts] = count_ways_shaft();
        
        cout << "Case " << t++ << ": " << shafts << " " << ways << "\n";

    }
}