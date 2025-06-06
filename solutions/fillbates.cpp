#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > mat;
typedef vector<vector<int> > graph;
typedef pair<int,int> pi;
typedef pair<double,double> pd;

#define pb push_back
#define mp make_pair

#define forn(i,from,to) for (int i = from; i < to; i++)

constexpr int INF  = 1e9;
constexpr int MAXN = 53;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    vi candidates[MAXN];

    string line; cin >> line;

    forn(i,0,line.size()) {
        int idx = 'A' <= line[i] and line[i] <= 'Z' ? line[i] - 'A' + 26 : line[i] - 'a';
        candidates[idx].pb(i);
    }
        
        
    int k; cin >> k;

    while(k--) {
        string word; cin >> word;

        int prev_pos = -1, first = -1, last = 0;
        bool matched = true;

        for(char c: word) {
            
            int c_idx = 'A' <= c and c <= 'Z' ? c - 'A' + 26 : c - 'a';

            auto it = lower_bound(candidates[c_idx].begin(), candidates[c_idx].end(), prev_pos + 1);

            if (it == candidates[c_idx].end()) matched = false;
            if (!matched) break;

            int i = *it;

            if (first == -1) first = i;
            last = i;
            prev_pos = i;
        }

        if (matched) cout << "Matched " << first << " " << last << "\n";
        else cout << "Not matched\n";
    }




}