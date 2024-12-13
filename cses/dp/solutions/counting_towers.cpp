#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

#define pb push_back
#define mp make_pair

#define forn(i,a,b) for (int i = a; i <= b; i++)

const int mod = 1000000007;
const int MAXN = 10e6;

ll memo[MAXN][2];

// Basicamente vemos cuantas formas tenemos de ir de un casillero dividido en 2 a otro dividido en 2 + ir a uno entero y viceversa

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int n,t; cin >> t;

    memo[1][0] = memo[1][1] = 1;

    forn(i, 1, 10e6) {
        memo[i][0] %= mod; memo[i][1] %= mod;
        memo[i+1][0] += 2 * memo[i][0] + memo[i][1];
        memo[i+1][1] += 4 * memo[i][1] + memo[i][0];
    }

    while (t--) {
        cin >> n;
        ll res = memo[n][0] + memo[n][1];
        res %= mod;
        cout << res << endl;
    }
    
}