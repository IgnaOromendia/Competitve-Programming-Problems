#include <iostream>
#include <vector>
#include <bitset>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<double> vd;
typedef vector<vector<int> > mat;
typedef vector<vector<double> > graph;
typedef pair<int,int> pi;
typedef pair<int,int> point;
typedef pair<double,double> pd;

#define pb push_back
#define mp make_pair

#define forn(i,from,to) for (int i = from; i < to; i++)

constexpr int INF  = 1e9;
constexpr int MAXN = 0;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

void dense_prim(int n, int r, graph& adj) {
    vector<bool> selected(n, false);
    vd tree_edges_costs(n, INF);
    tree_edges_costs[0] = 0;
    int states = 1;
    double roadLength = 0, railroadLength = 0;

    forn(i, 0, n) {
        int v = -1;

        forn(j, 0, n) 
            if (!selected[j] and (v == -1 or tree_edges_costs[j] < tree_edges_costs[v]))
                v = j;
        
        selected[v] = true;

        if (tree_edges_costs[v] <= r) roadLength += tree_edges_costs[v];
        else {
            railroadLength += tree_edges_costs[v];
            states++;
        }

        forn(u, 0, n)
            if (adj[v][u] < tree_edges_costs[u]) 
                tree_edges_costs[u] = adj[v][u];
        
    }


    cout << states << " " << (int)round(roadLength) << " " << (int)round(railroadLength) << "\n";

}

double dist(point& a, point& b) {
    return hypot(a.first - b.first, a.second - b.second);
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int n, r, t, tcase = 1; cin >> t;

    while(t--) {
        cin >> n >> r;

        vector<point> coordinates(n);
        graph adj(n, vd(n, 0));

        forn(i,0,n) {
            int x,y; cin >> x >> y;
            coordinates[i] = mp(x,y);

            forn(v, 0, i)  
                adj[v][i] = adj[i][v] = dist(coordinates[v], coordinates[i]);
        }

        cout << "Case #" << tcase++ << ": ";
        dense_prim(n, r, adj);

    }
}