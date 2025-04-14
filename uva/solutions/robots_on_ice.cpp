#include <iostream>
#include <vector>
#include <cstring>
#include <math.h>

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
constexpr int MAXN = 9;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

int n,m, visited[MAXN][MAXN]; 
pi check_in[3];

int amount_of_ice_paths(int i, int j, int old_i, int old_j, int v_count) {
    if (i == 0 and j == 1) return v_count == (n * m) - 1;
    
    // Si llegamos a una fila donde no podemos avanzar 
    // y ambos lados están sin visitar entonces ya no voy 
    // a poder recorrer todas las celdas
    if (j < n-1 and j > 0 and !visited[i][j-1] and !visited[i][j+1]) {
        // Borde
        if (i == 0 or i == m-1 ) return 0;
        // No poder avanzar por visitado al frente
        if (visited[i-1][j] and i-1 != old_i) return 0;
        if (visited[i+1][j] and i+1 != old_i) return 0;
    }
        
    // Mismo que antes pero con las columnas
    if (i < m-1 and i > 0 and !visited[i-1][j] and !visited[i+1][j]) {
        // Borde
        if (j == 0 or j == n-1) return 0;
        // No poder avanzar por visitado al frente
        if (visited[i][j-1] and j-1 != old_j) return 0;
        if (visited[i][j+1] and j+1 != old_j) return 0;
    }

    // Chequeamos que se respete los puntos check-in 
    pi point = mp(i,j);

    forn(k,0,3)
        if (!visited[check_in[k].first][check_in[k].second]) {
            int dist = abs(i - check_in[k].first) + abs(j - check_in[k].second);
            // cout << point.first << "," << point.second << " " << check_in[k].first << "," << check_in[k].second  << " " << dist + v_count + 1 << " <? " << floor((k+1) * n * m / 4) << endl;
            if (dist + v_count + 1 > floor((k+1) * n * m / 4)) return 0;
        }

    if (check_in[0] == point and v_count + 1 != floor(n * m / 4)) return 0;
    if (check_in[1] == point and v_count + 1 != floor(2 * n * m / 4)) return 0;
    if (check_in[2] == point and v_count + 1 != floor(3 * n * m / 4)) return 0;

    int paths = 0;

    visited[i][j] = 1;

    if (i < m-1 and !visited[i+1][j]) paths += amount_of_ice_paths(i+1, j, i, j, v_count+1);
    if (j < n-1 and !visited[i][j+1]) paths += amount_of_ice_paths(i, j+1, i, j, v_count+1);
    if (i > 0   and !visited[i-1][j]) paths += amount_of_ice_paths(i-1 ,j, i, j, v_count+1);
    if (j > 0   and !visited[i][j-1]) paths += amount_of_ice_paths(i, j-1, i, j, v_count+1);

    visited[i][j] = 0;

    return paths;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    cin >> m >> n;

    int test_case = 1;

    while(n+m) {
        memset(visited, 0, sizeof(visited));

        forn(i,0,3) {
            int x,y; cin >> x >> y;
            check_in[i] = mp(x,y);
        }

        cout << "Case " << test_case++ << ": " << amount_of_ice_paths(0,0,0,0,0) << "\n";

        cin >> m >> n;
    }
    
}