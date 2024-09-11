#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e9;

int n, m, r, c;

vector<vector<long long> > memo;
vector<vector<bool> > visited;

long long min_seconds(int i, int j) {
    if (i == r and j == c) return 0;

    // cout << i << " " << j << <<  endl;

    if (memo[i][j] != -1) return memo[i][j];

    visited[i][j] = true;

    long long best = INF;


    if (i >= 1 and not visited[i-1][j])      best = min(best, 1 + min_seconds(i-1,j));
    if (i < n - 1 and not visited[i+1][j])  best = min(best, 1 + min_seconds(i+1,j));
    if (j >= 1 and not visited[i][j-1])      best = min(best, 1 + min_seconds(i,j-1));
    if (j < m - 1 and not visited[i][j+1])  best = min(best, 1 + min_seconds(i,j+1));         

    visited[i][j] = false;

    memo[i][j] = best;
    
    return best;
}

int main() {
    int t; cin >> t;
    while(t--) {
        cin >> n >> m >> r >> c;

        memo.assign(n, vector<long long>(m,-1));
        visited.assign(n, vector<bool>(m,false));

        long long sum = 0;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++) 
                sum += min_seconds(i,j);
                

        cout << sum << endl;
        // cout << min_seconds(0,0) << endl;
        // cout << min_seconds(1,0) << endl;
        // cout << min_seconds(0,1) << endl;
        // cout << min_seconds(1,1) << endl;
    }
}