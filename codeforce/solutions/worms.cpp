#include<iostream>
#include<vector>

using namespace std;

int searchLabel(vector<pair<int,int> >& labels, int j, int n) {
    int low = 0;
    int high = n-1;

    while(labels[low].first <= j and j <= labels[high].second) {
        int mid = (high + low) / 2;

        if (labels[mid].first <= j and j <= labels[mid].second) return mid + 1;

        if (labels[mid].first > j) {
            high = mid;
        } else {
            if ((mid + high) / 2 == mid) 
                low = mid+1;
            else 
                low = mid;
        }
    }
    return -1;
}


int main() {
    int n, w; cin >> n;

    vector<pair<int, int> > labels(n);

    int a2; cin >> a2;
    labels[0] = make_pair(1,a2);

    for (int i = 1; i < n; i++) {
        cin >> a2;
        int a1 = labels[i-1].second;
        labels[i] = make_pair(a1 + 1, a1 + a2);
    }
        
    cin >> w;

    for (int i = 0; i < w; i++) {
        int j; cin >> j;
        cout << searchLabel(labels, j, n) << endl;
    }


}