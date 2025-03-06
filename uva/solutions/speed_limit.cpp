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

    int n, dist, ti; cin >>n;

    while(n != -1) {
        dist = 0; ti = 0;

        forn(i,0,n) {
            int tf, v; cin >> v >> tf;
            dist += (tf - ti) * v;
            ti = tf;
        }

        cout << dist << " miles"<< endl;

        cin >> n;
    }
}