#include<iostream>
#include<vector>

using namespace std;

// Contants
#define NOT_VISITED -1
#define PROCESSING 0
#define VISITED 1

// Variables
vector<vector<int> > adj, adj_T, adj_cond;
vector<long long> costs_cond, costs;
vector<int> stack, state, str_comp, memo;
int n, m;

void dfs(int v, vector<vector<int> > &adj) {
    state[v] = PROCESSING;
    for(int u: adj[v]) {
        if(state[u] == NOT_VISITED) {
            str_comp[u] = str_comp[v];
            dfs(u, adj);
        }
    }
    state[v] = VISITED;
    stack.push_back(v);
}

int find_strong_components() {
    for(int i = 1; i < n+1; i++) {
        if(state[i] == NOT_VISITED) {
            dfs(i, adj);
        }
    }

    state.assign(n+1, NOT_VISITED);
    str_comp.assign(n+1, -1);
    int count = 0;

    while(!stack.empty()) {
        int v = stack.back(); stack.pop_back();
        if(state[v] == NOT_VISITED) {
            count++;
            str_comp[v] = count;
            dfs(v, adj_T);
        }
    }

    return count;
}

void dfs_condense(int v) {
    state[v] = VISITED;
    for(int u: adj[v]) {
        if (str_comp[u] != str_comp[v]) 
                adj_cond[str_comp[v]].push_back(str_comp[u]);
        if (state[u] == NOT_VISITED) {
            costs_cond[str_comp[u]] += costs[u];
            dfs_condense(u);
        }
    }
}

void condense_strong_components(int k) {
    adj_cond.assign(k+1, vector<int>());
    state.assign(n+1, NOT_VISITED);
    costs_cond.assign(k+1, 0);

    for(int v = 1; v <= n; v++) {
        if(state[v] == NOT_VISITED) {
            costs_cond[str_comp[v]] += costs[v];
            dfs_condense(v);
        }
    }
}

int max_profit(int v) {
    if (memo[v] == -1) {
        memo[v] = costs_cond[v];

        long long max_sum = 0;
        for(int u: adj_cond[v]) {
            long long sum_u = max_profit(u);
            if(sum_u > max_sum) max_sum = sum_u;
        }

        memo[v] += max_sum;
    }

    return memo[v];
}

long long max_coins() {
    int amount_str_cmp = find_strong_components();
    condense_strong_components(amount_str_cmp);

    memo.assign(amount_str_cmp+1, -1);

    long long max_s = 0;
    for(int v = 1; v <= amount_str_cmp; v++) {
        long long sum = max_profit(v);
        if (sum > max_s) max_s = sum;
    }

    return max_s;
}

int main() {
    cin >> n >> m;

    costs.assign(n+1, -1);
    adj.assign(n+1, vector<int>());
    adj_T.assign(n+1, vector<int>());
    state.assign(n+1, NOT_VISITED);
    str_comp.assign(n+1, -1);

    for(int i = 1; i <= n; i++) 
        cin >> costs[i];

    while(m--) {
        int u,v; cin >> u >> v;
        adj[u].push_back(v);
        adj_T[v].push_back(u);
    }

    cout << max_coins() << endl;
}