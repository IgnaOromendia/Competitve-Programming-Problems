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

string day_names[7] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

bool is_leap_year(int year) {
	return (year % 100 != 0 and year % 4 == 0) or year % 400 == 0;
}

int days_of_year(int year) {
	return is_leap_year(year) ? 366 : 365;
}

int days_of_month(int month, int year) {
	if (month == 2) 
		return is_leap_year(year) ? 29 : 28;

	if (month == 1 or month == 3 or month == 5 or month == 7 or month == 8 or month == 10 or month == 12)
		return 31;

	return 30;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);

    int day; cin >> day;

    while (day != -1) {
        int year = 2000;
        int month = 1;
        string day_name = day_names[day % 7];

        while(day >= days_of_year(year)) 
            day -= days_of_year(year++);
        
        while(day >= days_of_month(month, year)) 
            day -= days_of_month(month++, year);
        

        day++;

        cout << year << (month < 10 ? "-0" : "-") << month << (day < 10 ? "-0" : "-") << day  << " " << day_name << endl;

        cin >> day;
    }

    
}