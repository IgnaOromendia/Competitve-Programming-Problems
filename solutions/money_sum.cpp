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
const int MAXN = 100;

// Veamos si se puede sumar el valor s con i monedas
// este top-down me da TLE
// int check_sum(int i, int s, int *values, int *used) {
//     if (i == 0) return s == 0;

//     if (memo[i][s] != -1) return memo[i][s];

//     memo[i][s] = 0;

//     forn(j, 0, n) {
//         if (used[j]) continue;
//         used[j] = 1;
//         int usingcoin = check_sum(i - 1, s - values[j], values, used);
//         used[j] = 0;
//         memo[i][s] = memo[i][s] or check_sum(i - 1, s, values, used) or usingcoin;
//     }
        
//     return memo[i][s];
// }

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int n;cin >> n;

    int values[n]; 

    int sum = 0;
    
    forn(i,0, n) {
        cin >> values[i];
        sum += values[i];
    }
    int memo[n+1][sum+1];

    memset(memo, 0, sizeof(memo));

    memo[0][0] = true;

    for (int i = 1; i <= n; i++) 
        for (int j = 0; j <= sum; j++) {
            // Si ya era posible con i-1 monedas se puede con i
            memo[i][j] = memo[i - 1][j];

            // Si podemos usar una moneda la usamos
            if (j >= values[i - 1] and memo[i - 1][j - values[i - 1]]) 
                memo[i][j] = true;
            
        }

    int sums[sum+1];

    memset(sums, 0, sizeof(sums));

    int possible_sums = 0;
    forn(i,1,n+1) 
        forn(j,1,sum+1) 
            if (memo[i][j] == 1) sums[j] = 1;
        
    forn(i,0,sum+1) possible_sums += sums[i];

    cout << possible_sums << endl;
    forn(i,0,sum+1) if (sums[i]) cout << i << " ";
    
    cout << endl;

    return 0;
}