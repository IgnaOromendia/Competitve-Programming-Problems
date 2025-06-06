#include<iostream>
#include<vector>

using namespace std;

typedef vector<int> vi;
typedef vector<vector<int> > graph;
#define forn(i,from,to) for (int i = from; i < to; i++)


#define NOT_VISITED -1
#define PROCESSING 0
#define VISITED 1

graph adj, adjT;
vi order, state, strong_component;
int n;

void dfs(int v, vector<vector<int> > &adj) {
    for(int u: adj[v])
        if(state[u] == NOT_VISITED) {
            strong_component[u] = strong_component[v];
            dfs(u, adj);
        }
    
    state[v] = VISITED;
    order.push_back(v);
}

void find_strong_components() {
    forn(i,0,n)
        if(state[i] == NOT_VISITED)
            dfs(i, adj);


    state            = vector<int>(n+1, NOT_VISITED);
    strong_component = vector<int>(n+1, 0);
    int count = 0;

    while(!order.empty()) {
        int v = order.back(); order.pop_back();
        if(state[v] == NOT_VISITED) {
            count++;
            strong_component[v] = count;
            dfs(v, adjT);
        }
    }
}