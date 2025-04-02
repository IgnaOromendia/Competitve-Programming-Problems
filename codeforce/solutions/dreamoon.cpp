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

constexpr int INF  = 1e9;
constexpr int MAXN = 0;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

int final_position(string& sequence) {
    int position = 0;
    forn(i,0,sequence.length()) 
        position += sequence[i] == '+' ? 1 : -1;
    return position;
}

pi add_pairs(pi left, pi right) {
    return mp(left.first + right.first, left.second + right.second);
}

pi possible_ways(int i, string& seq, int obj) {
    if (i == seq.length()) return mp(1, obj == 0);

    if (seq[i] == '?') return add_pairs(possible_ways(i+1,seq,obj-1), possible_ways(i+1, seq, obj+1));

    return seq[i] == '+' ? possible_ways(i+1, seq, obj-1) : possible_ways(i+1, seq, obj+1);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    string orginal, recived;

    getline(cin, orginal);
    getline(cin, recived);

    pi result = possible_ways(0,recived, final_position(orginal));

    double p = double(result.second) / result.first;

    cout << fixed << setprecision(12) << p << "\n";

}