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
vector<vector<vector<pi> > > memo;

pi trends(int i, int li, int ld) {
    if (i == n) return mp(0, 0);

    pi curr_trends;
    int inc = 0, dec = 0;

    if (memo[i][li][ld].first != -1 and memo[i][li][ld].second != -1) return memo[i][li][ld];

    // Agregar el i-esimo edificio a la secuencia creciente
    if (height[i] > height[li] or li == -1) inc = width[i] + trends(i+1, i, ld).first;

    // Agregar el i-esimo edificio a la secuencia decreciente
    if (height[i] < height[ld] or ld == -1) dec = width[i] + trends(i+1, li, i).second;

    // Salterar el i-esimo edificio
    pi skip = trends(i+1, li, ld);

    return memo[i][li][ld] = mp(max(inc, skip.first), max(dec, skip.second));
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

        memo.assign(n, vector<vector<pi> >(n, vector<pi>(n, mp(-1,-1))));
    
        height.assign(n,0);
        width.assign(n,0);

        height[0] = -1;
        height[1] = INF;
        width[0] = width[1] = 0;

        forn(i,2,n) cin >> height[i];

        forn(i,2,n) cin >> width[i];

        pi building_trends = trends(2,0,1);

        print_case(t, building_trends.first, building_trends.second);

    }

}
