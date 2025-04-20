#include<iostream>

using namespace std;

// ### INSPIRED IN USACO solution ###

const int max_planets = 2e5 + 5;
const int max_jump = 30; // log2(10^9)
 
int n, q;
int parent[max_planets][max_jump];
// parent[i][j] represents i's (2^j)th parent

int travel(int x, int k) {
    for(int p = 0; p < max_jump; p++) 
        if(k & (1 << p)) x = parent[x][p]; // k bit-and 2^p 
    return x;
}
 
int main() {
    ios_base::sync_with_stdio(false);

    cin >> n >> q;
 
    for(int i = 1; i <= n; i++) cin >> parent[i][0];

    for(int planet = 1; planet < max_jump; planet++)
        for(int root = 1; root <= n; root++)
            parent[root][planet] = parent[parent[root][planet - 1]][planet - 1];
 
    while(q--) {
        int x, k; cin >> x >> k;
        cout << travel(x,k) << endl;
    }
}