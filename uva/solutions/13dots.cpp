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
constexpr int MAXN = 101, MAXM = 10201;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

int price[MAXN], favour[MAXN], budget, n, memo[MAXN][MAXM];

int knapsack(int i, int sum) {
    // cout << sum << end l;

    // Si se pasa del presupuesto y no podía llegar a tener un reembolso
    if (sum > budget and budget <= 1800) return -INF;

    // Si se pasa del presupesto + el posible reembolso
    if (sum > budget + 200) return -INF;

    // Caso base + preguntar si nos pasamos
    if (i == n) {
        // cout << sum << " ret: " << ((sum < 2000 and sum > budget) ? "-inf" : "0") << endl;
        return (sum <= 2000 and sum > budget) ? -INF : 0;
    }

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