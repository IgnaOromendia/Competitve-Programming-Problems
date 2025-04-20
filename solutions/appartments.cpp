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

    int n, m, k; cin >> n >> m >> k;

    vi desired(n);
    vi real(m);

    forn(i, 0, n) cin >> desired[i];

    forn(i, 0, m) cin >> real[i];

    sort(desired.begin(), desired.end());
    sort(real.begin(), real.end());

    int i = 0, j = 0, count = 0;

    while(i < m and j < n) {
        if (abs(real[i] - desired[j]) <= k) {
            count++;
            i++;
            j++;
        } else if (real[i] < desired[j]) {
            i++;
        } else {
            j++;
        }
    }

    cout << count << endl;


}