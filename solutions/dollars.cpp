#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>
#include <algorithm>
#include <math.h>
#include <map>
#include <queue>
#include <sstream>

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
const int MAXN = 6001;
const int MAXC = 11;
const int mod  = 1e9 + 7;
const double PI = 3.14159265359;

int five_comb[MAXC] = {1, 2, 4, 10, 20, 40, 100, 200, 400, 1000, 2000};
ll comb[MAXN] = {1};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    double c; cin >> c;

    forn(i, 0, MAXC) 
        forn(j, five_comb[i], MAXN)
            comb[j] += comb[j - five_comb[i]];

    cout << fixed << showpoint << setprecision(2);
    while(c) {
        cout << setw(6) << c << setw(17) <<  comb[(int)(c * 20 + 0.5f)] << endl;;
        cin >> c;
    }
}