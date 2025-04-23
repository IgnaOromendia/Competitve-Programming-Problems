#include <iostream>

using namespace std;

int main() {
    int t; cin >> t;
    while(t--) {
        int n, m, r, c; cin >> n >> m >> r >> c;

        int dmax = abs(1 - r) + abs(1 - c);
        dmax = max(dmax, abs(n - r) + abs(m - c));
        dmax = max(dmax, abs(1 - r) + abs(m - c));
        dmax = max(dmax, abs(n - r) + abs(1 - c));

        cout << dmax << endl;
    }
}