#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, k;
vector<int> stalls;

bool possible_position(int mid) {
    int count = 1;
    int selected_stall = stalls[0];

    // Compararmos las distancias entre establos para que sea mayor a mid
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

    //  Busqueda binaria en la distancia maxima que tienen que cumplir los establos
    while(min_diff <= max_diff) {
        mid = (max_diff + min_diff) / 2;
        // Chequeo de posiciones
        if (possible_position(mid)) {
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