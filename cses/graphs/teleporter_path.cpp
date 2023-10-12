#include<iostream>
#include<vector>

using namespace std;

#include<iostream>
#include<vector>
#include<stack>

using namespace std;
using node = pair<int, int>;

#define IMP "IMPOSSIBLE"

int n, m;
vector<bool> marked_edge;
vector<int> degree_in, degree_out;
vector<vector<node> > adj;
vector<int> path;

// O(n)
bool validate() {
    bool possible = true;
    int odd = 0;
    for(int i = 2; i <= n; i++) {
        if ((degree_in[i] + degree_out[i]) % 2 == 1) odd++;
        if(abs(degree_in[i] - degree_out[i]) > 1) possible = false;
    }
    return odd <= 2 and possible;
}

// O(m)
void find_eulerian_path(int s) {
    stack<int> st;
    st.push(s);

    while(!st.empty()) {
        int v = st.top();
        bool degree_zero = true;

        while(!adj[v].empty()) {
            int u    = adj[v].back().first;
            int edge = adj[v].back().second;
            adj[v].pop_back();

            if(!marked_edge[edge]) {
                marked_edge[edge] = true;
                st.push(u);
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
    degree_in.assign(n+1, 0);
    degree_out.assign(n+1, 0);

    int j = 0;
    // O(n + m)
    while(j < m) {
        int v, u; cin >> v >> u;
        degree_out[v]++;
        degree_in[u]++;
        adj[v].push_back(make_pair(u,j));
        j++;
    }

    if (validate()) {
        // O(m)
        find_eulerian_path(1);

        int path_sz = path.size();

        if (path_sz == m+1 and path[path_sz-1] == 1 and path[0] == n) {
            for(int i = path_sz - 1; i >= 0; i--) cout << path[i] << " ";
            cout << endl;
        } else {
            cout << IMP << endl;
        }

    } else {
        cout << IMP << endl;
    }
}