#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <string>
#include <algorithm>

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
constexpr int MAXN = 100;
constexpr int mod  = 1e9 + 7;
constexpr double PI = 3.14159265359;

int n, visitTimer = 1;
graph adj, adjT;
vi order, visited, scc;

int dfs(int v, graph &adj, bool save_order) {
    int nodes = 0;
    visited[v] = visitTimer;

    for(int u: adj[v])
        if(visited[u] != visitTimer) {
            scc[u] = scc[v];
            nodes += 1 + dfs(u, adj, save_order);
        }
            
        
    if (save_order) order.push_back(v);
    return nodes;
}

int min_subdict_size() {
    forn(i,0,n) 
        if(visited[i] != visitTimer) 
            dfs(i, adj, true);

    visitTimer++;

    int count = 0, subdic_size = 0;
    vi sizeOne;

    for(int i = n-1; i >= 0; i--) {
        int v = order[i];
        if(visited[v] != visitTimer) {
            scc[v] = count;
            int curr_size = 1 + dfs(v, adjT, false);

            if (curr_size == 1) {
                sizeOne.pb(v);
                scc[v] = -1;
                continue;
            }

            subdic_size += curr_size;
            count++;
        }
    }
        

    for(int v: sizeOne)
        for(int u: adjT[v]) 
            if (scc[u] != -1) {
                subdic_size++;
                scc[v] = count;
                break;;
            }
        
            
    return subdic_size;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    string line, word, def_word;

    while(cin >> n, n) {
        cin.ignore();
    
        int nodes = 0;

        adj.resize(n);
        adjT.resize(n);
        visited.assign(n, 0);
        scc.assign(n, -1);

        unordered_map<string,int> word_to_node;
        vector<string> node_to_word(n), words;
        word_to_node.reserve(n);
        words.reserve(n);

        forn(i,0,n) {
            getline(cin, line);

            istringstream line_stream(line);
            
            // Agregamos el i-esimo nodo
            if (line_stream >> word) 
                if (word_to_node.find(word) == word_to_node.end()) {
                    node_to_word[nodes] = word;
                    words.pb(word);
                    word_to_node[word] = nodes++;
                }
                    

            int from = word_to_node[word];
                
            // Agregamos los nodos a los los tiene una arista dirigida
            while(line_stream >> def_word) {
                if (word_to_node.find(def_word) == word_to_node.end()) {
                    node_to_word[nodes] = def_word;
                    words.pb(def_word);
                    word_to_node[def_word] = nodes++;
                }
                    
                int to = word_to_node[def_word];
                    
                adj[from].pb(to);
                adjT[to].pb(from);
            }

        }

        int subdic_size = min_subdict_size();

        cout << subdic_size << "\n";

        sort(words.begin(), words.end());

        bool firstCout = true;

        forn(i,0,n) 
            if (scc[word_to_node[words[i]]] != -1) {
                if (firstCout) {
                    cout << words[i];
                    firstCout = false;
                } else {
                    cout << " " << words[i];
                }
            }
        cout << "\n";

        adj.clear();
        adjT.clear();
        order.clear();
    }
}