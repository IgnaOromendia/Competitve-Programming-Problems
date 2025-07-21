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
#define remove(set, x) (set &= ~(1 << x))

constexpr ll INF  = 1e18;
constexpr int MAXN = 1001;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

int n, visitTimer = 1, position[MAXN], weight[MAXN], visited[MAXN][MAXN];
ll memo[MAXN][MAXN], sum[MAXN], sumX[MAXN];

// Vamos a querer caluclar el costo de juntar desde i a j en j
// sum_t=i^j W_t * (X_j - X_t) =
// (sum_t=i^j W_t) * X_j - ( sum_t=i^j W_t) * X_t
void preprocess_costs() {
    sum[0]  = weight[0];
    sumX[0] = 1LL * weight[0] * position[0];

    forn(i,1,n) {
        sum[i]  = sum[i-1] + weight[i];
        sumX[i] = 1LL * sumX[i-1] + weight[i] * position[i];
    }
}

void min_cost(int k, int l, int r, int opt_l, int opt_r) {
    if (l > r) return;

    int mid = (l + r) / 2;

    if (mid == 0) {
        visited[mid][k] = visitTimer;
        return;
    }

    ll min_c = INF;
    int opt = -1;

    forn(j, opt_l, min(opt_r, mid - 1) + 1) {
        if (visited[j][k - 1] != visitTimer)
            min_cost(k - 1, j, j, 0, 0);

        ll weight_ij = sum[mid - 1] - (j > 0 ? sum[j - 1] : 0);
        ll weight_pos_ij = sumX[mid - 1] - (j > 0 ? sumX[j - 1] : 0);
        ll cost = weight_ij * position[mid - 1] - weight_pos_ij;
        ll curr = memo[j][k - 1] + cost;

        if (curr < min_c) {
            min_c = curr;
            opt = j;
        }
    }

    memo[mid][k]    = min_c;
    visited[mid][k] = visitTimer;

    min_cost(k, l, mid - 1, opt_l, opt);
    min_cost(k, mid + 1, r, opt, opt_r);
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    int k;

    memset(visited, 0, sizeof(visited));

    while(cin >> n >> k) {
        forn(i, 0, n) cin >> position[i] >> weight[i];

        preprocess_costs();

        memo[0][0] = 0;
        visited[0][0] = visitTimer;

        forn(i, 1, n+1) {
            memo[i][0] = INF;
            visited[i][0] = visitTimer;
        }
           
        forn(i, 1, k+1) min_cost(i, 1, n, 0, n-1);

        cout << memo[n][k] << '\n';

        visitTimer++;
    }

}