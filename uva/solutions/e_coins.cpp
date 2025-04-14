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

constexpr int INF  = 1e9;
constexpr int MAXN = 41, MAXS = 301;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

struct ECoin {
    int conv_val, it_val;
    ECoin(int c, int it): conv_val(c), it_val(it) {}
    ECoin(): ECoin(0,0) {}
};

ECoin coins[MAXN];
int m, s, memo[MAXN][MAXS][MAXS];

int amount_of_coins(int i, int con_val, int it_val) {
    if (i == m) return (s*s == con_val*con_val + it_val*it_val) ? 0 : INF;
    if (s*s < con_val*con_val + it_val*it_val) return INF;

    if (memo[i][con_val][it_val] != -1) return memo[i][con_val][it_val];

    int amount = 1 + amount_of_coins(i, con_val + coins[i].conv_val, it_val + coins[i].it_val);

    amount = min(amount, 1 + amount_of_coins(i+1, con_val + coins[i].conv_val, it_val + coins[i].it_val));

    return memo[i][con_val][it_val] = min(amount, amount_of_coins(i+1, con_val, it_val));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int t; cin >> t;
    while(t--) {
        cin >> m >> s;

        memset(memo, -1, sizeof(memo));

        forn(i,0,m) {
            int val, it_val;  cin >> val >> it_val;
            coins[i] = ECoin(val, it_val);
        }

        int amount = amount_of_coins(0,0,0);

        cout << (amount == INF ? "not possible" : to_string(amount)) << "\n";

    }
}