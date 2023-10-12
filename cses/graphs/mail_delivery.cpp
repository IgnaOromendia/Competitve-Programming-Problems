#include<iostream>
#include<vector>
#include<stack>

using namespace std;
using node = pair<int, int>;

#define IMP "IMPOSSIBLE"

int n, m;
vector<bool> marked_edge;
vector<vector<node> > adj;
vector<int> path;

// O(m)
void find_eulerian_path(int s) {
    for(int i = 1; i <= n; i++) {
        if(adj[i].size()&1) {
            cout << IMP << endl;
            return;
        }
    }

    stack<int> st;
    st.push(s);

    while(!st.empty()) {
        int v = st.top();
        bool degree_zero = true;

        while(!adj[v].empty()) {
            node u = adj[v].back(); adj[v].pop_back();
            if(!marked_edge[u.second]) {
                marked_edge[u.second] = true;
                st.push(u.first);
                degree_zero = false;
                break;
            }
        }

        if(degree_zero) {
            path.push_back(v);
            st.pop();
        }
    }
}

int main() {
    cin >> n >> m;

    adj.assign(n+1, vector<node>());
    marked_edge.assign(m+1, false);

    int j = 0;
    // O(n + m)
    while(j < m) {
        int v, u; cin >> v >> u;
        adj[v].push_back(make_pair(u,j));
        adj[u].push_back(make_pair(v,j));
        j++;
    }

    // O(m)
    find_eulerian_path(1);

    if (path.size() == m+1) {
        for(int i = 0; i < path.size(); i++) {
            cout << path[i] << " ";
        }
        cout << endl;
    } else {
        cout << IMP << endl;
    }
}