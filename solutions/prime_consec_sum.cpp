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
const int MAXN = 10001;
const int mod  = 1e9 + 7;

bool is_prime(int number) {
    for(int i = 2; i <= sqrt(number); i++)
        if (number % i == 0) return false;

    return true;
}

int next_prime(int prime) {
    forn(i, prime+1, INF) 
        if (is_prime(i)) return i;
    return -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int prime[MAXN], count, ans;

    int number; cin >> number;

    prime[0] = 2;
    forn(i, 1, MAXN) prime[i] = next_prime(prime[i-1]);
        
    while (number != 0) {
        ans = 0;

        for (int i = 0; number >= prime[i]; i++) {
            count = 0;
            for (int j = i; j < MAXN and count < number; j++) 
                count += prime[j];
                
            if (count == number) ans++;
        }

        cout << ans << endl;

        cin >> number;
    }

}