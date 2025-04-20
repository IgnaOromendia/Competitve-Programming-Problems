#include<iostream>
#include<vector>
#include<math.h>

const unsigned int INF = 1e7;

using namespace std;

int length;
vector<int> memo;

int count_steps(int n) {
    if (n == 0) return 0;
    if (n < 0) return INF;

    if (memo[n] == -1) {
        memo[n] = INF;
        int i = 1;
        while(n > 0 and log10(i) < length) {
            // cout << "---" << endl;
            // cout << "i: " << i << " | " << (i / 10) << " < " << length << endl;
            int digit = (n / i) % 10;
            // cout << "n: " << n << " - " << digit <<  endl;
            memo[n] = min(memo[n], 1 + count_steps(n - digit));
            i *= 10;
        }
    }

    return memo[n];
}

void number_length(int n) {
    while(n > 0) {
        n = n / 10;
        length++;
    }
}

int main() {
    int n; cin >> n;
    memo.assign(n+1, -1);

    number_length(n);
    cout << count_steps(n) << endl;
}