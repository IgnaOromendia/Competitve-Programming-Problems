#include<iostream>
#include<vector>

using namespace std;

const int INF = 10e8;

int n;
vector<int> coin;
vector<int > memo;

int min_coins(int s) {
    if (s < 0) return INF;
    if (s == 0) return 0;

    if (memo[s] == -1) {
        memo[s] = INF;
        for(int i = 0; i < n; i++) {
            memo[s] = min(memo[s], 1 + min_coins(s - coin[i]));
        }

    }

    return memo[s];
}

int main() {
    int x;
    cin >> n >> x;

    memo.assign(x+1,-1);
    coin.assign(n, 0);
    
    for(int i = 0; i < n; i++) cin >> coin[i];

    int amount = min_coins(x);

    if (amount == INF) 
        cout << -1 << endl;
    else
        cout << amount << endl;
}