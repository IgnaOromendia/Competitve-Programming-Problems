#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <math.h>
#include <map>
#include <queue>
#include <sstream>
#include <iomanip>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > mat;
typedef pair<int,int> pi;
typedef pair<double,double> pd;

#define pb push_back
#define mp make_pair

#define forn(i,from,to) for (int i = from; i < to; i++)

const int INF  = 1e9;
const int MAXN = 1000001;
const int mod  = 1e9 + 7;
const double PI = 3.14159265359;

int is_prime[MAXN], prime[MAXN], max_i = 0;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int x; cin >> x;

    forn(i, 0, MAXN) is_prime[i] = 1; 
    is_prime[0] = is_prime[1] = 0;      

    for (int i = 2; i * i < MAXN; i++) 
        if (is_prime[i]) 
            for (int j = i * i; j < MAXN; j += i) 
                is_prime[j] = 0; 
            
    forn(i,2,MAXN) if(is_prime[i]) prime[++max_i] = i;

    bool wrong = true;

    while(x) {
        forn(i,2,max_i+1) {
            if (prime[i]*2 > x) break;

            if (is_prime[x - prime[i]]) {
                wrong = false;
                cout << x << " = " << prime[i] << " + " << x - prime[i] << endl;
                break;
            }
        }

        if (wrong) cout << "Goldbach's conjecture is wrong." << endl;

        

        cin >> x;
    }
}