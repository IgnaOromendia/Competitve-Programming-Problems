#include <iostream>
#include <vector>
#include <algorithm>

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
constexpr int MAXG = 1e4;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int l,g; 

    pi coverage[MAXG];
    
    while (cin >> l >> g, l + g) {

        forn(i,0,g) {
            int x,r; cin >> x >> r;
            coverage[i] = mp(max(x - r, 0), min(x + r, l));
        }

        sort(coverage, coverage + g);

        int reach = 0, needed = 0, i = 0;
    
        while(reach < l) {
            int next = -1;
            while(i < g and coverage[i].first <= reach) next = max(next, coverage[i++].second);
            if (next < 0) break;
            reach = next;
            needed++;
        }

        cout << (reach == l ? g - needed : -1) << "\n";
    }
}