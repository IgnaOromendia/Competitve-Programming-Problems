#include <iostream>
#include <vector>
#include <cstring>
#include <climits>

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
constexpr int MAXN = 21;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

int A,B,C;
ll garbage[MAXN][MAXN][MAXN];
tensor5D sum;

ll kadane(int f1, int f2, int c1, int c2) {
    ll res = LLONG_MIN, curr = 0;
    forn(z, 0, C) {
        curr = max(sum[f1][f2][c1][c2][z], curr + sum[f1][f2][c1][c2][z]);
        res = max(curr, res);
    }
    return res;
}

void compute_sums() {
    forn(z, 0, C)
        forn(f1, 0, A) forn(f2, f1, A)
            forn(c1, 0, B) forn(c2, c1, B) {
                ll total = 0;
                forn(i, f1, f2+1) 
                    forn(j, c1, c2+1)
                        total += garbage[i][j][z];

                sum[f1][f2][c1][c2][z] = total;
            }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int t; cin >> t;

    while(t--) {
        cin >> A >> B >> C;

        sum.assign(A, tensor4D(A, tensor(B, mat(B, vl(C)))));

        ll max_heap = LLONG_MIN;

        forn(z, 0, C)
            forn(x, 0 , A)
                forn(y, 0, B) {
                    cin >> garbage[x][y][z];   
                    max_heap = max(max_heap, garbage[x][y][z]);
                }
                                  
        compute_sums();      

        forn(f1, 0, A) forn(f2, f1, A)
            forn(c1, 0, B) forn(c2, c1, B) {
                ll curr_heap = kadane(f1, f2, c1, c2);
                if (curr_heap == 0) continue;
                max_heap = max(max_heap, curr_heap);
            }

        cout << max_heap << "\n";

        if (t > 0) cout << "\n";

    }
}