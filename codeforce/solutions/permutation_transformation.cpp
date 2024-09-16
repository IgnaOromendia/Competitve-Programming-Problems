#include<iostream>
#include<vector>

using namespace std;

int maxVecIndex(vector<int>& v, int i, int j) {
    int max = i;
    for (int k = i+1; k < j; k++) 
        if (v[k] > v[max]) max = k;
    return max;
}

void transform(vector<int>& seq, vector<int>& depth, int i, int j, int d) {
    if (i == j) return;

    int m = maxVecIndex(seq, i, j);

    if(depth[m] == -1) depth[m] = d;

    transform(seq, depth, i, m, d+1);
    transform(seq, depth, m+1, j, d+1);
}


int main() {
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;

        vector<int> seq(n);
        vector<int> depth(n,-1);

        for (int i = 0; i < n; i++) cin >> seq[i];

        transform(seq, depth, 0, n, 0);

        for (int i = 0; i < n; i++) cout << depth[i] << " ";
        cout << endl;
    }
}