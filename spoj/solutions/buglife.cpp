#include<iostream>
#include<vector>
#include<string>

using namespace std;

int n, m;
bool suspect = false;
vector<int> state;
vector<int> gender;
vector<vector<int> > edges;

const int NOT_VISITED = -1;
const int PROCESSING  = 0;
const int VISITED     = 1;

const int GENDER_1 = 0;
const int GENDER_2 = 1;

// Find an odd cycle
void define_genders(int v, int parent = -1) {
    state[v] = PROCESSING;
    for(int u: edges[v]) {
        if (state[u] == NOT_VISITED) {
            gender[u] = gender[v] == GENDER_2 ? GENDER_1 : GENDER_2;
            define_genders(u, v);
        }
    }
    state[v] = VISITED;
}

void dfs(int v, int parent = -1) {
    state[v] = PROCESSING;
    for(int u: edges[v]) {
        if (u != parent and gender[u] == gender[v]) suspect = true;
        if (state[u] == NOT_VISITED) {
            dfs(u, v);
        }
    }
    state[v] = VISITED;
}

void analizeBugs() {
    // O(n + m)
    for(int i = 1; i < n+1; i++) {
        if(state[i] == NOT_VISITED) {
            gender[i] = GENDER_1;
            define_genders(i);
        }
    }

    state = vector<int>(n+1, NOT_VISITED);

    // O(n+m)
    for (int i = 1; i < n+1; i++) {
        if(state[i] = NOT_VISITED) {
            dfs(i);
        }
    }
}

int main() {
    int c; cin >> c;
    int totalScenarios = c + 1;

    string suspicious     = "Suspicious bugs found!";
    string not_suspicious = "No suspicious bugs found!";

    while(c--) {
        cin >> n >> m;
        int i     = 0;
        suspect   = false;

        edges     = vector<vector<int> >(n+1,vector<int>(0));
        gender    = vector<int>(n+1, -1);
        state     = vector<int>(n+1, NOT_VISITED);

        while(i < m) {
            int u, v; cin >> u >> v;
            edges[u].push_back(v);
            edges[v].push_back(u);
            i++;
        }

        analizeBugs();
        
        string anwser = suspect ? suspicious : not_suspicious;

        cout << "Scenario #" << totalScenarios - (c+1) << ":" << endl;
        cout << anwser << endl;
    }
}