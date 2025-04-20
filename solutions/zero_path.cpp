#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <math.h>
#include <set>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > mat;
typedef pair<int,int> pi;
typedef pair<double,double> pd;

#define pb push_back
#define mp make_pair

#define forn(i,from,to) for (int i = from; i < to; i++)

constexpr int INF  = 1e7;
constexpr int MAXN = 1000;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

int n, m;
mat memo_max, memo_min;
int grid[MAXN][MAXN];

int max_temp_path(int i, int j) {
    if (i == n-1 and j == m-1) return memo_max[i][j] = grid[i][j];

    if (i > n-1 or j > m-1) return -INF;

    if (memo_max[i][j] != -INF) return memo_max[i][j];

    return memo_max[i][j] = grid[i][j] + max(max_temp_path(i,j+1), max_temp_path(i+1,j));
}

int min_temp_path(int i, int j) {
    if (i == n-1 and j == m-1) return memo_min[i][j] = grid[i][j];

    if (i > n-1 or j > m-1) return INF;

    if (memo_min[i][j] != INF) return memo_min[i][j];

    return memo_min[i][j] = grid[i][j] + min(min_temp_path(i,j+1), min_temp_path(i+1,j));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int t; cin >> t;

    while(t--) {
        cin >> n >> m;

        memo_max.assign(n, vi(m, -INF));
        memo_min.assign(n, vi(m, INF));

        forn(i,0,n) 
            forn(j,0,m) 
                cin >> grid[i][j];

        int max_temp = max_temp_path(0,0);
        int min_temp = min_temp_path(0,0);
                        
        if (max_temp % 2 == 0 and min_temp % 2 == 0 and min_temp <= 0 and max_temp >= 0)
            cout << "YES" << "\n";
        else
            cout << "NO" << "\n";
            
    }
}