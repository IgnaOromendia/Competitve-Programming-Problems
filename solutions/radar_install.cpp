#include <iostream>
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
const int MAXN = 1000;
const int mod  = 1e9 + 7;
const double PI = 3.14159265359;

pd island[MAXN];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int n,d, tcount = 1; cin >> n >> d;

    while(n+d > 0) {
        
        bool no_sol = false;

        forn(i,0,n) {
            int x,y; cin >> x >> y;

            if(d < y) no_sol = true;

            double h = sqrt(d*d - y*y);

            island[i] = mp(x-h, x+h);
        }

        sort(island, island + n);

        double last = -INF;

        int radars = 0;

        forn(i,0,n) {
            if (island[i].first <= last) {
                if (island[i].second <= last) last = island[i].second;
                continue;
            }

            radars++;
            last = island[i].second;
        }

        cout << "Case " << tcount << ": " << (no_sol ? -1 : radars) << endl;
        tcount++;
        cin >> n >> d;
    }

}