// https://vjudge.net/problem/UVA-11790
#include<vector>
#include<iostream>
#include<algorithm>
#include<string>

using namespace std;
using trends = pair<int, int>;

const int INF = 1e9;
const string increasing = "Increasing";
const string decreasing = "Decreasing";

struct Building {
    int height;
    int width;

    Building(int h ,int w) {height = h; width = w;}
};

int total_buildings = 0;
vector<Building> buildings;
vector<int> memo_inc;
vector<int> memo_dec;

trends calculate_trend() {
    int max_inc = 0;
	int max_dec = 0;

	for(int i = 0; i < total_buildings; ++i) {
        int current_width =  buildings[i].width;
        int current_heigth =  buildings[i].height;

        memo_inc[i] = current_width;
        memo_dec[i] = current_width;

        for(int j = 0; j < i; ++j){
            int old_height = buildings[j].height;
            if(old_height < current_heigth)
                memo_inc[i] = max(memo_inc[i], memo_inc[j] + current_width);
            if(current_heigth < old_height)
                memo_dec[i] = max(memo_dec[i], memo_dec[j] + current_width);
        }

        max_inc = max(max_inc, memo_inc[i]);
        max_dec = max(max_dec, memo_dec[i]);
    }

    return make_pair(max_inc, max_dec);
}

void print_case(int case_number, int inc, int dec) {
    cout << "Case " << case_number << ". "  ;
    if (inc >=  dec) cout << increasing << " (" << inc << "). " << decreasing << " (" << dec << ")." << endl;
    else cout << decreasing << " (" << dec << "). " << increasing << " (" << inc << ")." << endl;
}

int main() {
    int c; cin >> c;
    for(int t = 1; t <= c; t++) {
        
        cin >> total_buildings;

        memo_dec.assign(total_buildings, 0);
        memo_inc.assign(total_buildings, 0);

        vector<int> heights(total_buildings, 0);

        for(int i = 0; i < total_buildings; i++) cin >> heights[i];

        for(int i = 0; i < total_buildings; i++) {
            int w; cin >> w;
            buildings.push_back(Building(heights[i],w));
        }

        trends building_trends = calculate_trend();

        print_case(t, building_trends.first, building_trends.second);

        buildings.clear();
    }

}
