#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, k;
vector<int> stalls;

bool possible_position(int mid) {
    int count = 1;
    int selected_stall = stalls[0];

    for(int i = 1; i < n; i++) {
        if(stalls[i] - selected_stall >= mid) {
            selected_stall = stalls[i];
            count++;
        }
        if (count == k) return true;
    }

    return false;
}

int distance() {
    sort(stalls.begin(), stalls.end()); // O(n log n)
    int max_diff = stalls[n-1] - stalls[0];
    int result = 1;
    int min_diff = 1;
    int mid;

    //  Binary search with validation O(n log n)
    while(min_diff <= max_diff) {
        mid = (max_diff + min_diff) / 2;
        if (possible_position(mid)) { // O(n)
            min_diff = mid + 1;
            result = max(result, mid);
        } else {
            max_diff = mid - 1;
        }
    }
    
    return result;
}

int main() {
    int c; cin >> c;
    while(c--) {
        cin >> n >> k;
        int copyN = n;
        while(copyN--) {
            int i;cin >> i;
            stalls.push_back(i);
        }

        cout << distance() << endl;
        stalls.clear();
    }
}