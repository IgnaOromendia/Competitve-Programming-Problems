#include <iostream>
#include <vector>
#include <queue>

using namespace std;
using node = long long;
using cost = int;
using dist = int;
using neighborhood = vector<vector<pair<cost,node> > >;
using node_dist = pair<dist, node>;

// Constants
const long long INF = 1e9;

// Structs

struct edge_t {
    edge_t(cost c, node v, node u) {this->c = c; this->v = v; this->u = u;}
    cost c;
    node v, u;
};

// Variables

int c, k;
int min_path;
long long n, m, s, t;

neighborhood neighbors;
neighborhood inverted_neighbors;
vector<edge_t> original_streets;
vector<edge_t> inverted_original_streets;
vector<edge_t> candidate_streets;
vector<bool> processed;
vector<dist> distance_S;
vector<dist> distance_T;
priority_queue<node_dist> minHeap;

// *** AUXILIARS ***

void reset_variables() {
    original_streets.clear();
    inverted_original_streets.clear();
    candidate_streets.clear();
}

// *** MAIN ***

void dijkstra_minheap(node initial, vector<dist>& distances, neighborhood& neighborhood) {
    // Inicializa variables
    processed = vector<bool>(n+1,false);
    for(int i = 1; i <= n; i++) distances[i] = INF;
    distances[initial] = 0;
    minHeap.push(make_pair(0,initial));

    // Busca camino minimo
    while(!minHeap.empty()) {
        node v = minHeap.top().second; minHeap.pop();

        if (processed[v]) continue;
        processed[v] = true;

        for(auto z: neighborhood[v]) {
            cost w  = z.first;
            node u  = z.second;

            if (distances[v] + w < distances[u]) {
                distances[u] = distances[v] + w;
                minHeap.push(make_pair(-distances[u],u));
            }
        }
    }
}

void selectCandidate() {
    for(edge_t a: candidate_streets) {
        int candidate_path = distance_S[a.v] + a.c + distance_T[a.u];
        if(min_path > candidate_path) min_path = candidate_path;
    }
}

int main() {
    cin >> c;

    while(c--) {
        cin >> n >> m >> k >> s >> t;

        neighbors           = vector<vector<pair<dist,node> > >(n+1,vector<pair<dist,node> >(0));
        inverted_neighbors  = vector<vector<pair<dist,node> > >(n+1,vector<pair<dist,node> >(0));
        distance_S          = vector<dist>(n+1,INF);
        distance_T          = vector<dist>(n+1,INF);

        long long copiaM = m;
        while (copiaM--) {
            int l;              
            long long d, c;     
            cin >> d >> c >> l;

            edge_t a = edge_t(l,d,c);
            edge_t a_i = edge_t(l,c,d);

            original_streets.push_back(a);
            inverted_original_streets.push_back(a_i);

            neighbors[d].push_back(make_pair(l,c));
            inverted_neighbors[c].push_back(make_pair(l,d));
        }

        int copyK = k;
        while (copyK--) {
            int q;              
            long long u, v;     
            cin >> u >> v >> q;
            edge_t a = edge_t(q,u,v);
            edge_t b = edge_t(q,v,u);
            candidate_streets.push_back(a);
            candidate_streets.push_back(b);
        }
        
        // Dijkstra from s
        dijkstra_minheap(s,distance_S, neighbors);

        // Dijkstra from t
        dijkstra_minheap(t,distance_T, inverted_neighbors);

        min_path = distance_S[t];

        selectCandidate();

        if (min_path == INF) min_path = -1; 

        cout << min_path << endl;

        reset_variables();
    }
}