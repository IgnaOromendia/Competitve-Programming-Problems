#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <queue>
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

constexpr int INF  = 1e9;
constexpr int MAXT = 500;
constexpr int MAXN = 100 * 100 * MAXT; // Nodos * Tiempo máximo
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

int bfs(int nv, int nh, int* monitor, mat& restriction) {
    int offset = nh * nv, escape = offset - 1;
    pi dir[5] = {{-1,0}, {0,1}, {1,0}, {0,-1}, {0,0}}; // arriba, derecha, abajo, izquierda, esperar
    bitset<MAXN> visited; // Redujo casi la mitad del tiempo
    queue<pi> q; // nodo - timer

    visited.set(0);
    q.push(mp(0,0));

    while(!q.empty()) {
        auto [u, timer] = q.front(); q.pop();

        // Posición de u en la grilla
        int x = u % nv, y = u / nv;
 
        for (auto [dx, dy] : dir) {
            
            // Valida movimiento
            int new_x = x + dx, new_y = y + dy;
            if (new_x < 0 or new_x >= nv or new_y < 0 or new_y >= nh) continue;

            int w = (new_x + nv * new_y);

            // Nos fijamos que no esté monitoreado
            if (monitor[timer+1] == w) continue;

            // Nos fijamos que no sea una calle restringida
            bool restricted_street = false;
            forn(i, 0, restriction[u].size()) 
                if (restriction[u][i] == w) {
                    restricted_street = true;
                    break;
                }
            
            if (restricted_street) continue;

            // Como es grafo implicito una vez q llegamos al escape tenemos q salir
            if (w == escape) {
                return timer + 1; 
            }

            // Vamos al nivel corresponidientes
            w += (timer + 1) * offset;            
            
            // Si no fue visitado actualizamos
            if (not visited.test(w)) {
                visited.set(w);
                q.push(mp(w % offset, timer + 1));
            }
        }
    }

    return 0;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int nv, nh, r, m;
    
    while(cin >> nv >> nh) {
        cin >> r;
        mat restriction(nh*nv);

        while(r--) {
            int x1,y1,x2,y2; cin >> x1 >> y1 >> x2 >> y2;
            restriction[x1 + nv * y1].pb(x2  + nv * y2);
        }

        cin >> m;
        int monitor[MAXT];
        memset(monitor, 0, sizeof(monitor));
        // Antes era umap era 6 veces más lento

        while(m--) {
            int t,x,y; cin >> t >> x >> y;
            monitor[t] = x + nv * y;
        }

        int time = bfs(nv, nh, monitor, restriction);

        cout << time << "\n";
    }

}