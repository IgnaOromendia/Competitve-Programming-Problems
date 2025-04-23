#include<iostream>
#include<vector>

#define ll long long

using namespace std;

vector<vector<int> > adj;
vector<int> color;
int n;
ll k = 0;

void dfs(int v) {
    if (color[v] == 1) k++;
    for(int u: adj[v]) 
        if (color[u] == -1) {
            color[u] = 1 - color[v];
            dfs(u);
        }
}

ll solve() {
    for (int i = 0; i < n; i++)
        if (color[i] == -1) {
            color[i] = 1;
            dfs(i);
        }

    return k * (n - k) - (n - 1);
}


int main() {
    cin >> n;

    adj.assign(n, vector<int>());
    color.assign(n, -1);

    for(int i = 0; i < n - 1; i++) {
        int u,v; cin >> v >> u; u--;v--;
        adj[v].push_back(u);
        adj[u].push_back(v);
    }

    cout << solve() << endl;

}