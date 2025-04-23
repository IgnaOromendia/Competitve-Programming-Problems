#include <iostream>
#include <vector>

// https://codeforces.com/contest/782/problem/B

using namespace std;

int main() {
    int n; cin >> n;

    vector<int> position(n);
    vector<int> speed(n);

    for (int i = 0; i < n; i++) cin >> position[i];
        
    for (int i = 0; i < n; i++) cin >> speed[i];

    double lower = 0, upper = 10e8, eps = 10e-8;

    while (upper - lower > eps){
        double mid = (upper + lower) / 2;

        double left = 0, right = 10e8;
        for (int i = 0; i < n; i++) {
            left  = max(left, position[i] - mid * speed[i]);
            right = min(right, position[i] + mid * speed[i]);
        }

        if (left < right) upper = mid;
        else lower = mid;
    }

    printf("%.7f\n",lower);

    return 0;
}