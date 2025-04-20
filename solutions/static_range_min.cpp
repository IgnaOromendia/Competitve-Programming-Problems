#include <iostream>
#include <vector>
#include <cstring>
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
const int MAXN = 2 * 1e5 + 1;
const int mod  = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int n,q; cin >> n >> q;

    int k = log2(n) + 1;
    ll st[k + 1][MAXN];
    int log[MAXN + 1];    

    forn(i,0,n) cin >> st[0][i];

    forn(i,1,k+1)
        for(int j = 0; j + (1 << i) <= n; j++) 
            st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);

    log[1] = 0;
    forn(i, 2, MAXN+1)
        log[i] = log[i/2] + 1;

    while(q--) {
        ll a,b; cin >> a >> b; a--; b--;
        int i = log[b - a + 1];
        cout << min(st[i][a], st[i][b - (1 << i) + 1]) << endl;
    }

    return 0;
}