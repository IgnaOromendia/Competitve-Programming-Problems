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

    // Ordeno segun el día en el que empiezan
    sort(projects.begin(), projects.end(), [](Project const &lhs, Project const &rhs){
        return lhs.starting_day < rhs.starting_day;
    });

    forn(i, 0, n) 
        start_times[i] = projects[i].starting_day;
    
    // Memo que representa la máxima cantidad de dinero ganado hasta el i-esimo
    vector<ll> memo(n + 1, 0);  
    
    // Enfoque bottom up
    forn(i, 0, n) {
        // Comparamos el máximo dinero ganado hasta ahora con el valor actual contando el próximo proyecto
        memo[i + 1] = max(memo[i + 1], memo[i]);
        
        // Buscamos el próximo proyecto en log n
        int next_project = lower_bound(start_times.begin(), start_times.end(), projects[i].ending_day+1) - start_times.begin();

        // Comparamos el máximo dinero ganado hasta ahora + elegir este proyecto contra el valor actual contando el próximo proyecto
        memo[next_project] = max(memo[next_project], memo[i] + projects[i].reward);
    }

    cout << memo[n] << endl;
}
