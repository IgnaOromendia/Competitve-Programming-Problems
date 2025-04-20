#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <math.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > mat;
typedef pair<int,int> pi;

#define pb push_back
#define mp make_pair

#define forn(i,from,to) for (int i = from; i < to; i++)

const int INF  = 1e9;
const int MAXN = 11000;
const int mod  = 1e9 + 7;
const float PI = 3.14159265359;

struct node {
    int k, step; // current prime number k, the length of the path (the number of changed digits ) step
};

node q[100000];
int primes[MAXN];
int dist[MAXN];

void init_prime_graph(int n) {
    memset(primes, 0, sizeof(primes));
    primes[0]=1;
    primes[1]=1;
    forn(i,2,n+1) 
        if (!primes[i]) for (int j=i*i; j<=n; j+=i) primes[j]=1;
}

int modify_digit(int x, int i, int j){ // change the i-th digit of x into j
    if (i==1) return (x/10)*10+j; else
    if (i==2) return (x/100)*100+x%10+j*10; else
    if (i==3) return (x/1000)*1000+x%100+j*100;
    return (x%1000)+j*1000;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    init_prime_graph(9999); 
    
    int t; cin >> t;
    while (t--){
        int x,y; cin >> x >> y; 

        q[1].k=x; 
        q[1].step=0;

        int l=1,r=1; // Initialize pointers of the queue

        memset(dist, 100, sizeof(dist)); 

        int ans = -1; // Initialize the minimal cost

        while (1){
            if (q[l].k==y) { // goal prime y is gotten
                ans = q[l].step;
                break;
            }
            int tk,ts;
            for (int i=1; i<=4; i++) // every digit of the front for the queue is changed
                for (int j=0; j<=9; j++) 
                    if (!((j==0)&&(i==4))){
                        tk = modify_digit(q[l].k, i, j);

                        if (primes[tk]) continue; // If tk isn’t a prime

                        ts=q[l].step+1; // the length of the path to tk
                        if (ts>=dist[tk]) continue;

                        if (tk==y){ // If tk is the goal prime
                            ans = ts;
                            break;
                        }
                        
                        dist[tk] = ts; // the length of the path to tk
                        r++;
                        q[r].k = tk; // Prime tk and its length of the path is pushed
                        q[r].step = ts;
                    }
                
            if (l==r||ans>=0) break; // If the queue is empty or the goal prime is arrived
            
            l++;
        }

        if (ans>=0) cout<<ans<<endl; else cout<<"Impossible"<<endl; // Output the result
    }
}

