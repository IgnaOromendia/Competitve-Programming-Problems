#include<iostream>
#include<vector>

using namespace std;

const unsigned int INF = 10e8;
const unsigned int M = 1000000007;

int n;
vector<int> coins;
vector<long long> memo;

long long count_ways(int s) {
    if (s == 0) return 1;
    if (s < 0) return 0;

    if (memo[s] == -1) {
        memo[s] = 0;
        for(int i = 0; i < n; i++) 
            memo[s] = (memo[s] + count_ways(s - coins[i])) % M;
    }

    return memo[s];
}

int main() {
    int x;
    cin >> n >> x;

    coins.assign(n,0);
    memo.assign(x+1,-1);

    for(int i = 0; i < n; i++) cin >> coins[i];

    cout << count_ways(x) << endl;
}