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
const int MAXN = 30;
const int mod  = 1e9 + 7;
const float PI = 3.14159265359;

int nodes[MAXN], visited[MAXN];
int graph[MAXN][MAXN];
vi order;

void dfs(int v) {
    visited[v] = true;

    forn(u, 0, MAXN) 
        if (graph[v][u] and !visited[u]) {
            // cout << v << " -> " << u << endl;
            dfs(u);
        }
            
    order.pb(v);
}

void all_topological_sort_aux(vi &result) {
    bool flag = false;

    for (int i = 0; i < MAXN; i++) {
        if (nodes[i] && !visited[i]) {
            bool canVisit = true;
            for (int j = 0; j < MAXN; j++) {
                if (graph[j][i] && !visited[j]) {
                    canVisit = false;
                    break;
                }
            }

            if (canVisit) {
                visited[i] = true;
                result.pb(i);

                all_topological_sort_aux(result);

                visited[i] = false;
                result.pop_back();
                flag = true;
            }
        }
    }

    if (!flag) {
        for (int i = 0; i < result.size(); i++) {
            cout << char(result[i] + 'a');
        }
        cout << endl;
    }
}

void all_topological_sort() {
    vi result;
    memset(visited, 0, sizeof(visited));
    all_topological_sort_aux(result);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    string line;

    bool first_case = true;

    while(getline(cin, line)) {
        if (!first_case) cout << endl;

        memset(graph, 0, sizeof(graph));
        memset(nodes, 0, sizeof(nodes));

        for(int i = 0; i < line.length(); i+=2) nodes[line[i] - 'a'] = 1;
        
        getline(cin, line);

        for(int i = 0; i < line.length(); i+=4)         
            graph[line[i] - 'a'][line[i+2] - 'a'] = 1;

        all_topological_sort();

        first_case = false;
    }
            
}