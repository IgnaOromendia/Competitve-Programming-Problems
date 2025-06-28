#include <vector>

using namespace std;

typedef vector<int> vi;

#define forn(i,from,to) for (int i = from; i < to; i++)

struct DSU {
    vi p, size;

    DSU(int n){
        p = vi(n, -1);
        size = vi(n, 1);
        forn(i, 0, n) p[i] = i;
    }

    void unite(int v, int w) {
        v = find(v), w = find(w);
        if(v == w) return;
        if(size[v] < size[w]) swap(v, w);
        p[w] = v;
        size[v] += size[w]; 
    }
    
    int find(int v) {
        return p[v] == v ? v : p[v] = find(p[v]);
    }

};