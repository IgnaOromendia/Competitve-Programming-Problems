#include <iostream>
#include <vector>
#include <cstring>
#include <bitset>
#include <climits>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;
typedef vector<pi> vpi;
typedef vector<vector<int> > mat;
typedef pair<double,double> pd;
typedef vector<mat> tensor;

#define pb push_back
#define mp make_pair

#define forn(i,from,to) for (int i = from; i < to; i++)

constexpr int INF  = 1e9;
constexpr int MAXN = 20;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int n, x; cin >> n >> x;

    vpi memo(1 << n);
    vi weights(n);
    int people = (1 << n) - 1;

    forn(i, 0, n) cin >> weights[i];    

    // Memorizamos para cada subconjunto que todavía no subió la cantidad de viajes y la suma de pesos
    memo[0] = mp(1, 0);

    // Iteramos sobre todos los subconjuntos posibles
    forn(S, 1, 1 << n) {
        memo[S] = mp(INF, 0);
        
        // Por cada persona i me fijo que no haya subido y pruebo hacerlo subir
        // Mejora de implementación recorriendo solo los bits prendidos (reduce de 120ms a 60ms)
        int P = S;
        while(P) {
            // Obtenemos el bit menos significativos prendido
            int i = __builtin_ctz(P); 
            // Hacemos un XOR para eliminar ese bit
            P ^= (1 << i);  

            // Elimino a i de los que no viajaron todavía
            int S2 = S & ~(1 << i);

            auto [rides, w] = memo[S2];

            // En caso de que nos excedamos aumentamos la cantidad de viajes y reincicamos el peso
            rides += w + weights[i] <= x ? 0 : 1;
            int curr_weigth = weights[i] + ( w + weights[i] <= x ? w : 0);

            memo[S] = min(memo[S], mp(rides, curr_weigth));
        }
    }

    cout << memo[people].first << endl;

}