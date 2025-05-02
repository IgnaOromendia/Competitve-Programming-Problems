#include <iostream>
#include <vector>
#include <cstring>
#include <bitset>
#include <iomanip>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > mat;
typedef vector<vector<float> > matf;
typedef pair<int,float> pif;
typedef pair<double,double> pd;
typedef vector<vector<pif> > weighted_graph;

#define pb push_back
#define mp make_pair

#define forn(i,from,to) for (int i = from; i < to; i++)

constexpr float INF  = 1e9;
constexpr int MAXN = 51, MAXM = 1000, MAXP = 13;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

int n, p;
int store[MAXP];
float memo[MAXP][1 << MAXP], dist[MAXN][MAXN], price[MAXP];

void floyd() {
    forn(k,0,n) forn(i,0,n) forn(j,0,n) 
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}

float tsp(int v, int visited, int stores) {
    if (visited == stores) return dist[store[v]][0];

    if (memo[v][visited] != -1) return memo[v][visited];

    memo[v][visited] = INF;

    forn(u, 0, p) {
        if (!(stores & (1 << u)) or (visited & (1 << u))) continue;
        memo[v][visited] = min(memo[v][visited], dist[store[v]][store[u]] + tsp(u, visited | (1 << u), stores));
    }

    return memo[v][visited];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int t, m; cin >> t;

    while (t--) {

        cin >> n >> m;

        n++;
        
        fill(&memo[0][0], &memo[0][0] + MAXP * (1 << MAXP), -1.0f);
        fill(&dist[0][0], &dist[0][0] + MAXN * MAXN, INF);

        forn(i,0,n) dist[i][i] = 0;

        forn(i, 0, m) {
            int u,v; cin >> u >> v;
            float c; cin >> c;
            dist[u][v] = dist[v][u] = min(dist[u][v], c);;
        }

        cin >> p;


        forn(i,0,p) {
            int s; float d; cin >> s >> d;
            store[i] = s;
            price[i] = d;
        }

        floyd();

        float best_saving = 0.0f;

        // Probamos todos los subconjuntos de tiendas
        forn(S, 1, 1 << p) {
            float profit = 0.0f;

            // Ganancia del subconjunto
            forn(i, 0, p) if (S & (1 << i)) 
                    profit += price[i];

            float cost = INF;

            fill(&memo[0][0], &memo[0][0] + MAXP * (1 << MAXP), -1.0f);

            forn(i, 0, p) {
                if (!(S & (1 << i))) continue;
                float this_cost = dist[0][store[i]] + tsp(i, 1 << i, S);
                cost = min(cost, this_cost);
            }

            best_saving = max(best_saving, profit - cost);
        }

        if (best_saving > 1e-6)
            cout << "Daniel can save $" << fixed << setprecision(2) << best_saving << "\n";
        else
            cout << "Don't leave the house\n";
    }
}