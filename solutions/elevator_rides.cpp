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

#define forn(i,a,b) for (int i = a; i < b; i++)

const int INF  = 1e9;
const int MAXN = 0;
const int mod  = 1000000007;


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int n, max_weight; cin >> n >> max_weight;

    // <min amount of rides, min weight of the last ride>
    pi memo[1 << n];
    int weights[n];

    forn(i, 0, n) cin >> weights[i];
   
    memo[0] = {1, 0};

    forn(s, 1, 1 << n) {
        memo[s] = {n+1, 0};

        forn(p, 0, n) {
            // Item si included in the set
            if (s & (1 << p)) {
                // Subset without p
                pi option = memo[s^(1 << p)];

                if (option.second + weights[p] <= max_weight){ 
                    option.second += weights[p];
                } else {
                    option.first++;
                    option.second = weights[p];
                }

                memo[s] = min(memo[s], option);
            }
            
        }
    }

    cout << memo[(1 << n)-1].first << endl;

    return 0;

}