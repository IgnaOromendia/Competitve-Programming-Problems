#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <math.h>
#include <map>
#include <queue>
#include <sstream>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int> > mat;
typedef pair<int,int> pi;

#define pb push_back
#define mp make_pair

#define forn(i,from,to) for (int i = from; i < to; i++)

const int INF  = 1e9;
const int MAXN = 0;
const int mod  = 1e9 + 7;
const double PI = 3.14159265359;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    string text; 
    int i;
    while (cin >> text) {
        cin.ignore(INF, '\n');
        if (text == "ENDOFINPUT") break;
        getline(cin, text, '\n');
        
        for (i = 0; i < text.length(); i++) // the rule creating plain text
            if (isalpha(text[i]))
                text[i] = 'A' + (text[i] - 'A' + 21) % 26;
            
        cout << text << endl; // Output the original message by Caesar
        cin >> text; //Next Caesar's message
    }
}