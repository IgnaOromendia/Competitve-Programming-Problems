#include <vector>
#include <iostream>
#include <queue>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > mat;
typedef vector<vector<int> > graph;
typedef pair<int,int> pi;
typedef pair<double,double> pd;

#define mp make_pair

const int INF = 1e9;

int n, m;
mat capacity; 
graph net;

int bfs(int s, int t, vi& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pi > q;
    q.push(make_pair(s, INF));

    while (!q.empty()) {
        auto [cur, flow] = q.front();
        q.pop();

        for (int next : net[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                long long new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push(mp(next, new_flow));
            }
        }
    }

    return 0;
}

long long maxflow(int s, int t) {
    int flow = 0, new_flow;
    vi parent(n+1);

    while (new_flow = bfs(s, t, parent)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}