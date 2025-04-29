#include <iostream>
#include <vector>
#include <cstring>
#include <bitset>
#include <set>
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
constexpr int MAXN = 128, MAXM = 20;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

int n,m, objects[MAXN][MAXM];

// Se fija que todos sean identificables y además devuevle la cantidad de bits necesarios
bool all_identifiable(int S) {
    set<int> unique_ids;
    
    forn(i,0,n) { 
        int object_id = 0;  // id para el objeto i usando solo columnas seleccionadas
        
        forn(j,0,m) 
            if (S & (1 << j) and objects[i][j])
                object_id |= (1 << j);

        unique_ids.insert(object_id);
    }
    
    return unique_ids.size() == n;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);


    while(cin >> m >> n,m+n) {

        int max_sets = 1 << m;

        forn(i,0,n) {
            string line; cin >> line;
            forn(j,0,m)
                objects[i][j] = line[j] - '0';
        }

        if (n == 1) cout << 0 << "\n";
        else {
            int min_q = INF;

            forn(S, 1, max_sets) 
                if (all_identifiable(S)) 
                    min_q = min(min_q, __builtin_popcount(S));  // Cantidad de bits prednidios en S
            


            cout << min_q << "\n";
        }

    }

}