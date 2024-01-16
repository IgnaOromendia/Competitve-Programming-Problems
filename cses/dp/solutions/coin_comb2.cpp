#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

const unsigned int M = 1000000007;

int n, x;
vector<int> coins;
vector<int> memo;

int count_ways() {
    memo[0] = 1;

    for(int i = 1; i <= n; i++) {
        for(int cost = 0; cost <= x; cost++) {
            if(cost - coins[i - 1] >= 0) {
                memo[cost] += memo[cost - coins[i - 1]];
                memo[cost] %= M;
            } 
        }
    }

    return memo[x];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> x;

    coins.assign(n,0);
    memo.assign(x+1, 0);

    for(int i = 0; i < n; i++) cin >> coins[i];

    cout << count_ways() << endl;
}