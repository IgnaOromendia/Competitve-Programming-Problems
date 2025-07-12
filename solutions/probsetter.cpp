#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <queue>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > mat;
typedef vector<vector<int> > graph;
typedef pair<int,int> pi;
typedef pair<double,double> pd;

#define pb push_back
#define mp make_pair

#define forn(i,from,to) for (int i = from; i < to; i++)

constexpr int INF  = 1e9;
constexpr int MAXN = 0;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

graph net;
mat capacity;

int bfs(int s, int t, vi& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pi> q;
    q.push({s, INF});

    while (!q.empty()) {
        auto [cur, flow] = q.front();
        q.pop();

        for (int next : net[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t) return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t, int n) {
    int flow = 0, new_flow;
    vi parent(n);

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
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int n, nk, np;

    while(cin >> nk >> np, nk+np) {

        n = nk + np + 2;
        int source = n-2, sink = n-1;
        int requested = 0;

        net.assign(n, vi());
        capacity.assign(n, vi(n, 0));

        forn(c, 0, nk) {
            cin >> capacity[c][sink];
            requested += capacity[c][sink];
            net[c].pb(sink);
        }

        forn(i, 0, np) {
            int e; cin >> e;

            capacity[source][i+nk] = 1;
            net[source].pb(i+nk);
            net[i+nk].pb(source);
            
            while(e--) {
                int c; cin >> c; c--;
                capacity[i+nk][c] = 1;
                net[i+nk].pb(c);
                net[c].pb(i+nk);
            }
        }

        int flow = maxflow(source, sink, n);

        if (flow == requested) {
            cout << "1\n";

            forn(c, 0, nk) {
                for (int p : net[c])
                    if (p >= nk && p < nk + np && capacity[c][p] > 0) cout << (p-nk+1) << " ";
                cout << "\n";
            }

        } else {
            cout << "0\n";
        }

    }
}