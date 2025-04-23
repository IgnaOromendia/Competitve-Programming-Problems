#include<iostream>
#include<vector>

#define ll long long

using namespace std;

int main() {
    int t; cin >> t;
    
    while (t--) {
        ll x,y,a,b;
    
        cin >> x >> y >> a >> b;

        ll cost = 0;

        if (2*a < b) {
            cost = a * (x + y);
        } else {
            cost = (max(x,y) - min(x,y)) * a + min(x,y) * b;
        }

        cout << cost << endl;
    }
    
}