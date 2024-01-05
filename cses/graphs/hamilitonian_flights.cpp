#include<iostream>
#include<vector>
#include<cstring>

using namespace std;

const unsigned int M = 1000000007;

int n;
vector<vector<int> > adj;

int mod(int a) {
    return (a % M + M) % M;
}

long long hamiltonian_paths() {
    long long memo[n][(1 << n)]; // memo[n][2^n]
    memset(memo, 0, sizeof(memo));

    memo[0][1] = 1;

    // BITMASKING
    for(int i = 2; i < (1 << n); i++) {
        // If the first vertex is absent continue
        if ((i & (1 << 0)) == 0) continue;

        // Considering the full subsets
        if ((i & (1 << (n-1))) && i != ((1 << n) - 1)) continue;

        for(int end = 0; end < n; end++) {
            // If the end is not in the subset
            if ((i & (1 << end)) == 0) continue;
            
            // Set without the end
            int prev = i - (1 << end);

            for(int u: adj[end]) {
                if((i & (1 << u))) {
                    memo[end][i] = mod(memo[u][prev] + memo[end][i]);
                }
            }
        }
    }

    return memo[n-1][(1 << n) - 1];
}

int main() {
    int m;
    cin >> n >> m;

    adj.assign(n, vector<int>());

    while(m--) {
        int v,u; cin >> v >> u;
        adj[u-1].push_back(v-1);
    }

    long long paths = hamiltonian_paths();

    cout << mod(paths) << endl;
}