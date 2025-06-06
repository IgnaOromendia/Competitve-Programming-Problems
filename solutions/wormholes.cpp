#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>

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

constexpr int INF  = 1e9;
constexpr int MAXN = 0;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

struct Edge {
    int from, to, cost;
    Edge(int from, int to, int cost) : from(from), to(to), cost(cost) {}
    Edge() : from(0), to(0), cost(0) {}
};

int n, m;

// Bellman Ford
bool find_negative_cycle(vector<Edge>& edges) {
    vi dist(n, INF);
    int x;

    forn(i,0,n) {
        x = -1;

        for(Edge e: edges) 
            if(dist[e.from] + e.cost < dist[e.to]) {
                dist[e.to] = dist[e.from] + e.cost;
                x = e.to;
            }
        
    }

    return x != -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int t; cin >> t;

    while(t--) {
        cin >> n >> m;

        vector<Edge> edges(m);

        forn(i,0,m) {
            int from, to, c; cin >> from >> to  >> c;
            edges[i] = Edge(from, to, c);
        }

        cout << (find_negative_cycle(edges) ? "possible" : "not possible") << "\n";

    }
}