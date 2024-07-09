#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int> > adj;

void dfs(int v, vector<int> & parents, vector<int> & heights, vector<int> & lows, vector<int> & pigeon_value) {
    for (int u : adj[v]) {
        if (parents[u]==-1) {
            parents[u]=v;
            heights[u] = heights[v]+1;
            lows[u]=heights[u];
            dfs(u, parents, heights, lows, pigeon_value);
            //Si esa rama no supera al padre, se convierte en una nueva componente 
            //conexa si el padre se elimina => Incrementa el pigeon value del padre
            if(lows[u]>=heights[v]) {
                pigeon_value[v]++;
            } else {
                lows[v] = min(lows[v],lows[u]);
            } 
        } else if (parents[v]!=u) {
            lows[v] = min(lows[v],heights[u]);
        }
    }
}


bool compare(pair<int,int>& a, pair<int,int>& b){ 
    if (a.second == b.second) return a.first < b.first;
    return a.second > b.second;
}

int main() {
    while(true) {
        int n, m; cin >> n >> m;
        if (n+m == 0) break;

        adj.assign(n, vector<int>());

        int v,u;cin >> v >> u;

        while(v >= 0) {
            adj[u].push_back(v);
            adj[v].push_back(u);
            cin >> v >> u;
        }

        vector<pair<int,int> > candidates;
        vector<int> parents(n,-1);
        vector<int> height(n,-1);
        vector<int> low(n,-1);
        vector<int> pigeon_value(n,1);

        parents[0] = 0;
        height[0] = 0;
        low[0] = 0;
        pigeon_value[0] = 0;

        dfs(0,parents,height,low,pigeon_value);

        for (int i = 0; i < n; i++) candidates.push_back(make_pair(i,pigeon_value[i]));

        sort(candidates.begin(), candidates.end(), compare);

        for(int i = 0; i < m; i++) cout << candidates[i].first << " " << candidates[i].second << endl;

        cout << endl;
    }
}