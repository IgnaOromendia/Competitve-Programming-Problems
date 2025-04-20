#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int numbers[15], it, x, count; 
    
    cin >> x;

    while(x != -1) {
        it = 0;
        count = 0;

        while(x != 0) {
            numbers[it] = x; 
            cin >> x;
            it++;
        }

        forn(i,0, it) {
            for(int j = i+1; j < it; j++) 
                if (numbers[i]*2 == numbers[j] or numbers[j]*2 == numbers[i])
                    count++;
        }

        cout << count << endl;

        cin >> x;
    }
}