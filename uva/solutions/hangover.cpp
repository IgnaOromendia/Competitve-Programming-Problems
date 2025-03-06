#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <math.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > mat;
typedef pair<int,int> pi;

#define pb push_back
#define mp make_pair

#define forn(i,from,to) for (int i = from; i < to; i++)

const int INF  = 1e9;
const int MAXN = 500;
const int mod  = 1e9 + 7;
const float PI = 3.14159265359;
const double delta = 1e-8;

int zero(double x) {
    if (x < -delta) return -1;
    return x > delta;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    double len[MAXN];
    len[0] = 0.0;
    int i = 1;

    for(; zero(len[i-1] - 5.2) < 0; i++) 
        len[i] = len[i-1] + double(1.0/(i+1));
    
    
    double x; cin >> x;
    
    while(zero(x)) {
        int l = 0,r = i;

        while(l+1 < r) {
            int mid = (l+r) / 2;
            if(zero(len[mid] - x) < 0)
                l = mid;
            else
                r = mid;
        }

        cout << r << " card(s)" << endl;
            
        cin >> x;
    }


}