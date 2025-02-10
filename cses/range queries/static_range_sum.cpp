#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > mat;
typedef pair<int,int> pi;

#define pb push_back
#define mp make_pair

#define forn(i,a,b) for (int i = a; i < b; i++)

const int INF  = 1e9;
const int MAXN = 2 * 1e5;
const int mod  = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int n,q; cin >> n >> q;

    ll sums[n+2];

    sums[0] = 0;
    
    forn(i,1,n+1) {
        int x; cin >> x;
        sums[i] = sums[i-1] + x;
    }

    while(q--) {
        ll a,b; cin >> a >> b; 

        if (a < 0) a = 0;

        cout << sums[b] - sums[a-1] << endl;
    }

}