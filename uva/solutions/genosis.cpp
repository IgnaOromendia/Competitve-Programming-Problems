#include<iostream>
#include<vector>

// https://vjudge.net/problem/UVA-13211

using namespace std;

size_t min_power_needed_with_order(vector<vector<int> >& defense_network, vector<int>& order) {
    int n = defense_network.size();

    size_t sum=0;
    // Going in the reverse order
    for (int k=n-1;k>=0;k--) {
        int z = order[k];

        // Minimum power tower crossing z or not
        for(int i=0;i<n;i++) 
            for (int j=0;j<n;j++) 
                if(i!=j && j!=z && i!=z)
                    defense_network[i][j] = min(defense_network[i][j],defense_network[i][z] + defense_network[z][j]);

        // Sum of remaining towers
        size_t local_sum = 0;
        for(int i = k; i < n; i++)
            for(int j = k; j < n; j++)
                local_sum += defense_network[order[i]][order[j]];

        sum += local_sum;
    }

    return sum;
}


int main() {
    int t;cin >> t;
    while(t--) {
        int number_of_towers; cin >> number_of_towers;

        vector<vector<int> > defense_network(number_of_towers, vector<int>(number_of_towers, 0));
        vector<int> destroy_order(number_of_towers,0);

        for(int i = 0; i < number_of_towers; i++)
            for(int j = 0; j < number_of_towers; j++)
                cin >> defense_network[i][j];

        for(int i = 0; i < number_of_towers; i++) cin >> destroy_order[i];

        cout << min_power_needed_with_order(defense_network, destroy_order) << endl;

    }
}