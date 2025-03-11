#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <math.h>
#include <iomanip> 

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > mat;
typedef pair<int,int> pi;

#define pb push_back
#define mp make_pair

#define forn(i,from,to) for (int i = from; i < to; i++)

const int INF  = 1e9;
const int MAXN = 201;
const int mod  = 1e9 + 7;
const float PI = 3.14159265359;

double dist[MAXN][MAXN];
int con[MAXN][MAXN];

void connect_paths(double eps, int n) {
    memset(con, 0, sizeof(con));

    forn(i,0,n)
        forn(j,0,n)
            con[i][j] = dist[i][j] <= eps;

    forn(k,0,n)
        forn(i,0,n)
            forn(j,0,n)
                con[i][j] |= con[i][k] & con[k][j];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int t; cin >> t;
    int tcount = 1;

    while(t) {
        memset(dist, 0, sizeof(dist));

        int xcoord[t];
        int ycoord[t];

        forn(i,0,t) 
            cin >> xcoord[i] >> ycoord[i];

        forn(i,0,t)
            forn(j,i+1,t) 
                dist[i][j] = dist[j][i] = sqrt(pow(xcoord[i] - xcoord[j], 2) + pow(ycoord[i] - ycoord[j], 2));
            
        double l = 0, r = 1e5;

        while(r-l > 1e-7) {
            double k = (l+r) / 2;

            connect_paths(k, t); 
            
            if(con[0][1]) 
                r = k;
            else
                l = k;
        }

        cout << "Scenario #" << tcount << endl;
        cout << "Frog Distance = " << fixed << setprecision(3) << r << "\n\n";
        
        tcount++;
        cin >> t;

    }

    

}