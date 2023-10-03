#include<iostream>
#include<vector>
#include<queue>

#define NOT_VISITED -1
#define VISITING 0
#define VISITED 1
#define IMP "IMPOSSIBLE"

using namespace std;

int n, m, cycle_start = -1, cycle_end = -1, timer = 0;
vector<int> cycle, father, state, time_in;
vector<vector<int> > adj;

void dfs(int v, int p = -1) {
    state[v] = VISITING;
    for(int u : adj[v]) {
        if(state[u] == NOT_VISITED) {
            father[u] = v;
            timer++;
            time_in[u] = timer;
            dfs(u, v);
        } else if(state[u] == VISITING) {
            cycle_start = v;
            cycle_end = u;
        }
    }
    state[v] = VISITED;
}

void find_cycle() {
    for(int i = 1; i <= n; i++) {
        if(state[i] == NOT_VISITED) {
            father[i] = i;
            time_in[i] = timer;
            dfs(i);
        }
    }
}

void build_cycle() {
    int it    = time_in[cycle_end] < time_in[cycle_start] ? cycle_start : cycle_end;
    int limit = it == cycle_start ? cycle_end : cycle_start;

    while(it != limit) {
        cycle.push_back(it);
        it = father[it];
    }
    cycle.push_back(limit);
}

void find_trip() {
    find_cycle();
    build_cycle();

    if (cycle_start == -1) {
        cout << IMP << endl;
    } else {
        cycle.push_back(cycle[0]);
        cout << cycle.size() << endl;
        for(int i = cycle.size() - 1; i >= 0; i--) {
            cout << cycle[i] << " ";
        }
        cout << endl;
    }    
}


int main() {
    cin >> n >> m;

    adj.resize(n+1);
    state.resize(n+1, NOT_VISITED);
    father.resize(n+1, -1);
    time_in.resize(n+1, -1);

    while(m--) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
    }

    find_trip();
}