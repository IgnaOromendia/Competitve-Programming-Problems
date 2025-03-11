#include<vector>
#include<queue>

using namespace std;

int n;
vector<vector<int> > adj;
vector<int> parent;

void bfs() {
    vector<bool> visited(n + 1, false);
    visited[1] = true;
    queue<int> q;
    q.push(1);

    while(!q.empty()) {
        int u = q.front(); q.pop();

        for (int w : adj[u]) {
            if (!visited[w]) {
                visited[w] = true;
                parent[w] = u;
                q.push(w);
            }
        }
    }
}