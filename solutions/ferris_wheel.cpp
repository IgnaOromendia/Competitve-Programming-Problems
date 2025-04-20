#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > mat;
typedef pair<int,int> pi;

#define pb push_back
#define mp make_pair

#define forn(i,from,to) for (int i = from; i < to; i++)

const int INF  = 1e9;
const int MAXN = 0;
const int mod  = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int n, x; cin >> n >> x;

    vi weights(n);

    forn(i, 0, n) cin >> weights[i];

    sort(weights.begin(), weights.end());

    int gondolas = 0, l = 0, r = n-1;

    while(r >= l) {
        if (weights[r] + weights[l] <= x) {
            r--;
            l++;
            gondolas++;
        } else {
            r--;
            gondolas++;
        }
    }

    cout << gondolas << endl;
}