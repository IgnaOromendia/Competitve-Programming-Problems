#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > mat;
typedef vector<vector<int> > graph;
typedef pair<int,int> pi;
typedef pair<double,double> pd;

#define pb push_back
#define mp make_pair

#define forn(i,from,to) for (int i = from; i < to; i++)

// Bitset
#define contains(set, x) (set & (1 << x))
#define add(set, x) (set |= (1 << x))
#define size(set) __builtin_popcount(set)
#define remove(set, x) (set &= ~(1 << x);)

constexpr int INF  = 1e9;
constexpr int MAXN = 2 * (1e5 + 1);
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

int visited[MAXN];
graph adj, adjT;
vi order, strong_component;
int n, visitTimer = 1;

void dfs(int v, graph& adj, bool save_order = true, bool save_sc = false) {
    visited[v] = visitTimer;

    for(int u: adj[v])
        if(visited[u] != visitTimer) {
            if (save_sc) strong_component[u] = strong_component[v];
            dfs(u, adj, save_order, save_sc);
        }
    
    if (save_order) order.push_back(v);
}

bool solve_2SAT(int offset) {
    forn(i, 0, n)
        if(visited[i] != visitTimer)
            dfs(i, adj);

    visitTimer++;
    int count = 0;

    for(int i = n-1; i >= 0; i--) {
        int v = order[i];
        if(visited[v] != visitTimer) {
            count++;
            strong_component[v] = count;
            dfs(v, adjT, false, true);
        }
    }

    forn(xi, 0, offset) 
        if (strong_component[xi] == strong_component[xi + offset])
            return false;

    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int t, tcase = 1; cin >> t;

    memset(visited, 0, sizeof(visited));
    
    while(t--) {
        int m; cin >> n >> m;

        int offset = n;

        n *= 2;

        // Los primeros n son los flyovers y los segundos n son subway
        adj.assign(n, vi());
        adjT.assign(n, vi());
        order.reserve(n);
        strong_component.assign(n, -1);

        while(m--) {
            int w1, w2; cin >> w1 >> w2;
            int x1 = abs(w1) - 1 + offset * (w1 > 0); 
            int x2 = abs(w2) - 1 + offset * (w2 > 0); 

            int nx1 = x1 >= offset ? x1 - offset : x1 + offset;
            int nx2 = x2 >= offset ? x2 - offset : x2 + offset;

            adj[nx1].pb(x2);
            adj[nx2].pb(x1);
            adjT[x2].pb(nx1);
            adjT[x1].pb(nx2);
        }

        bool twoSat = solve_2SAT(offset);

        cout << "Case " << tcase++ << ": " << (twoSat ? "Yes" : "No") << "\n";

        order.clear();
        visitTimer++;
    }
    
}