#include <iostream>
#include <vector>
#include <cstring>
#include <bitset>
#include <climits>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vector<ll> > mat;
typedef pair<int,ll> pil;
typedef pair<double,double> pd;
typedef vector<mat> tensor;

#define pb push_back
#define mp make_pair

#define forn(i,from,to) for (int i = from; i < to; i++)

constexpr int INF  = 1e9;
constexpr int MAXN = 100, MAXM = 100;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

int n,m;
ll k;
int A[MAXN][MAXM];
tensor sums;


pil kadane(int f1, int f2) {
    int res_costo = INT_MAX, curr_costo = 0;
    int alto = f2 - f1 + 1, ancho, c1 = 0, res_area = 0;

    // Recorremos todas las columnas para el rango [f1,f2]
    forn(c2, 0, m){
        // Sumamos la el coste de la nueva columna
        curr_costo += sums[f1][f2][c2];

        // Si nos pasamos empezamos desde esa columna
        while (c1 <= c2 and curr_costo > k) {
            curr_costo -= sums[f1][f2][c1];
            c1++;
        }

        ancho = c2 - c1 + 1;
        int curr_area = alto * ancho;


        // Nos fijamos si cuesta "menos" y si el area es mayor
        if (curr_area > res_area) {
            res_area = curr_area;
            res_costo = curr_costo;
        } else if (curr_area == res_area and curr_costo < res_costo) {
            res_costo = curr_costo;
        } 

    }

    return mp(res_area, res_costo);
}

// O(n^2 * m) aprox 10^5 por seg
void all_row_sum() {
    forn(c,0,m)
        forn(f1,0,n) 
            forn(f2,f1,n) {
                if (f1 == f2) sums[f1][f2][c] = A[f1][c];
                else if (f1 == 0) sums[f1][f2][c] = sums[f1][f2-1][c] + A[f2][c];
                else sums[f1][f2][c] = sums[f1-1][f2][c] - sums[f1-1][f1-1][c];
            }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int tcase = 1, t; cin >> t;

    while(t--) {
        cin >> n >> m >> k;

        forn(i,0,n) 
            forn(j,0,m) 
                cin >> A[i][j];

        sums.assign(n, mat(n, vl(m,0)));

        all_row_sum();

        // Area y costo
        pil result = mp(0, INF);

        forn(f1,0,n)
            forn(f2,f1,n) {
                auto [area, costo] = kadane(f1, f2);

                if (area == 0) continue;

                if ((area > result.first or (area == result.first and costo < result.second)) and costo <= k) 
                    result = mp(area,costo);
            }
            
        if (result.second == INF) result.second = 0;
        cout << "Case #" << tcase++ << ": " << result.first << " " << result.second << "\n";

    } 
}