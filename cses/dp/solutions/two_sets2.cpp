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
const int MAXN = 501;
const int mod  = 1000000007;

int n;
mat memo;

ll equal_sum(int i, int t) {
    if (t < 0) return 0;
    if (i == 0) return t == 0;

    if (memo[i][t] != -1) return memo[i][t];

    ll add_s1 = equal_sum(i-1, t-i) % mod;
    ll add_s2 = equal_sum(i-1, t) % mod;    

    return memo[i][t] = (add_s1 + add_s2) % mod;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    cin >> n;

    int max_sum = n * (n + 1) / 2;
    int sum_set = max_sum / 2;

    if (max_sum % 2 != 0) {
        cout << 0 << endl;
        return 0;
    }

    memo.assign(n+1, vi(sum_set+1, -1));

    ll res = equal_sum(n, sum_set);

    // División modular o algo asi que encontre por internet
    res = (res * ((mod + 1) / 2)) % mod;

    cout << res << endl;
    return 0;
}