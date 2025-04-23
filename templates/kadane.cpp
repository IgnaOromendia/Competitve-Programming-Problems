#include <vector>

using namespace std;

#define forn(i,from,to) for (int i = from; i < to; i++)

// Máxima suma del intervalo [a,b] en una secuencia de números
int kadane(const vector<int>& v) {
    int res = v[1], curr = -1;
    forn(i, 1, v.size()) {
        curr = max(v[i], curr + v[i]);
        res = max(curr, res);
    }
    return res;
}