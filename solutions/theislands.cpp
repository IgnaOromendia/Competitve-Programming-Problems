#include <iostream>
#include <vector>
#include <cstring>
#include <bitset>
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

float memo[MAXN][MAXN][3];
int n, b1, b2;
pi island[MAXN];

float dist(int i, int j) {
    return hypot(island[i].first - island[j].first, island[i].second - island[j].second);
}

// Vamos a pensar b1path como 0 si no esta asignado, 1 si pertence a i y 2 si pertence a j
float btsp(int i, int j, int b1path) {
    if (i == n-1 && j == n-1) return 0;
    if (i == n-1) return dist(j, n-1);
    if (j == n-1) return dist(i, n-1);

    if (memo[i][j][b1path] != -1) return memo[i][j][b1path];

    if (i == b1 or j == b1) {
        float path_i = dist(i, i+1) + btsp(i+1, j, 1);
        float path_j = dist(j, i+1) + btsp(i+1, i, 2);
        return memo[i][j][b1path] = min(path_i, path_j);
    }

    // Si i va a pasar por b2 y b1 está en j
    // o si j va a pasar por b2 y b1 está en j
    // asignamos b2 a i
    if ((i == b2 or j == b2) and b1path == 2)
        return memo[i][j][b1path] = dist(j, i+1) + btsp(i+1,i, b1path);

    // Si i va a pasar por b2 y b1 está en i
    // o si j va a pasar por b2 y b1 está en i
    // asignamos b2 a j
    if ((i == b2 or j == b2) and b1path == 1)
        return memo[i][j][b1path] = dist(i, i+1) + btsp(i+1, j, b1path);


    float path_i = dist(i, i+1) + btsp(i+1, j, b1path);
    float path_j = dist(j, i+1) + btsp(i+1, i, b1path);
    return memo[i][j][b1path] = min(path_i, path_j);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int tcase = 1;

    while(cin >> n >> b1 >> b2, n + b1 + b2 != 0) {

        fill(&memo[0][0][0], &memo[0][0][0] + MAXN * MAXN * 3, -1.0f);

        forn(i, 0, n) {
            int x,y; cin >> x >> y;
            island[i] = mp(x,y);
        }

        cout << "Case " << tcase++ << ": " << setprecision(2) << fixed << btsp(0,0,0) << "\n";
    }

}