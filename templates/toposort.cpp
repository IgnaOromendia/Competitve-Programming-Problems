#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > mat;
typedef pair<int,int> pi;
typedef pair<double,double> pd;

#define NOT_VISITED -1
#define VISITING 0
#define VISITED 1

#define pb push_back
#define mp make_pair

#define forn(i,from,to) for (int i = from; i < to; i++)

constexpr int INF  = 1e9;
constexpr int MAXN = 1e5 + 1;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

int n;
mat adj;
vi order, state;
bool cycle = false;

void dfs(int v) {
    state[v] = VISITING;

    for(int u: adj[v])
        if (state[u] == NOT_VISITED) dfs(u);
        else if (state[u] == VISITING) cycle = true;

    order.pb(v);
    state[v] = VISITED;
}

void toposort() {
    forn(i,0,n) 
        if (state[i] == NOT_VISITED) 
            dfs(i);
}