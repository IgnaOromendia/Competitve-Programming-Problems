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
    

    while(n) {
        int cc = 0, cr = 0;
        int row[n], col[n];

        memset(row, 0, sizeof(row));
        memset(col, 0, sizeof(col));

        forn(i,0,n)
            forn(j,0,n) {
                int e; cin >> e;
                row[i] += e;
                col[j] += e;
            }

        int i = -1,j = -1;

        forn(k,0,n) {
            if (row[k]&1) {cr++; i = k;}
            if (col[k]&1) {cc++; j = k;}
        }

        if (cc == 0 and cr == 0)
            cout << "OK" << endl;
        else if (cc == 1 and cr == 1)
            cout << "Change bit (" << i+1 << "," << j+1 << ")" << endl;
        else
            cout << "Corrupt" << endl;

        cin >> n;
    }
}