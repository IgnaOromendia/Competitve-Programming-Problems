#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <math.h>
#include <map>
#include <queue>
#include <sstream>
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

const int INF  = 1e9;
const int MAXN = 7, MAXM = 7;
const int mod  = 1e9 + 7;
const double PI = 3.14159265359;

int grid[MAXN][MAXM], visited[MAXN][MAXM], n, m;;

int number_of_paths(int i, int j) {
    if (i == n - 1 and j == m-1) return 1;
    
    if (visited[i][j] or grid[i][j] == 0) return 0;

    visited[i][j] = 1;

    int paths = 0;

    if (i > 0) paths += number_of_paths(i-1,j);
    if (i < n-1) paths += number_of_paths(i+1,j);
    if (j > 0) paths += number_of_paths(i,j-1);
    if (j < m-1) paths += number_of_paths(i,j+1);

    visited[i][j] = 0;

    return paths; 
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    memset(visited, 0, sizeof(visited));

    cin >> n >> m;

    forn(i,0,n)
        forn(j,0,m)
            cin >> grid[i][j];

    cout << number_of_paths(0,0) << "\n";
}