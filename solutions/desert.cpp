#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > mat;
typedef vector<vector<int> > graph;
typedef pair<int,int> pi;
typedef pair<double,double> pd;

#define pb push_back
#define mp make_pair

#define forn(i,from,to) for (int i = from; i < to; i++)

// Bitset
#define contains(set, x) (set & (1 << x))
#define add(set, x) (set |= (1 << x))
#define size(set) __builtin_popcount(set)
#define remove(set, x) (set &= ~(1 << x);)

constexpr int INF  = 1e9;
constexpr int MAXN = 0;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

int curr_consumption = 0, curr_leak = 0;

double calc_tank(int new_pos, int old_pos) {
    double dist = new_pos - old_pos;
    return ((curr_consumption * dist / 100.0) + curr_leak * dist);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    double max_tank = 0, curr_tank = 0;
    int pos = 0;

    string line, element;

    while(getline(cin, line)) {
        stringstream ss(line);
        int new_pos;

        if (line == "0 Fuel consumption 0") break;

        ss >> new_pos;

        ss >> element;

        curr_tank += calc_tank(new_pos, pos);

        if (element == "Fuel") {
            ss >> element; // Consumimos la palabra consumption
            ss >> curr_consumption;
        } else if (element == "Leak") {
            curr_leak++;
        } else if (element == "Mechanic") {
            curr_leak = 0;
        } else if (element == "Gas") {
            ss >> element; // Consumimos la palabra Station
            max_tank = max(max_tank, curr_tank);
            curr_tank = 0;
        } else if (element == "Goal") {
            max_tank = max(max_tank, curr_tank);
            cout << fixed << setprecision(3) << max_tank << endl;

            curr_leak = 0;
            curr_tank = 0;
            pos = 0;
            curr_consumption = 0;
            max_tank = 0;
        }

        pos = new_pos;

    }


}