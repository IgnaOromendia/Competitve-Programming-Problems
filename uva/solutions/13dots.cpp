#include <iostream>
#include <vector>
#include <cstring>

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
constexpr int MAXN = 100, MAXM = 10200;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

int price[MAXN], favour[MAXN], budget, n, memo[MAXN][MAXM];

int knapsack(int i, int sum) {
    if (sum > budget + 200) return -INF;

    if (i == n and sum < budget + (sum > 2000 ? 200 : 0)) return 0;
    if (i == n and sum > budget + (sum > 2000 ? 200 : 0)) return -INF;

    if (memo[i][sum] != -1) return memo[i][sum];

    return memo[i][sum] = max(favour[i] + knapsack(i+1, sum + price[i]), knapsack(i+1, sum));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

   while (cin >> budget >> n) {
    
        forn(i,0,n) {
            cin >> price[i];
            cin >> favour[i];
        }

        memset(memo, -1, sizeof(memo));

        cout << knapsack(0, 0) << "\n";
   }

    
}