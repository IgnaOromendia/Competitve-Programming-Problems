#include <vector>
#include <iostream>

using namespace std;

const double INF = 10e8;

vector<int> sequence;
vector<vector<vector<int> > > memo;

int minUnpainted(int n, int i, int wUlt = 0, int bUlt = 1) {
    if (i == n) return 0;

    if (memo[i][wUlt][bUlt] != -1) return memo[i][wUlt][bUlt];
    
    int whitePaint = INF;
    int blackPaint = INF;

    if (sequence[i] > sequence[bUlt]) blackPaint = minUnpainted(n, i+1, wUlt, i);
    if (sequence[i] < sequence[wUlt]) whitePaint = minUnpainted(n, i+1, i, bUlt);

    int bestPaint = min(1 + minUnpainted(n, i+1, wUlt, bUlt), min(blackPaint, whitePaint));

    return memo[i][wUlt][bUlt] = bestPaint;

}

int main() {
    int n; cin >> n;

    while(n != -1) {
        n += 2;
        sequence.assign(n, 0);
        memo.assign(n,vector<vector<int> >(n, vector<int>(n, -1)));

        sequence[0] = INF;
        sequence[1] = -INF;

        for (int i = 2; i < n; i++) cin >> sequence[i];

        cout << minUnpainted(n, 2) << endl;

        cin >> n;
    }


}