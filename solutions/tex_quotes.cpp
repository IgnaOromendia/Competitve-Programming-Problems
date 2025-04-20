#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <math.h>

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
const float PI = 3.14159265359;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    string text;
    bool openning_bracket = true;

    string closing_bracket = "'";

    while(getline(cin, text)) {

        forn(c,0,text.length())
            if(text[c] == '"') {
                text[c] = openning_bracket ? '`' : '\'';
                text.insert(c+1, openning_bracket ? "`" : "'");
                openning_bracket = !openning_bracket;
            }
                
        cout << text << endl;

    }
}

/*
``To be or not to be,'' quoth the Bard, ``that
is the question''.
The programming contestant replied: ``I must disagree.
To `C' or not to `C', that is The Question!''

*/