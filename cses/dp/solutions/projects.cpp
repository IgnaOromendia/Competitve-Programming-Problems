#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<int> vi;

#define forn(i,a,b) for (int i = a; i < b; i++)

struct Project {
    int starting_day, ending_day, reward;
    Project(int s, int e, int r): starting_day(s), ending_day(e), reward(r) {}
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int n;cin >> n;
    vector<Project> projects;
    projects.reserve(n); 
    vi start_times(n);

    forn(i, 0, n) {
        int a, b, p; cin >> a >> b >> p;
        projects.emplace_back(a, b, p);
    }

    sort(projects.begin(), projects.end(), [](Project const &lhs, Project const &rhs){
        return lhs.starting_day < rhs.starting_day;
    });

    forn(i, 0, n) {
        start_times[i] = projects[i].starting_day;
        // cout << start_times[i] << " ";
    }
    
    // cout << endl;

    vector<ll> memo(n + 1, 0);  
    
    forn(i, 0, n) {
        memo[i + 1] = max(memo[i + 1], memo[i]);
        
        int next_project = lower_bound(start_times.begin(), start_times.end(), projects[i].ending_day+1) - start_times.begin();
        // int next_project = i + 1;
        // while (next_project < n && projects[next_project].starting_day <= projects[i].ending_day) {
        //     ++next_project;
        // }

        // cout << next_project2 << " " << next_project << endl;

        memo[next_project] = max(memo[next_project], memo[i] + projects[i].reward);
    }

    cout << memo[n] << endl;
}
