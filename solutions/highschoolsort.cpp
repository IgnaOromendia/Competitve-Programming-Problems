#include <iostream>
#include <vector>
#include <bitset>
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
constexpr int MAXN = 1e4;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int t, tcase = 1; cin >> t;
    
    while(t--) {
        int n; cin >> n;

        // El primero en orden siempre va a ser el 1
        int sorted = 0;

        forn(i,0,n) {
            int h; cin >> h;
            // Si ya se encuentra en orden con respecto al útlimo que estaba en orden entonces no hace falta moverlo
            if (h == sorted+1) sorted++;
        }
    
        cout << "Case " << tcase++ << ": " << n - sorted << "\n";
    }
    
}