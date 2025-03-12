#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <math.h>
#include <map>
#include <queue>

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
const double PI = 3.14159265359;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);


    int y;

    while (cin >> y && y != 0) {
        int i = 1;
        double sum = 0;
        double k = pow(2, 2 + (y - 1960) / 10);
        
        while (sum < k) 
            sum += log2(++i);
        
        
        cout << i - 1 << endl;  
    }

    
}