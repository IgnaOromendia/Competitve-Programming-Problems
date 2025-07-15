#include <iostream>
#include <vector>
#include <cstring>
#include <bitset>
#include <set>
#include <algorithm>
#include <unordered_map>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > mat;
typedef pair<int,int> pi;
typedef pair<double,double> pd;
typedef unordered_map<pi, int> umap;

#define pb push_back
#define mp make_pair

#define forn(i,from,to) for (int i = from; i < to; i++)

// Bitset
#define contains(set, x) (set & (1 << x))
#define add(set, x) (set |= (1 << x))
#define size(set) __builtin_popcount(set)
#define remove(set, x) (set &= ~(1 << x);)

constexpr int INF  = 1e9;
constexpr int MAXN = 128, MAXM = 11;
constexpr int MCOMB = 1 << MAXM;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

int n, m, features[MAXN];
int memo[MCOMB][MCOMB], objects[MCOMB][MCOMB];

int min_questions(int used, int useful) {
    if (objects[used][useful] <= 1) return 0; // No hace falta que preguntemos xq ya está separado o no hay

    if (memo[used][useful] != -1) return memo[used][useful];

    int res = MAXM;

    forn(f, 0, m) {
        if (contains(used, f)) continue;
        
        int useful_f = useful, using_f = used;
        add(useful_f, f);
        add(using_f, f);

        if (objects[using_f][useful_f] == 0 or objects[using_f][useful] == 0) continue;

        res = min(res, 1 + max(min_questions(using_f, useful_f), min_questions(using_f, useful)));

    }    

    return memo[used][useful] = res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);


    while(cin >> m >> n and m+n) {

        int max_sets = 1 << m;

        memset(objects, 0, sizeof(objects));
        memset(features, 0, sizeof(features));
        memset(memo, -1, sizeof(memo));

        forn(i, 0, n) {
            string line; cin >> line;

            forn(j, 0, m)
                if (line[j] == '1') 
                    add(features[i], j);
        }

        if (n <= 1) {
            cout << 0 << "\n";
            continue;
        }

        // Para combinación de features preguntados y realmente usados calculamos cuantos objetos nos separan
        forn(o, 0 ,n) {
            // Obtenemos los features usados por el objeto o
            int curr_features = 0;
            forn(f, 0, m) if (contains(features[o], f)) add(curr_features, f);
            
            // Para cada combinación de features agregamos el objeto en la posición de los features que responde que si
            forn(s, 0, MCOMB) {
                int useful_features = s & curr_features;
                objects[s][useful_features]++;
            }
        }

        int min_q = min_questions(0, 0);
        
        cout << min_q << "\n";

    }

}