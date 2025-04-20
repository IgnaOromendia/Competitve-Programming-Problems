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

const int INF  = 1e9;
const int MAXN = 0;
const int mod  = 1e9 + 7;
const double PI = 3.14159265359;

// Multplicative formula
ll comb(ll n, ll k) {
    if (k == 0 or k == n) return 1;
    if (k > n / 2) k = n - k;

    ll a = 1, b = 1;

    forn(i,1,k+1) {
        a *= n + 1 - i;
        b *= i;
        if (a % b == 0) {
            a /= b;
            b = 1;
        }
    }

    return a / b;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    ll n,k; cin >> n >> k;

    while(n+k) {
        cout << comb(n,k) << endl;
        cin >> n >> k;
    }

}