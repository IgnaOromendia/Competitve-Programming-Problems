#include<iostream>
#include<vector>

using namespace std;

const unsigned int INF = 1e7;

int n,x;
vector<int> pages;
vector<int> price;
vector<vector<int> > memo;

void max_pages() {
    for(int book = 1; book <= n; book++) {
        for(int budget = 0; budget <= x; budget++) {
            
            // skipping 
            memo[book][budget] = memo[book - 1][budget];  

            // buying
            if(budget >= price[book - 1]) { 
                memo[book][budget] = max(memo[book][budget], memo[book - 1][budget - price[book - 1]] + pages[book - 1]);
            }
        }        
    }
    
    cout << memo[n][x] << endl;
}

int main() {
    cin >> n >> x;

    pages.assign(n,0);
    price.assign(n,0);
    memo.assign(n+1, vector<int>(x+1,0));

    for(int i = 0; i < n; i++) cin >> price[i];
    for(int i = 0; i < n; i++) cin >> pages[i];

    max_pages();
}