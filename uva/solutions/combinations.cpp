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
const int MAXN = 110;
const int mod  = 1e9 + 7;
const double PI = 3.14159265359;

ll comb[MAXN][MAXN];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    forn(n,0,MAXN) comb[n][0] = 1;
    forn(n,1,MAXN)
        forn(k,1,MAXN)
            comb[n][k] = comb[n-1][k-1] + comb[n-1][k];

    int n,k; cin >> n >> k;
    
    while(n+k) {
        cout << n << " things taken " << k << " at a time is " << comb[n][k] << " exactly." << endl;
        cin >> n >> k;
    } 

}