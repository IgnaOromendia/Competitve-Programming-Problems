#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <math.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > mat;
typedef pair<int,int> pi;

#define pb push_back
#define mp make_pair

#define forn(i,from,to) for (int i = from; i < to; i++)

const int INF  = 1e9;
const int MAXN = 0;
const int mod  = 1e9 + 7;
const float PI = 3.14159265359;

const int BLACK_TILE    = 0;
const int RED_TILE      = 1;

int n, m, amount;
mat map, visited;

void amount_tiles(int i, int j) {
	if (i >= n or i < 0 or j >= m or j < 0) return;
	if (visited[i][j] or map[i][j] == RED_TILE) return;

	visited[i][j] = 1;
    amount++;

	amount_tiles(i+1,j);
    amount_tiles(i-1,j);
    amount_tiles(i,j+1);
    amount_tiles(i,j-1);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    cin >> m >> n;
    int si, sj;

    while(n+m > 0) {
        map = vector<vector<int> >(n, vector<int>(m, 0));
        visited = vector<vector<int> >(n, vector<int>(m, 0));
                    
        forn(i,0,n)
            forn(j, 0, m) {
                char t; cin >> t;
                if (t == '.') map[i][j] = BLACK_TILE;
                if (t == '#') map[i][j] = RED_TILE;
                if (t == '@') {
                    map[i][j] = BLACK_TILE;
                    si = i;
                    sj = j;
                }
            }    
        
        amount = 0;
        amount_tiles(si,sj);

        cout << amount << endl;

        cin >> m >> n;
    }
}