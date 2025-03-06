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

    int set = 1;

    while(n) {
        string names[n];

        forn(i,0,n) cin >> names[i];

        cout << "SET " << set << endl;

        for(int i = 0; i < n; i+=2) cout << names[i] << endl;

        for(int i = n - (n%2) - 1; i > 0; i-=2) cout << names[i] << endl;

        cin >> n;
        set++;
    }


}