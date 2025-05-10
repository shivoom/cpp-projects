#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <tuple>
using namespace std;

vector<tuple<int, string>> randdeck() {
    //generating random numbers and defining cards/suits
    random_device rd;
    mt19937 gen(rd());
    vector<int> cardnums {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    vector<string> suits {"Clubs", "Spades", "Diamonds", "Hearts"};
    vector<tuple<int, string>> deck {};
    //creating the deck
    for (int i {0}; i < suits.size(); i++){
        for (int j {0}; j < cardnums.size(); j++){ 
            deck.push_back(make_tuple(cardnums.at(j), suits.at(i)));
        }
    }
    //shuffle deck
    shuffle(deck.begin(), deck.end(), gen);
    return deck;
}
pair<vector<tuple<int,string>>, vector<tuple<int,string>>> dealing () {
    vector<tuple<int, string>> deck {randdeck()};
    vector<tuple<int, string>> userhand {};
    vector<tuple<int, string>> syshand {};
    for (int i {0}; i < 2; i++){
        tuple<int, string> usercard {deck.at(i)};
        userhand.push_back(make_tuple(get<0>(usercard), get<1>(usercard)));
    }
    for (int i {0}; i < userhand.size(); i++) {
      tuple<int, string> card {userhand.at(i)};
      cout << get<0>(card) << " of " << get<1>(card) << endl;
    }
    for (int i {2}; i < 4; i++){
        tuple<int, string> syscard {deck.at(i)};
        syshand.push_back(make_tuple(get<0>(syscard), get<1>(syscard)));
    }
    for (int i {0}; i < syshand.size(); i++) {
      tuple<int, string> card {syshand.at(i)};
      cout << get<0>(card) << " of " << get<1>(card) << endl;
    }
    return make_pair(userhand, syshand);
}
void cardnames () {
    
}
int main () {
    dealing();
    
}
   