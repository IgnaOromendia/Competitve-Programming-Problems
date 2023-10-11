#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
using node = pair<int, int>;

#define IMP "IMPOSSIBLE"

int n, m;
vector<bool> marked_edge;
vector<vector<node> > adj;
vector<int> path;

// O(m)
void find_eulerian_path(int v) {
    for(node &u: adj[v]) {
        if(marked_edge[u.second]) continue;
        marked_edge[u.second] = true;
        find_eulerian_path(u.first);
    }
    path.push_back(v);
}

int main() {
    cin >> n >> m;

    adj.assign(n+1, vector<node>());
    marked_edge.assign(m+1, false);

    int j = 0;
    while(m--) {
        int v, u; cin >> v >> u;
        adj[v].push_back(make_pair(u,j));
        adj[u].push_back(make_pair(v,j));
        j++;
    }

    find_eulerian_path(1);

    if (path[0] == path[path.size()-1] and path.size()-1 == marked_edge.size()-1) {
        for(int i = 0; i < path.size(); i++) {
            cout << path[i] << " ";
        }
        cout << endl;
    } else {
        cout << IMP << endl;
    }
}