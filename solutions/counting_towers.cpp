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
constexpr int MAXN = 1e7 + 1;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

ll memo_sin_huecos[MAXN];
ll memo_con_huecos[MAXN];

ll con_huecos(int i);

// Voy a pensar que podemos rellenar la torre de altura i dejando huecos o no

// Rellenar una torre de alutra i sin dejar huecos
ll sin_huecos(int i) {
    // Ponemos bloque 1x2
    if (i == 1) return 1; 
    if (i <= 0) return 0;

    if (memo_sin_huecos[i] != -1) return memo_sin_huecos[i];

    // Ponemos un 1x2 o un 2x2
    ll result = (sin_huecos(i-1) + sin_huecos(i-2)) % mod;

    // Ponemos un 2x1 (vertical)
    result = (result + 2 * con_huecos(i-1)) % mod;

    return memo_sin_huecos[i] = result;
}

// Rellenar una torre de altura i dejando un hueco
ll con_huecos(int i) {
    if(i <= 0) return 0;

    if (memo_con_huecos[i] != -1) return memo_con_huecos[i];

    // Ponemos un 1x2 y...
    return memo_con_huecos[i] = (sin_huecos(i-1) + con_huecos(i-1)) % mod;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int n,t; cin >> t;

    fill(memo_sin_huecos, memo_sin_huecos + MAXN, -1);
    fill(memo_con_huecos, memo_con_huecos + MAXN, -1);

    while (t--) {
        cin >> n;
        cout << sin_huecos(n) << "\n";
    }
    
}