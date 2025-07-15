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
#define remove(set, x) (set &= ~(1 << x);)

constexpr int INF  = 1e9;
constexpr int MAXT = 2001;
constexpr int MAXH = 2001;
constexpr int MAXF = 501;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

int t, h, f, acorns[MAXT][MAXH], memo[MAXT][MAXH], memo_h[MAXH];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int c; cin >> c;

    while(c--) {
        // t trees of h height losing f height in every descent
        int h; cin >> t >> h >> f;

        memset(memo, -1, sizeof(memo));
        memset(memo_h, -1, sizeof(memo_h));
        memset(acorns, 0, sizeof(acorns));

        forn(i, 0, t) {
            int n; cin >> n;
            forn(j, 0, n) {
                int a; cin >> a;
                acorns[i][a]++;
            }
        }

        // Bottom up
        
        // Base
        forn(i, 0, t) {
            memo_h[0]  = acorns[i][0];
            memo[i][0] = acorns[i][0];
        }

        forn(j, 1, h+1)  {
            forn(i, 0, t) {
                // Same tree
                memo[i][j] = max(memo[i][j],  acorns[i][j] + memo[i][j-1]);

                // Height memo
                memo_h[j] = max(memo_h[j], memo[i][j]); // Hizo que baje de 600 a 290

                // Fly
                if (j - f >= 0) memo[i][j] = max(memo[i][j], acorns[i][j] + memo_h[j-f]);

            } 
        }

        int max_a = 0;

        forn(i, 0, t) max_a = max(max_a, memo[i][h]);
        
        cout << max_a << "\n";

    }
}