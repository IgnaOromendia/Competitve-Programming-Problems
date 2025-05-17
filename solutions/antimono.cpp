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
constexpr int MAXN = 30000;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

int freds[MAXN];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int n, t; cin >> t;
    
    while(t--) {
        cin >> n;
        forn(i,0,n) cin >> freds[i];

        // next es 1 cuando necesitamos que i < i-1 y 0 cuando i > i-1
        int max_seq = 1, next = 1;

        forn(i,1,n) {
            // Caso 1: Necesitamos que sea menor y lo es
            // Caso 2: Necesiamtos que sea mayor y lo es
            if ((next and freds[i] <= freds[i-1]) or (!next and freds[i] >= freds[i-1])) {
                next = !next;
                max_seq++;
            } 
        }

        cout << max_seq << "\n";
    }
}