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
constexpr int MAXN = 50 * 50;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;
constexpr pi dir[4] = {{-1,0}, {0,1}, {1,0}, {0,-1}};

mat capacity;
graph adj;

int bfs(int s, int t, vi& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2; 
    queue<pi> q;
    q.push({s, INF});

    while (!q.empty()) {
        auto [cur, flow] = q.front();
        q.pop();

        for(int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next] > 0) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t) return new_flow; 
                q.push({next, new_flow});
            }
        }   
    }

    return 0;
}

int maxflow(int s, int t, int N) {
    int flow = 0, new_flow;
    vi parent(N);

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

    int n, m, t, b; cin >> t;

    while(t--) {
        cin >> n >> m >> b;

        // Cada nodo v va a estar representado como v_in y v_out con capaicdad 1 entre ellos
        // Los primeros N/2 van a ser in y los demas out
        int cells = n * m;
        int N = 2 * cells + 2;
        int source = N - 2, sink = N - 1;
        
        capacity.assign(N, vi(N, 0));
        adj.assign(N, vi());
        mat is_bank(m, vi(n, 0));

        forn(i,0,b) {
            int x,y; cin >> x >> y;
            is_bank[y-1][x-1] = 1;
        }

        // cout << N << endl;

        forn(i, 0, n) {
            forn(j, 0, m) {
                int u_in = i * m + j;
                int u_out = u_in + cells;                

                if (is_bank[j][i]) {
                    // s -> b_out
                    capacity[source][u_out] = 1;
                    adj[source].pb(u_out);
                    adj[u_out].pb(source);
                } else {
                    // u_in -> u_out
                    capacity[u_in][u_out] = 1;
                    adj[u_in].pb(u_out);
                    adj[u_out].pb(u_in);
                }

                for (auto [dx, dy] : dir) {
                    int ni = i + dx, nj = j + dy;

                    // u_out -> v_in
                    if (ni >= 0 && ni < n && nj >= 0 && nj < m) {
                        int v_in = ni * m + nj;

                        capacity[u_out][v_in] = 1;
                        adj[v_in].pb(u_out);
                        adj[u_out].pb(v_in);
                    }
                }

                // u_out -> t sii es borde
                if (i == 0 or i == n-1 or j == 0 or j == m-1) {
                    capacity[u_out][sink] = 1;
                    adj[u_out].pb(sink);
                }
                    
            }
        }

        int flow = maxflow(source, sink, N);

        if (flow != b) cout << "not ";

        cout << "possible\n"; 
    }
}