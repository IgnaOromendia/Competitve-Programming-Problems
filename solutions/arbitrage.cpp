#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <math.h>
#include <map>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > mat;
typedef pair<int,int> pi;

#define pb push_back
#define mp make_pair

#define forn(i,from,to) for (int i = from; i < to; i++)

const int INF  = 1e9;
const int MAXN = 31;
const int mod  = 1e9 + 7;
const float PI = 3.14159265359;

map<string,int> coinToNode;
double dist[MAXN][MAXN];

bool profit_exchange(int n) {
	forn(i,0,n)
		forn(j,0,n)
			if (dist[i][j] * dist[j][i] > 1) 
				return true;
	return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int n; cin >> n;
    int tcount = 1;

    while(n) {
        memset(dist, 0, sizeof(dist));

        forn(i,0,n) {
            string coin; cin >> coin;
            coinToNode.insert(mp(coin,i));
        }

        int m; cin >> m;

        forn(i,0,m) {
            string v,u; 
            double c;
            cin >> v >> c >> u;
            dist[coinToNode[v]][coinToNode[u]] = c;
        }

        forn(k,0,n)
            forn(i,0,n)
                forn(j,0,n)
                    if (i != k and j != k and i != j)
                        if(dist[i][k] * dist[k][j] > dist[i][j])
                            dist[i][j] = dist[i][k] * dist[k][j];

        
        cout << "Case " << tcount << ": " << (profit_exchange(n) ? "Yes" : "No") << endl;
        
        tcount++;
        cin >> n;

    }

}