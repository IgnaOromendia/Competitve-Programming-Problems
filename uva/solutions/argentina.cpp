#include<vector>
#include<iostream>
#include<algorithm>
#include<string>

using namespace std;

const int INF = 1e9;
const int max_players = 10;
const int max_attackers = 5;

struct Player {
    string name;
    int attack;
    int defense;

    Player(string player_name, int atk, int def) {
        name = player_name;
        attack = atk;
        defense = def;
    }

    bool operator <(const Player& other_player) const{
        return name < other_player.name;
    }
};

struct Selection_data {
    int attack;
    int defense;
    int amount_attackers;
    vector<bool> players;

    Selection_data() {
        amount_attackers = 0;
        attack = 0;
        defense = 0;
        players.assign(max_players, false);
    };

    void add_attacker(int atk) {
        attack += atk;
        amount_attackers++;
    }

    void add_defender(int def) {
        defense += def;
    }

    void assign_player(int index) {
        players[index] = true;
    }

    void deassign_player(int index) {
        players[index] = false;
    }

    void remove_attacker(int atk) {
        attack -= atk;
        amount_attackers--;
    }

     void remove_defender(int def) {
        defense -= def;
    }

    bool operator==(const Selection_data& other_data) const {
        return attack == other_data.attack and defense == other_data.defense;
    }

    bool operator>(const Selection_data& other_data) const {
        if (other_data.attack == attack) return defense > other_data.defense;
        return attack > other_data.attack;
    }

};

void print_players(vector<string> &players) {
    int last_index = players.size() - 1;
    cout << "(";
    for(int i = 0; i < last_index; i++) cout << players[i] << ", ";
    if (last_index >= 0) cout << players[last_index];
    cout << ")" << endl;
}

void max_team_ability(int player_index, vector<Player>& players, Selection_data& actual_selection, Selection_data& optimal_selection) {
    if (player_index == max_players) {
        if (actual_selection > optimal_selection) {
            optimal_selection = actual_selection;
        }
    } else {
        // Add attackers
        if (actual_selection.amount_attackers < max_attackers) {
            actual_selection.add_attacker(players[player_index].attack);
            actual_selection.assign_player(player_index);
            max_team_ability(player_index+1, players, actual_selection, optimal_selection);
            actual_selection.remove_attacker(players[player_index].attack);
        }
        // Add defender 
        if ((player_index - actual_selection.amount_attackers) < max_attackers) {
            actual_selection.deassign_player(player_index);
            actual_selection.add_defender(players[player_index].defense);
            max_team_ability(player_index+1, players, actual_selection, optimal_selection);
            actual_selection.remove_defender(players[player_index].defense);
        }
    }
}

int main() {

    int t; cin >> t;
    int c = 1;
    while(c <= t) {
        
        vector<Player> players;

        for(int i = 0; i < 10; i++) {
            string name;
            int atk, def;
            cin >> name >> atk >> def;
            players.push_back(Player(name, atk, def));
        }

        sort(players.begin(), players.end());

        Selection_data optimal_selection = Selection_data();
        Selection_data actual_selection = Selection_data();

        max_team_ability(0, players, actual_selection, optimal_selection);

        vector<string> attackers, defenders;

        for(int i = 0; i < max_players; i++) {
            if (optimal_selection.players[i]) attackers.push_back(players[i].name);
            else defenders.push_back(players[i].name);
        }

        cout << "Case " << c << ":" << endl;
        print_players(attackers);
        print_players(defenders);

        c++;
    }

    
}