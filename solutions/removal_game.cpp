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

const int INF = 1e9;
const int MAXN = 5000;

ll values[MAXN];
ll memo[MAXN][MAXN];

ll max_score_player1(int r, int l) {
    if (r > l) return 0;

    if (memo[r][l] != -1) return memo[r][l];

    // Tomamos el min porque el oponente juega optimo 
    ll right = values[r] + min(max_score_player1(r+2,l), max_score_player1(r+1,l-1));
    ll left = values[l] + min(max_score_player1(r+1,l-1), max_score_player1(r,l-2));

    return memo[r][l] = max(right,left);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int n; cin >> n;

    forn(i,0,n) cin >> values[i];

    memset(memo, -1, sizeof(memo));

    cout << max_score_player1(0,n-1) << endl;
}