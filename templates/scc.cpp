#include<iostream>
#include<vector>

using namespace std;

typedef vector<int> vi;
typedef vector<vector<int> > graph;
#define forn(i,from,to) for (int i = from; i < to; i++)

graph adj, adjT;
vi order, visited, strong_component;
int n, visitTimer = 1;

void dfs(int v, graph& adj) {
    visited[v] = visitTimer;

    for(int u: adj[v])
        if(visited[u] != visitTimer) {
            strong_component[u] = strong_component[v];
            dfs(u, adj);
        }
    
    order.push_back(v);
}

void find_strong_components() {
    forn(i,0,n)
        if(visited[i] != visitTimer)
            dfs(i, adj);


    visitTimer++;
    strong_component = vector<int>(n+1, 0);
    int count = 0;

    for(int i = n-1; i >= 0; i--) {
        int v = order[i];
        if(visited[v] != visitTimer) {
            count++;
            strong_component[v] = count;
            dfs(v, adjT);
        }
    }
}