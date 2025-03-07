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

    int t, n1, n2; cin >> t;

    forn(x,0,t) {
        string s; 
        int a[100], b[100];

        memset(a,0,sizeof(a));
        memset(b,0,sizeof(b));
        
        cin >> s;
        n1 = s.length();

        for(int i = 0; i < n1; i++)
            a[i] = s[i] - '0';

        cin >> s;
        n2 = s.length();
        
        for(int i = 0; i < n2; i++)
            b[i] = s[i] - '0';

        int n = max(n1,n2);
        bool flag = false;

        // Addition
        for(int i = 0; i < n ; i++) {
            a[i] += b[i];
            if (a[i] > 9) {
                a[i] -= 10;
                a[i+1]++;
                flag = i == n-1;
            }
        }

        if (flag) n++;

        bool notZero = false;
        
        forn(i,0,n) {
            if (notZero or a[i] != 0) {
                notZero = true;
                cout << a[i];
            }
        }
        cout << endl;
        
    }
}