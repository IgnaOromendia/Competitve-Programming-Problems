#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pi;

#define pb push_back
#define mp make_pair

#define forn(i,a,b) for (int i = a; i <= b; i++)

const int MAXN = 5001;

int memo[MAXN][MAXN];

int word_distance(int n, int m, string &w1, string &w2) {
    if (m == 0 and n == 0) return 0;

    if (m == 0) return n;

    if (n == 0) return m;

    if (memo[n][m] != -1) return memo[n][m];

    if (w1[n-1] == w2[m-1]) return word_distance(n-1, m-1, w1, w2);

    int insert  = 1 + word_distance(n, m-1, w1, w2);
    int remove  = 1 + word_distance(n-1, m, w1, w2);
    int replace = 1 + word_distance(n-1, m-1, w1, w2);

    return memo[n][m] = min({insert, remove, replace});
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    memset(memo, -1, sizeof(memo));

    string w1, w2;
    cin >> w1 >> w2;

    cout << word_distance(w1.size(), w2.size(), w1, w2) << endl;

    return 0;
}