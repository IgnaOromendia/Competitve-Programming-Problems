#include <iostream>
#include <vector>
#include <cstring>
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
constexpr int MAXN = 0;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

vi prod, cons;

int angry_cons_for(int price) {
    auto pos = lower_bound(cons.begin(), cons.end(), price);

    // Si no encontró no hay enojados
    if (pos == cons.begin()) return 0;

    // Devolvemos la cantidad de consumidores enojados
    return pos - cons.begin();
}

int angry_prod_for(int price) {
    auto pos = upper_bound(prod.begin(), prod.end(), price);

    // Si no encontró no hay enojados
    if (pos == prod.end()) return 0;

    // Devolvemos la cantidad de productores enojados
    return prod.size() - (pos - prod.begin());
}

void assign_mins(int& min_price, int& min_angry, int price) {
    int curr_angry = angry_prod_for(price) + angry_cons_for(price);

    if (min_angry > curr_angry or (curr_angry == min_angry and price < min_price)) {
        min_angry = curr_angry;
        min_price = price;
    }
}


// Con busqueda binaria en el precio se queda trabado en algunas "trampas"
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int t; cin >> t;

    while(t--) {
        int p, c, low = INF, high = 0, min_price = INF; 
        
        cin >> p >> c;

        prod.assign(p, 0);
        cons.assign(c, 0);

        forn(i,0,p) cin >> prod[i];
        forn(i,0,c) cin >> cons[i];

        sort(prod.begin(), prod.end());
        sort(cons.begin(), cons.end());

        int min_angry = p+c+1, angry_c, angry_p;

        // Evidentemnte tenemos que probar con todos los precios ya que la binaria no puede llegar a todo el espacio de soluciones
        forn(i, 0, p) assign_mins(min_price, min_angry, prod[i]);
        forn(i, 0, c) assign_mins(min_price, min_angry, cons[i]);

        // El c = 0 y p = 0 lo porceso antes
        if (c == 0 and p == 0) {
            cout << "0 0" << "\n";
            continue;
        }

        // En caso de que no haya productores forzamos a precios gratis
        min_price = (p == 0) ? 0 : min_price;

        // En caso de no tener consumidores forzamos el precio a favor del productor que pida más
        min_price = (c == 0) ? prod[p-1] : min_price;

        // Si no hya consumidores o productores no vamos a tener enojados
        min_angry = (c == 0 or p == 0) ? 0 : min_angry;
        
        // En caso de que sea el mínimo de los conumidores nos da lo mismo si es ese o 0
        if (min_price == cons[0] and min_price < prod[0]) min_price = 0;

        cout << min_price << " " << min_angry << "\n"; 
    }

}