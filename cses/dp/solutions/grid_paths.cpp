#include<iostream>
#include<vector>

using namespace std;

const unsigned int M = 1000000007;
const char EMPTY = '.';
const char TRAP = '*';

int n;
vector<vector<int> > memo;
vector<vector<char> > grid;

int paths(int i, int j) {
    if (grid[i][j] == TRAP) return 0;
    if (i == n - 1 and j == n - 1) return 1;

    if (memo[i][j] == -1) {
        int right = 0, down = 0;
        if (i + 1 < n) down = paths(i + 1, j);
        if (j + 1 < n) right = paths(i, j + 1);
        memo[i][j] = (right + down) % M;
    }

    return memo[i][j];
}

int main() {
    cin >> n;

    memo.assign(n, vector<int>(n,-1));
    grid.assign(n, vector<char>(n,'a'));

    for(int i = 0; i < n; i++) 
        for(int j = 0; j < n; j++) 
            cin >> grid[i][j];
    
    cout << paths(0,0) << endl;
}
