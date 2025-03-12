#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <math.h>
#include <map>
#include <queue>
#include <sstream>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > mat;
typedef pair<int,int> pi;

#define pb push_back
#define mp make_pair

#define forn(i,from,to) for (int i = from; i < to; i++)

const int INF  = 1e9;
const int MAXN = 1001;
const int mod  = 1e9 + 7;
const double PI = 3.14159265359;

string intToString(int num) {
    stringstream ss;
    ss << num;
    return ss.str();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int n; cin >> n;
    int fi = 0, sfi = 1, si = n-1, ssi = n-2, sum_time = 0;

    vi time(n);

    forn(i,0,n) cin >> time[i];

    sort(time.begin(), time.end());    

    vector<string> steps;
    int total_time = 0;

    if (n == 1) {
        total_time = time[0];
        steps.push_back(intToString(time[0]));
    } else if (n == 2) {
        total_time = time[1];
        steps.push_back(intToString(time[0]) + " " + intToString(time[1]));
    } else {
        int l = 0, r = n - 1;

        while (r - l >= 3) {
            int opt1 = 2 * time[l] + time[r] + time[r - 1];
            int opt2 = 2 * time[l + 1] + time[l] + time[r];

            if (opt1 < opt2) {
                total_time += opt1;
                steps.push_back(intToString(time[l]) + " " + intToString(time[r]));
                steps.push_back(intToString(time[l]));
                steps.push_back(intToString(time[l]) + " " + intToString(time[r - 1]));
                steps.push_back(intToString(time[l]));
            } else {
                total_time += opt2;
                steps.push_back(intToString(time[l]) + " " + intToString(time[l + 1]));
                steps.push_back(intToString(time[l]));
                steps.push_back(intToString(time[r - 1]) + " " + intToString(time[r]));
                steps.push_back(intToString(time[l + 1]));
            }
            r -= 2;
        }

        if (r == 2) {
            total_time += time[0] + time[1] + time[2];
            steps.push_back(intToString(time[0]) + " " + intToString(time[1]));
            steps.push_back(intToString(time[0]));
            steps.push_back(intToString(time[0]) + " " + intToString(time[2]));
        } else {
            total_time += time[1];
            steps.push_back(intToString(time[0]) + " " + intToString(time[1]));
        }
    }

    cout << total_time << endl;
    for (int i = 0; i < steps.size(); i++) {
        cout << steps[i] << endl;
    }

}