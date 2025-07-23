#include <iostream>
#include <vector>
#include <cstring>
#include <bitset>
#include <math.h>
#include <iomanip>

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
constexpr int MAXN = 101;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

double memo[MAXN][MAXN][4];
int visited[MAXN][MAXN][4], choice[MAXN][MAXN][4];
int n, b1, b2, tcase = 1;
pi island[MAXN];
vi going, coming;

double dist(int i, int j) {
    return hypot(island[i].first - island[j].first, island[i].second - island[j].second);
}

// state 0 = ni b1 ni b2 se visitaron
// state 1 = b1 en la ida, b2 en la vuelta
// state 2 = b2 en la ida, b1 en la vuelta
// state 3 = ambos en el mismo camino

// choiche sirve para reconstruir la solución
// 0 es camino de ida, 1 camino de vuelta

double btsp(int i, int j, int state) {
    if(max(i, j) == n - 1) {
        if(state == 0 or state == 3) return INF;
        return dist(i, n-1) + dist(j, n-1);
    }
    
    if(visited[i][j][state] == tcase) return memo[i][j][state];
    visited[i][j][state] = tcase;
    
    int next = max(i, j) + 1;
    double result = INF;
    
    int new_state = state;
    // Camino de ida
    if (next == b1) {
        // Si ya habíamos puesto b2 en la ida
        new_state = state == 2 ? 3 : 1;
    } else if (next == b2) {
        // Si ya habíamos puesto b1 en la ida
        new_state = state == 1 ? 3 : 2;
    }
    
    if(new_state != 3) {
        result = dist(i, next) + btsp(next, j, new_state);
        choice[i][j][state] = 0;
    }
    
    new_state = state;
    // Camino de vuelta
    if (next == b1) {
        // Si ya habíamos puesto b2 en la vuelta
        new_state = state == 1 ? 3 : 2;
    } else if (next == b2) {
        // Si ya habíamos puesto b1 en la vuelta
        new_state = state == 2 ? 3 : 1;
    }
    
    if(new_state != 3) {
        double cost = dist(j, next) + btsp(i, next, new_state);
        if(cost < result) {
            result = cost;
            choice[i][j][state] = 1;
        }
    }
    
    return memo[i][j][state] = result;
}

void build_path(int i, int j, int state) {
    if (max(i, j) == n-1) return;

    int next = max(i, j) + 1;
    int path = choice[i][j][state];
    int new_state = state;

    if (path == 0) {
        // Camino de ida
        if (next == b1) {
            // Si ya habíamos puesto b2 en la ida
            new_state = state == 2 ? 3 : 1;
        } else if (next == b2) {
            // Si ya habíamos puesto b1 en la ida
            new_state = state == 1 ? 3 : 2;
        }

        going.pb(next);
        build_path(next, j, new_state);
    } else {
        // Camino de vuelta
        if (next == b1) {
            // Si ya habíamos puesto b2 en la vuelta
            new_state = state == 1 ? 3 : 2;
        } else if (next == b2) {
            // Si ya habíamos puesto b1 en la vuelta
            new_state = state == 2 ? 3 : 1;
        }

        coming.pb(next);
        build_path(i, next, new_state);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    memset(visited, 0, sizeof(visited));

    while(cin >> n >> b1 >> b2, n + b1 + b2 != 0) {

        forn(i, 0, n) {
            int x,y; cin >> x >> y;
            island[i] = {x,y};
        }

        double cost = btsp(0, 0, 0);

        cout << "Case " << tcase++ << ": " << setprecision(2) << fixed << cost << "\n";

        going = {0};
        coming.clear();

        build_path(0, 0, 0);

        // Imprimimos el camino

        forn(i, 0, going.size()) cout << going[i] << " ";

        for(int i = coming.size() - 1; i >= 0; i--) cout << coming[i] << " ";

        cout << "0\n";

        
    }

}