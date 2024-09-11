#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n; cin >> n;
    vector<int> pages(n);

    for(int i = 0; i < n; i++) {
        int u; cin >> u;
        pages[i] = u-1;
    }

    int days = 0, i = 0, next = 0;
    while(i < pages.size()) {
        next = max(next, pages[i]);
        if(i == next) days ++;
        i++;
    }

    cout << days << endl;

}