#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

#define IMP "IMPOSSIBLE"

int n;
vector<vector<int> > adj;
vector<int> direct_way;
vector<long long> memo;

long long mod(long long x) {
    long long m = 1000000007LL;
    long long result = x % m;
    return result;
    //return result < 0 ? result + m : m;
}

int winning_routes(int v) {
    if (v == n) return 0;
    
    if (memo[v] == -1) {
        memo[v] = direct_way[v];
        for(int u: adj[v])
            memo[v] = mod(memo[v] + winning_routes(u));
    }

    return memo[v];
}

int main() {
    int m;
    cin >> n >> m;

    adj.assign(n+1, vector<int>());
    direct_way.assign(n+1, 0);
    memo.assign(n+1, -1);

    while(m--) {
        int u,v; cin >> u >> v;
        adj[u].push_back(v);
        direct_way[u] += (v == n);
    }

    cout << winning_routes(1) << endl;
}