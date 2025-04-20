#include<vector>
#include<iostream>
#include<string>
#include<queue>

using namespace std;

const int INF = 10e8;

vector<vector<int> > net;
vector<vector<int> > capacity;

int map_talle(string talle) {
    if (talle == "XS") return 1;
    if (talle == "S") return 2;
    if (talle == "M") return 3;
    if (talle == "L") return 4;
    if (talle == "XL") return 5;
    return 6;
}

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int> > q;
    q.push(make_pair(s, INF));

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : net[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push(make_pair(next, new_flow));
            }
        }
    }

    return 0;
}

int maxflow(int s, int t, int n) {
    int flow = 0;
    vector<int> parent(n+1);
    int new_flow;

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

int main() {
    int c; cin >> c;
    while (c--) {
        int n,m;cin >> n >> m;

        net.assign(m+8, vector<int>());
        capacity.assign(m+8, vector<int>(m+8,0));

        for(int i = 1; i <= m; i++) {
            net[0].push_back(i);
            net[i].push_back(0);
            capacity[0][i] = 1;
            capacity[i][0] = 0;
        }

        for(int i = 1; i <= m; i++) {
            string t1, t2; cin >> t1 >> t2;

            int node_t1 = m + map_talle(t1);
            int node_t2 = m + map_talle(t2);

            net[i].push_back(node_t1);
            net[node_t1].push_back(i);

            capacity[i][node_t1] = 1;
            capacity[node_t1][i] = 0;

            net[i].push_back(node_t2);
            net[node_t2].push_back(i);

            capacity[i][node_t2] = 1;
            capacity[node_t2][i] = 0;
        }

        int t = m + 7;

        for (int i = m+1; i <= m + 6; i++) {
            net[i].push_back(t);
            net[t].push_back(i);

            capacity[i][t] = n / 6;
            capacity[t][i] = 0;
            
        }

        cout << (maxflow(0,t,m+8) == m ? "YES" : "NO") << endl;

    }
}