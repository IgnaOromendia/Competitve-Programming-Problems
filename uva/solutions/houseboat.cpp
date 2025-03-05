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
const int MAXN = 0;
const int mod  = 1e9 + 7;
const float PI = 3.14159265359;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int n; cin >> n;

    forn(i,1,n+1) {
        float x,y; cin >> x >> y;

        float r = sqrt(x*x + y*y);
        int year = ceil(r*r * PI / 2 / 50);

        cout << "Property " << i << ": This property will begin eroding in year " << year << "." << endl; 
    }

    cout << "END OF OUTPUT." << endl;
}