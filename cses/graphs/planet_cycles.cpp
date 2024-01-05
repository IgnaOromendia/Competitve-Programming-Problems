#include<iostream>
#include<vector>
#include<queue>

using namespace std;

const int max_planet = 2e5 + 5;

int n, steps = 0;
vector<int> adj, visited, path_length;
queue<int> path;

void dfs(int v) {
    path.push(v);

    if(!visited[v]) {
        visited[v] = true;
        steps++;
        dfs(adj[v]);
    } else {
        steps += path_length[v];
    }
}


int main() {
    ios_base::sync_with_stdio(false);

    cin >> n;

    adj.assign(n+1,0);
    visited.assign(n+1,0);
    path_length.assign(n+1, 0);

    for(int i = 1; i <= n; i++) cin >> adj[i];

    for(int v = 1; v <= n; v++) {
        if (!visited[v]) {
            steps = 0;
            dfs(v);

            int decrement = 1;

            while(!path.empty()) {
                if (path.front() == path.back()) decrement = 0; // We are in a cycle
                path_length[path.front()] = steps;
                steps -= decrement;
                path.pop();
            }
        }
    }

    for(int v = 1; v <= n; v++) cout << path_length[v] << " ";
    cout << endl;
}