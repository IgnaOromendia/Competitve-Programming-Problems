#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <math.h>

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
const float PI = 3.14159265359;

int graph[6][6];

void init_graph() {
    memset(graph, 1, sizeof(graph));

    forn(i,0,6) graph[i][i] = 0;

    graph[1][4] = graph[4][1] = 0;
    graph[2][4] = graph[4][2] = 0;
}

void dfs(int v,int k,string s){ //DFS Traversal
    s += char(v+'0'); 

    if (k==8) {
        cout << s <<endl;
        return;
    }

    forn(u,1,6)
        if (graph[v][u]) {
            graph[v][u] = graph[u][v] = 0;
            dfs(u,k+1,s);
            graph[v][u] = graph[u][v] = 1;

        }
    
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    init_graph();
    dfs(1,0,"");
}