#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <math.h>
#include <map>
#include <queue>
#include <sstream>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > mat;
typedef pair<int,int> pi;

#define pb push_back
#define mp make_pair

#define forn(i,from,to) for (int i = from; i < to; i++)

const int INF  = 1e9;
const int MAXN = 105;
const int mod  = 1e9 + 7;
const double PI = 3.14159265359;

int grid[MAXN][MAXN];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int t; cin >> t;

    while(t--) {
        int n,k; cin >> n >> k;

        memset(grid, 0, sizeof(grid));

        int mx = 0, my = 0;

        forn(i, 0, n) {
            int x1,x2,y1,y2; cin >> x1 >> y1 >> x2 >> y2;
            mx = max(mx,x2);
            my = max(my,y2);
            if (x1 < x2)
                forn(j,x1,x2+1) grid[j][y1] = i+1;
            else 
                forn(j,x2,x1+1) grid[j][y1] = i+1;
        }

        int walls = 0;

        forn(i, 0, mx+1) {
            int curr_walls = 0;
            forn(j, 0, my+1) if (grid[i][j]) curr_walls++;
            
            int offset = curr_walls - k;

            if (offset > 0) {
                walls += offset;

                while(offset--) {
                    int max_sum = 0, max_bh;

                    forn(k, 0, my+1)
                        if (grid[i][k] > 0) {
                            int temp_sum = 0;
                            forn(z, i+1, mx+1)
                                if (grid[z][k] == grid[i][k]) temp_sum++; else break;

                            if (max_sum < temp_sum) {
                                max_sum = temp_sum;
                                max_bh = k;
                            }
                        }

                    forn(a, i, i+max_sum+1) grid[a][max_bh] = 0;
                }
            }
        }

        cout << walls << endl;
    }
}