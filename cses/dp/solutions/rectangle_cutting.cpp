#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

#define pb push_back
#define mp make_pair

#define forn(i,a,b) for (int i = a; i < b; i++)

const int INF = 1e9;
const int MAXN = 501;

int memo[MAXN][MAXN];

int min_cuts(int a, int b) {
    if (a == b) return 0; 

    if (memo[a][b] != -1) return memo[a][b];

    int res = INF;
    
    forn(i, 1, b) res = min(res, min_cuts(a, i) + min_cuts(a, b - i) + 1);
    
    forn(i, 1, a) res = min(res, min_cuts(i, b) + min_cuts(a - i, b) + 1);
    
    return memo[a][b] = res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int a,b; cin >> a >> b;

    memset(memo, -1, sizeof(memo));

    cout << min_cuts(a,b) << endl;

    return 0;
}