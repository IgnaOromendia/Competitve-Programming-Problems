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
#define remove(set, x) (set &= ~(1 << x))

#define NOT_VISITED  0
#define VISITING  1
#define VISITED  2

constexpr int INF  = 1e9;
constexpr int MAXN = 2e5 + 5;;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;
constexpr int LOG = 30;

int n, q;
int teleport[MAXN],  root[MAXN], state[MAXN];
int up[MAXN][LOG]; // up[v][k] = planeta al que se llega desde v con 2^k saltos
int cycle_dist[MAXN], cycle_pos[MAXN], cycle_len[MAXN];

void print_cycle(string message) {
    cout << message << endl;
    forn(i, 0, n) cout << cycle_dist[i] << " ";
    cout << endl;
}

// Uso binary lifting como en Planet Queries I
void dfs(int v) {
    state[v] = VISITING;
    up[v][0] = teleport[v];
    int u = teleport[v];

    if (state[u] == NOT_VISITED) {
        dfs(u);
        if (cycle_dist[v] != 0) {
            root[v] = root[u];
            cycle_dist[v] = cycle_dist[u] + 1;
        }
    } else if (state[u] == VISITING) {
        int w = v, len = 0;

        do {
            root[w] = v;
            cycle_pos[w] = len;
            cycle_dist[w] = 0;
            w = teleport[w];
            len++;
        } while (w != v);

        cycle_len[v] = len;

    } else { // VISITED
        cycle_dist[v] = cycle_dist[u] + 1;
        root[v] = root[u];
    }

    state[v] = VISITED;
}

int jump(int v, int k) {
    forn(i, 0, LOG) 
        if (k & (1 << i))
            v = up[v][i];

    return v;
}

void binary_lifting() {
    forn(k, 1, LOG)
        forn(v, 1, n+1)
            up[v][k] = up[up[v][k-1]][k-1];
}
 
int dist(int a, int b) {
    if (a == b) return 0;
    
    // Inalcanzables
    if (root[a] != root[b]) return -1; 

    // El target está hacia atrás
    if (cycle_dist[a] < cycle_dist[b]) return -1; 

    // Calculo distancia para ver si está en el camino al ciclo
    int diff = cycle_dist[a] - cycle_dist[b];
    int u = jump(a, diff);
    if (u == b) return diff;

    // Si alguno de los 2 no está en un ciclo es inalcanzable
    if (cycle_dist[u] != 0 or cycle_dist[b] != 0) return -1;

    int cycle_diff = (cycle_pos[b] - cycle_pos[u] + cycle_len[root[u]]) % cycle_len[root[u]];
    return diff + cycle_diff;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    forn(i,1,n+1) cin >> teleport[i];

    memset(state, NOT_VISITED, sizeof(state));
    memset(cycle_dist, -1, sizeof(cycle_dist));

    // Preprocess
    forn(i, 1, n+1) 
        if (state[i] == NOT_VISITED) 
            dfs(i);

    binary_lifting();
    
    while (q--) {
        int a, b; cin >> a >> b;
        cout << dist(a, b) << '\n';
    }

    return 0;
}