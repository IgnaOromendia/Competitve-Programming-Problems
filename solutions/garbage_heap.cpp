#include <iostream>
#include <vector>
#include <cstring>
#include <bitset>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vector<ll> > mat;
typedef pair<int,int> pi;
typedef pair<double,double> pd;
typedef vector<mat> tensor;
typedef vector<tensor> tensor4D;
typedef vector<tensor4D> tensor5D;

#define pb push_back
#define mp make_pair

#define forn(i,from,to) for (int i = from; i < to; i++)

constexpr int INF  = 1e9;
constexpr int MAXN = 20;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

int A,B,C;
ll garbage[MAXN][MAXN][MAXN];
tensor5D sum;

ll kadane(int f1, int f2, int c1, int c2) {
    ll res = 0, curr = -1;
    for(int z = 0; z < C; z++) {
        curr = max(sum[f1][f2][c1][c2][z], curr + sum[f1][f2][c1][c2][z]);
        res = max(curr, res);
    }
    return res;
}

void compute_sums() {
    
    forn(z, 0, C) {
        // Suma sobre columnas en rangos de filas
        forn(c, 0 ,B) {
            forn(f1, 0, A) 
                forn(f2, f1, A) {
                    if (f1 == f2) sum[f1][f2][c][c][z] = garbage[f2][c][z];
                    else if (f1 == 0) sum[f1][f2][c][c][z] = sum[f1][f2-1][c][c][z] + garbage[f2][c][z];
                    else sum[f1][f2][c][c][z] = sum[f1-1][f2][c][c][z] - sum[f1-1][f1-1][c][c][z];
                }
        }

        // Suma sobre filas en rangos de columnas
        forn(f, 0 ,A) {
            forn(c1, 0, B) 
                forn(c2, c1, B) {
                    if (c1 == c2) sum[f][f][c1][c2][z] = garbage[f][c2][z];
                    else if (c1 == 0) sum[f][f][c1][c2][z] = sum[f][f][c1][c2-1][z] + garbage[f][c2][z];
                    else sum[f][f][c1][c2][z] = sum[f][f][c1-1][c2][z] - sum[f][f][c1-1][c2-1][z];
                }
        }


    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int t; cin >> t;

    while(t--) {
        cin >> A >> B >> C;

        sum.assign(A, tensor4D(A, tensor(B, mat(B, vl(C)))));

        ll max_heap = INT_MIN;

        forn(z, 0, C)
            forn(x, 0 , A)
                forn(y, 0, B) {
                    cin >> garbage[x][y][z];   
                    max_heap = max(max_heap, garbage[x][y][z]);
                }
                                  

        compute_sums();      

        forn(f1, 0, A) forn(f2, f1, A)
            forn(c1, 0, B) forn(c2, c1, B) {
                ll heap = kadane(f1, f2, c1, c2);
                if (heap == 0) continue;
                max_heap = max(max_heap, heap);
            }

        cout << max_heap << "\n" << "\n";        

    }
}