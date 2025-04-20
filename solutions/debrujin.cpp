#include<vector>
#include<iostream>
#include<math.h>
#include<unordered_set>

using namespace std;

unordered_set<string> visited;
vector<int> edges;
string A = "01";

// Modified DFS in which no edge
// is traversed twice
void dfs(string node){
	for (int i = 0; i < 2; ++i) {
		string str = node + A[i];
		if (visited.find(str) == visited.end()) {
			visited.insert(str);
			dfs(str.substr(1));
			edges.push_back(i);
		}
	}
}

// Function to find a de Bruijn sequence
// of order n on k characters
string deBruijn(int n){
	string startingNode = string(n - 1, A[0]);
	dfs(startingNode);

	string S;

	// Number of edges
	int l = pow(2, n);
	for (int i = 0; i < l; ++i)
		S += A[edges[i]];
	S += startingNode;

	return S;
}

int main() {
	int n; cin >> n;

	cout << deBruijn(n) << endl;
}
