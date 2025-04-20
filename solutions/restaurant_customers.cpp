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

    int n; cin >> n;

    vector<pi> intervals(n);

    forn(i, 0, n) {
        int s,f; cin >> s >> f;
        intervals[i] = mp(s,f);
    }

    sort(intervals.begin(), intervals.end(), [](const pi& l, const pi& r){
        return l.first < r.first;
    });

    int j = 0;
    int max_interval = 0, same_interval = 1;

    forn(i, 0, n-1) {        
        if (intervals[i+1].first < intervals[j].second and intervals[i].second > intervals[i+1].first) {
            same_interval++;
        } else {
            max_interval = max(max_interval, same_interval);
            same_interval = 1;
            j = i;
        }
    }

    max_interval = max(max_interval, same_interval);

    cout << max_interval << endl;

}