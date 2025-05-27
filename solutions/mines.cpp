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
constexpr int MAXN = 0;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

struct Mine {
    int x,y,halfd;
    
    Mine(int x, int y, int d): x(x), y(y), halfd(d/2) {}

    bool contain(const Mine& m) {
        return abs(x - m.x) <= halfd and abs(y - m.y) <= halfd;
    }
};

int n, currTimer;
mat adj;
vi order, visited;

void dfs(int v, bool saveOrder) {
    visited[v] = currTimer;

    for(int to: adj[v])
        if (visited[to] != currTimer) 
            dfs(to, saveOrder);

    if (saveOrder) order.pb(v);
}

void toposort() {
    forn(i,0,n) 
        if (visited[i] != currTimer) 
            dfs(i, true);
}

int minMines() {
    int count = 0;

    currTimer++; // Nos ahorramos el assign a visited

    for(int i = n-1; i >= 0; i--) 
        if (visited[order[i]] != currTimer) {
            count++;
            dfs(order[i], false);
        }

    return count;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int t; cin >> t;

    while(t--) {
        cin >> n;

        currTimer = 1;

        vector<Mine> mines;
        mines.reserve(n);

        adj.assign(n, vi());
        visited.assign(n, 0);

        order.clear();
        order.reserve(n);        

        forn(i,0,n) {
            int x,y,d; cin >> x >> y >> d;
            mines.emplace_back(x,y,d);
        }

        // Creamos el grafo
        forn(i,0,n) forn(j,i+1,n) {
            if (mines[i].contain(mines[j])) adj[i].pb(j);
            if (mines[j].contain(mines[i])) adj[j].pb(i);
        }

        toposort();

        cout << minMines() << "\n";
  
    }

}