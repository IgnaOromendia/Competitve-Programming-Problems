#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <math.h>

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
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;
const string increasing = "Increasing";
const string decreasing = "Decreasing";

int n;
vi height, width;
mat memo_inc, memo_dec;

int inc_trend(int i, int l) {
    if (i == n) return 0;

    if (memo_inc[i][l] != -1) return memo_inc[i][l];

    int inc = 0;

    // Agregar el i-esimo edificio a la secuencia creciente
    if (height[i] > height[l] or l == -1) inc = width[i] + inc_trend(i+1, i);

    return memo_inc[i][l] = max(inc, inc_trend(i+1,l));
}

int dec_trend(int i, int l) {
    if (i == n) return 0;

    if (memo_dec[i][l] != -1) return memo_dec[i][l];

    int dec = 0;

    // Agregar el i-esimo edificio a la secuencia decreciente
    if (height[i] < height[l] or l == -1) dec = width[i] + dec_trend(i+1, i);

    return memo_dec[i][l] = max(dec, dec_trend(i+1,l));
}


void print_case(int case_number, int inc, int dec) {
    cout << "Case " << case_number << ". "  ;
    if (inc >=  dec) cout << increasing << " (" << inc << "). " << decreasing << " (" << dec << ").\n";
    else cout << decreasing << " (" << dec << "). " << increasing << " (" << inc << ").\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int c; cin >> c;
    for(int t = 1; t <= c; t++) {
        
        cin >> n;

        n+=2;

        memo_inc.assign(n, vi(n,-1));
        memo_dec.assign(n, vi(n,-1));
    
        height.assign(n,0);
        width.assign(n,0);

        height[0] = -1;
        height[1] = INF;
        width[0] = width[1] = 0;

        forn(i,2,n) cin >> height[i];

        forn(i,2,n) cin >> width[i];

        print_case(t, inc_trend(2,0), dec_trend(2,1));

    }

}
