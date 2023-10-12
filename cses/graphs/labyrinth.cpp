#include<iostream>
#include<vector>
#include<queue>

using namespace std;
using coord = pair<int, int>;

#define INF 1e9
#define FLOOR '.'
#define WALL '#'
#define START 'A'
#define END 'B'
#define YES "YES"
#define NO "NO"
#define UP 'U'
#define DOWN 'D'
#define RIGHT 'R'
#define LEFT 'L'

int n, m;
vector<vector<char> > grid;
vector<char> step;
vector<char> path;


struct position {
    int node;
    int x;
    int y;
    position() {}
    position(int i, int j): node((i*m) + j), x(i), y(j) {}
};

position A, B;

bool in_range(int i, int j) {
    return 0 <= i and i < n and 0 <= j and j < m;
}

void neighbors(vector<pair<char,coord> >& c, position v) {
    c[0] = make_pair(UP , make_pair(v.x-1,v.y)); 
    c[1] = make_pair(RIGHT ,make_pair(v.x,v.y+1));
    c[2] = make_pair(LEFT, make_pair(v.x,v.y-1));
    c[3] = make_pair(DOWN, make_pair(v.x+1,v.y));
}

int bfs() {
    step.assign(n*m, WALL);
    vector<bool> visited(n*m, false);
    vector<int> dist(n*m, INF);
    vector<pair<char,coord> > coords(4);  
    visited[A.node] = true;
    dist[A.node] = 0;
    queue<position> q;
    q.push(A);

    while(!q.empty()) {
        position u = q.front(); q.pop();

        neighbors(coords, u);

        for(auto &co: coords) {
            coord c = co.second;
            char dir = co.first;
            if (!in_range(c.first, c.second)) continue;

            position w(c.first,c.second);

            if (!visited[w.node] and grid[c.first][c.second] != WALL) {
                step[w.node]    = dir;
                visited[w.node] = true;
                dist[w.node]    = dist[u.node] + 1;
                q.push(w);
            }
        }
    }

    return dist[B.node];
}

void build_path(position v) {
    if (v.node == A.node) return;
    path.push_back(step[v.node]);
    if (step[v.node] == UP)     build_path(position(v.x+1, v.y));
    if (step[v.node] == DOWN)   build_path(position(v.x-1, v.y));
    if (step[v.node] == RIGHT)  build_path(position(v.x, v.y-1));
    if (step[v.node] == LEFT)   build_path(position(v.x, v.y+1));
}

int main() {
    cin >> n >> m;

    grid.assign(n, vector<char>(m));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == START) A = position(i,j);
            if (grid[i][j] == END) B = position(i,j);
        }
    }

    int dist = bfs();
    if (dist != INF) {
        cout << YES << endl;   
        cout << dist << endl;
        build_path(B);
        for(int i = dist - 1; i >= 0; i--) cout << path[i];
        cout << endl;
    } else {
        cout << NO << endl;
    }
     
}