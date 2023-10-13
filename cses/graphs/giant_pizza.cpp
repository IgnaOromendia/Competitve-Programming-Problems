#include<iostream>
#include<vector>

using namespace std;

#define IMP "IMPOSSIBLE"

int n, m;
vector<vector<int> > adj, adj_T;
vector<bool> visited, assignment;
vector<int> str_comp, stack;

// 2 - SAT

void dfs(int v, vector<vector<int> > &adj) {
    visited[v] = true;
    for(int u: adj[v]) {
        if(!visited[u]) {
            str_comp[u] = str_comp[v];
            dfs(u, adj);
        }
    }
    stack.push_back(v);
}

int find_strong_components() {
    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            dfs(i, adj);
        }
    }

    visited.assign(n, false);
    str_comp.assign(n, -1);
    int count = 0;

    while(!stack.empty()) {
        int v = stack.back(); stack.pop_back();
        if(!visited[v]) {
            count++;
            str_comp[v] = count;
            dfs(v, adj_T);
        }
    }

    return count;
}

bool choose_toppings() {
    find_strong_components();

    assignment.assign(n / 2, false);
    for(int i = 0; i < n; i += 2) {
        if (str_comp[i] == str_comp[i+1]) return false;
        assignment[i / 2] = str_comp[i] > str_comp[i + 1];
    }
    return true;
}

void add_disjunction(int a, bool na, int b, bool nb) {
    a = 2*a ^ na;
    b = 2*b ^ nb;
    int neg_a = a ^ 1; // ^ bit's XOR
    int neg_b = b ^ 1;
    adj[neg_a].push_back(b);
    adj[neg_b].push_back(a);
    adj_T[b].push_back(neg_a);
    adj_T[a].push_back(neg_b);
}

int main() {
    cin >> n >> m;

    adj.assign(2*n, vector<int>());
    adj_T.assign(2*n, vector<int>());
    visited.assign(2*n, false);
    str_comp.assign(2*n, -1);

    int i = 0;
    while(i < m) {
        // + 1 + 2
        // - 1 + 3
        // + 4 - 2
        i++;
    }

    if(choose_toppings()) {

    } else {
        cout << IMP << endl;
    }
}