#include<vector>
#include<iostream>

using namespace std;

// judge: https://cses.fi/problemset/task/1192

// Constants
const char LAND = '.';
const char WALL = '#';

// Variables
int n, m;
vector<vector<char> > grid;
vector<vector<int> > adj;
vector<bool> visited;

void dfs(int v) {
    visited[v] = true;
    for(int u: adj[v]) {
        if (!visited[u]) {
            dfs(u);
        }
    }
}

int count_rooms() {
    int num_rooms = 0;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int node = i*m + j;
            if (grid[i][j] == WALL) continue;
            if (!visited[node]) {
                dfs(node);
                num_rooms++;
            }
        }
    }

    return num_rooms;
}

int main() {
    cin >> n >> m;

    adj     = vector<vector<int> >(n*m, vector<int>());
    grid    = vector<vector<char> >(n, vector<char>(m));
    visited = vector<bool>(n*m, false);
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            char c; cin >> c;
            grid[i][j] = c;

            if (c == WALL) continue;

            // Up
            if (i > 0 and grid[i-1][j] == LAND) {
                adj[i*m + j].push_back((i-1)*m + j);
                adj[(i-1)*m + j].push_back(i*m + j);
            }

            // Left
            if (j > 0 and grid[i][j-1] == LAND) {
                adj[i*m + j].push_back(i*m + j - 1);
                adj[i*m + j - 1].push_back(i*m + j);
            }

            // Right
            if (j < m-1 and grid[i][j+1] == LAND) {
                adj[i*m + j].push_back(i*m + j + 1);
                adj[i*m + j + 1].push_back(i*m + j);
            }

            // Down
            if (i < n-1 and grid[i+1][j] == LAND) {
                adj[i*m + j].push_back((i+1)*m + j);
                adj[(i+1)*m + j].push_back(i*m + j);
            }
        }
    }
    
    cout << count_rooms() << endl;
}