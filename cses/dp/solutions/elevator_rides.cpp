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

int n, max_weight;

vi weights;
mat memo;

int non_empty_rides(vi& rides) {
    int sum = 0;
    forn(i,0,rides.size()){
        // cout << rides[i] << " ";
        sum += rides[i] > 0;
    }
    // cout << endl;
    return sum;
}

int min_rides(int i, int rides, vi& elevators) {
    if (i == n) return non_empty_rides(elevators);

    if (memo[i][rides] != -1) return memo[i][rides];
    
    memo[i][rides] = INF;
    forn(j, 0, n) {
        if (elevators[j] + weights[i] <= max_weight) {
            elevators[j] += weights[i];
            memo[i][rides] = min(memo[i][rides], min_rides(i+1, non_empty_rides(elevators), elevators));
            elevators[j] -= weights[i];
        }
    }   

    return memo[i][rides];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    cin >> n >> max_weight;

    weights.assign(n, 0);
    memo.assign(n, vector<int>(n,-1));

    forn(i, 0, n) cin >> weights[i];

    vi elevators(n,0);

    cout << min_rides(0, 0, elevators) << endl;

    

}