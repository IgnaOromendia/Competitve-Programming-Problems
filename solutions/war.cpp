#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>

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

constexpr int INF  = 1e9;
constexpr int MAXN = 0;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

struct DSU {
    int n;
    vi p, size;

    DSU() {}

    DSU(int people){
        n = people;
        p = vi(n, -1);
        size = vi(n, 1);
        forn(i, 0, n) p[i] = i;
    }

    void unite(int v, int w) {
        v = find(v), w = find(w);
        if(v == w) return;
        if(size[v] < size[w]) swap(v, w);
        p[w] = v;
        size[v] += size[w]; 
    }
    
    int find(int v) {
        return p[v] == v ? v : p[v] = find(p[v]);
    }

    bool areFirends(int u, int v) {
        return find(u) == find(v);
    }

    bool areEnemies(int u, int v, int n) {
        return find(u) == find(v + n) or find(v) == find(u + n);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int n, op, u, v; cin >> n;

    n++;
    
    // vamos a tomar los primeros n como amigos y los siguientes n como enemigos
    DSU countries = DSU(2*n);

    while(cin >> op >> u >> v, op + u + v != 0) {
        
        if (op == 1) {
            if (countries.areEnemies(u, v, n)) {
                cout << "-1\n";
                continue;
            }

            countries.unite(u, v);
            countries.unite(u + n, v + n); // Los enemigos de mis amigos son amigos
        }
        else if (op == 2) {
            if (countries.areFirends(u, v)) {
                cout << "-1\n";
                continue;
            }

            countries.unite(u, v + n);
            countries.unite(v, u + n);
        }
        else {
            bool areFirends = countries.areFirends(u, v);
            bool areEnemies = countries.areEnemies(u, v, n);

            if (areFirends and areEnemies) cout << "-1\n";
            else if (op == 3) cout << areFirends << "\n";
            else if (op == 4) cout << areEnemies << "\n";
        }
    }
}