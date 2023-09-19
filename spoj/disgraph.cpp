#include<iostream>
#include<vector>
#include<sstream>
#include<string>

using namespace std;

// judge: https://www.spoj.com/problems/DISGRAPH/

const long long INF = 1e9;

int n;
vector<int> state;
vector<int> memo;
vector<int> backedge_lower_limite_on;
vector<int> backedge_upper_limite_on;
vector<vector<int> > tree_edges; 
vector<vector<int> > edges;

const int NOT_VISITED = -1;
const int PROCESSING  = 0;
const int VISITED     = 1;

// Fin backedges O(n + m)
void dfs(int v, int parent = -1) {
    state[v] = PROCESSING;
    for(int u: edges[v]) {
        if (state[u] == NOT_VISITED) {
            // Generating a tree
            tree_edges[v].push_back(u);
            dfs(u, v);
        } else if (u != parent and state[u] == PROCESSING) {
            backedge_lower_limite_on[v]++;
            backedge_upper_limite_on[u]++;
        }
    }

    state[v] = VISITED;
}

int coverd(int v, int parent = -1) {
    if(memo[v] != -1) return memo[v];
    int res = backedge_lower_limite_on[v];
    res    -= backedge_upper_limite_on[v];
    for(int son: tree_edges[v]) {
        if (son != parent) res += coverd(son, v);
    }
    memo[v] = res;
    return res;
}

int bridges() {
    int components  = 0;
    int bridges     = 0;

    // Backedges
    for(int i = 0; i < n; i++) {
        if(state[i] == NOT_VISITED){
            dfs(i);
            components++;
        } 
    }

    for (int i = 0; i < n; i++) {
        if (coverd(i) == 0) bridges ++;
    }

    int count = bridges -= components;
    return  count > 0 ? count : 0;
}

int main() {
    cin >> n;

    int min_grade = INF;
    int i = 0;
    string line;
    getline(cin, line);

    while(i < n) {
        getline(cin,line);
        istringstream iss(line);
        int u;
        vector<int> s;
        while(iss >> u) {
            s.push_back(u);
        }
        edges.push_back(s);
        if (s.size() < min_grade) min_grade = s.size();
        i++;
    }

    tree_edges               = vector<vector<int> >(n,vector<int>(0));
    state                    = vector<int>(n,NOT_VISITED);
    memo                     = vector<int>(n,-1);
    backedge_lower_limite_on = vector<int>(n,0);
    backedge_upper_limite_on = vector<int>(n,0);

    int bridges_count = bridges();
    int road_number = bridges_count > 0 ? 1 : 0;
    cout << road_number << endl;
}