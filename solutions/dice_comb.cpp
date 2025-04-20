#include<iostream>
#include<vector>

using namespace std;

const unsigned int M = 1000000007;

int n;
vector<long long> memo;

int mod(int a) {
    return (a % M + M) % M;
}

long long combinations(int d) {
    if (d == 0) return 1;
    if (d < 0) return 0;

    if (memo[d] == -1) {
        memo[d] = 0;
        for(int i = 1; i <= 6; i++) {
            memo[d] = mod(memo[d] + combinations(d - i));
        }
    }

    return memo[d];
}

int main() {
    cin >> n;
    memo.assign(n+1, -1);
    cout << combinations(n) << endl;
}