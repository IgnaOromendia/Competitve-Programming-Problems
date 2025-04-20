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

    float sum = 0;

    forn(i, 0 ,12) {
        float x; cin >> x;
        sum += x;
    }

    float mean = sum / 12;

    cout << "$" << mean << endl;
}