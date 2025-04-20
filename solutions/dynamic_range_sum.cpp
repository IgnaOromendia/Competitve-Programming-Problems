#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > mat;
typedef pair<int,int> pi;

#define pb push_back
#define mp make_pair

#define forn(i,from,to) for (int i = from; i < to; i++)

const int INF  = 1e9;
const int MAXN = 50; //2 * 1e5 +! 1;
const int mod  = 1e9 + 7;

// k&-k represent the largest power of 2 that divides k

struct FenwickTree {
    vector<ll> bit;  // binary indexed tree
    int n;

    FenwickTree(int n) {
        this->n = n;
        bit.assign(n, 0);
    }

    ll sum(int k) {
        ll s = 0;
        while (k >= 1) {
            s += bit[k];
            k -= k&-k;
        }
        return s;
    }

    ll sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int k, ll x) {
        while (k <= n) {
            bit[k] += x;
            k += (k&-k);
        }
    }

    void print() {
        forn(i, 0, n) cout << bit[i] << " ";
        cout << endl;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int n, q; cin >> n >> q;

    FenwickTree tree(n+1);

    ll values[n+1];

    forn(i,1,n+1) {
        cin >> values[i];
        tree.add(i, values[i]);
    }

    while(q--) {
        int t, x, y; cin >> t >> x >> y;

        if (t == 1) {        
            tree.add(x, y - values[x]);
            values[x] = y;
        }

        if (t == 2) {
            cout << tree.sum(x,y) << endl;
        }

    }

    return 0;
}