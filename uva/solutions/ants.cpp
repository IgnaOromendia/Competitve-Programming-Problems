#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <math.h>
#include <map>
#include <queue>
#include <sstream>

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
const double PI = 3.14159265359;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int t;cin >> t;

    while(t--) {
        int L, n; cin >> L >> n;
        int little_res = 0, big_res = 0;

        forn(i,0,n) {
            int l; cin >> l;
            little_res  = max(min(l, L - l), little_res);
            big_res     = max(max(l, L - l), big_res);
        }

        cout << little_res << " " << big_res << endl;
    }

}