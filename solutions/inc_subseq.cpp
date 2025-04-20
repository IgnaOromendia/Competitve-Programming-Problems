#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > mat;
typedef pair<int,int> pi;

#define pb push_back
#define mp make_pair

#define forn(i,a,b) for (int i = a; i < b; i++)

const int INF  = 1e9;
const int MAXN = 0;
const int mod  = 1000000007;


int longest_increasing_subseq(vector<int>& nums, int n) {
    vector<int> ans;
    ans.push_back(nums[0]);

    for (int i = 1; i < n; i++) {
        if (nums[i] > ans.back()) {
            // Encontramos una secuencia más larga
            ans.push_back(nums[i]);
        } else {
            // Insertamos el nuevo elemento en la posición tal que se mantenga ordenado
            int low = lower_bound(ans.begin(), ans.end(), nums[i]) - ans.begin();
            ans[low] = nums[i];
        }
    }

    return ans.size();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int n; cin >> n;

    vi numbers(n);

    forn(i,0,n) cin >> numbers[i];

    cout << longest_increasing_subseq(numbers, n) << endl;
}