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
    double a = island[i].first - island[j].first;
    double b = island[i].second - island[j].second;
    return sqrt(a*a + b*b);
}

// state 0 = ni b1 ni b2 se visitaron
// state 1 = b1 en la ida, b2 en la vuelta
// state 2 = b2 en la ida, b1 en la vuelta
// state 3 = ambos en el mismo camino

// choiche sirve para reconstruir la solución
// 0 es camino de ida, 1 camino de vuelta

double btsp(int i, int j, int state) {
    if (i == n-1) {
        if (b1 == j and state == 1) return INF;
        if (b2 == j and state == 2) return INF;    
        return dist(j, n-1);
    }

    if (visited[i][j][state] == tcase) return memo[i][j][state];

    visited[i][j][state] = tcase;

    int new_state = state;

    // Camino de ida
    if (i+1 == b1) {
        // Si ya habíamos puesto b2 en la ida
        new_state = state == 2 ? 3 : 1;
    } else if (i+1 == b2) {
        // Si ya habíamos puesto b1 en la ida
        new_state = state == 1 ? 3 : 2;
    }

    double res = INF;

    if (new_state != 3) {
        res = dist(i, i+1) + btsp(i+1, j, new_state);
        choice[i][j][state] = 0;
    }

    new_state = state;

    // Camino de vuelta
    if (i+1 == b1) {
        // Si ya habíamos puesto b2 en la vuelta
        new_state = state == 1 ? 3 : 2;
    } else if (i+1 == b2) {
        // Si ya habíamos puesto b1 en la vuelta
        new_state = state == 2 ? 3 : 1;
    }

    if (new_state != 3) {
        double coming_cost = dist(j, i+1) + btsp(i+1, i, new_state);

        if (coming_cost < res) {
            res = coming_cost;
            choice[i][j][state] = 1;
        }
    }

    return memo[i][j][state] = res;
}

void build_path(int i, int j, int state) {
    if (i == n-1) {
        coming.pb(n-1);
        return;
    }

    int path = choice[i][j][state];
    int new_state = state;

    if (path == 0) {
        // Camino de ida
        if (i+1 == b1) {
            // Si ya habíamos puesto b2 en la ida
            new_state = state == 2 ? 3 : 1;
        } else if (i+1 == b2) {
            // Si ya habíamos puesto b1 en la ida
            new_state = state == 1 ? 3 : 2;
        }

        going.pb(i+1);
        build_path(i+1, j, new_state);
    } else {
        // Camino de vuelta
        if (i+1 == b1) {
            // Si ya habíamos puesto b2 en la vuelta
            new_state = state == 1 ? 3 : 2;
        } else if (i+1 == b2) {
            // Si ya habíamos puesto b1 en la vuelta
            new_state = state == 2 ? 3 : 1;
        }

        coming.pb(i+1);
        build_path(i+1, i, new_state);
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

        double cost = dist(0,1) + btsp(1, 0, 0);

        cout << "Case " << tcase++ << ": " << setprecision(2) << fixed << cost << "\n";

        going = {0,1};
        coming.clear();

        build_path(1, 0, 0);

        forn(i, 0, going.size()) cout << going[i] << " ";

        for(int i = coming.size() - 1; i >= 0; i--) cout << coming[i] << " ";

        cout << "\n";

        
    }

}