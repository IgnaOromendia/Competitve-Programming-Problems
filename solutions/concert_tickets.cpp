#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <set>

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

    int n, m; cin >> n >> m;

    multiset<int> tickets;

    forn(i, 0, n) {
        int h; cin >> h;
        tickets.insert(h);
    }

    forn(i, 0, m) {
        int max_price; cin >> max_price;

        auto it = tickets.upper_bound(max_price);

        if (it == tickets.begin()) {
            cout << -1 << endl;
        } else {
            it--;
            cout << *it << endl;
            tickets.erase(it);
        }

    }

}