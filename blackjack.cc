#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <tuple>
using namespace std;


vector<tuple<int, string>> randdeck() {
  // generating random numbers and defining cards/suits
  random_device rd;
  mt19937 gen(rd());
  vector<int> cardnums{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
  vector<string> suits{"Clubs", "Spades", "Diamonds", "Hearts"};
  vector<tuple<int, string>> deck{};
  // creating the deck
  for (int i{0}; i < suits.size(); i++) {
    for (int j{0}; j < cardnums.size(); j++) {
      deck.push_back(make_tuple(cardnums.at(j), suits.at(i)));
    }
  }
  // shuffle deck
  shuffle(deck.begin(), deck.end(), gen);
  return deck;
}
void cardnames(vector<tuple<int, string>> userhand, vector<tuple<int, string>> syshand) {
  //checks for number value then translates to card name
  for (int i{0}; i < userhand.size(); i++) {
    tuple<int, string> card{userhand.at(i)};
    if (get<0>(card) == 11) {
      cout << "You have a Jack of " << get<1>(card) << endl;
    } else if (get<0>(card) == 12) {
      cout << "You have a Queen of " << get<1>(card) << endl;
    } else if (get<0>(card) == 13) {
      cout << "You have a King of " << get<1>(card) << endl;
    } else if (get<0>(card) == 1) {
      cout << "You have a Ace of " << get<1>(card) << endl;
    } else {
      cout << "You have a " << get<0>(card) << " of " << get<1>(card) << endl;
    }
  }
  //same process with system cards, but not revealing its second card
  for (int i{0}; i < syshand.size() - 1; i++) {
    tuple<int, string> card{syshand.at(i)};
    if (get<0>(card) == 11) {
      cout << "The dealer has a Jack of " << get<1>(card) << endl;
    } else if (get<0>(card) == 12) {
      cout << "The dealer has a Queen of " << get<1>(card) << endl;
    } else if (get<0>(card) == 13) {
      cout << "The dealer has a King of " << get<1>(card) << endl;
    } else if (get<0>(card) == 1) {
      cout << "The dealer has a Ace of " << get<1>(card) << endl;
    } else {
      cout << "The dealer has a " << get<0>(card) << " of " << get<1>(card) << endl;
    }
    cout << "The dealer has one unknown card" << endl;
  }
}
int totalhand(vector<tuple<int, string>> hand) {
  vector<int> cards {};
  int total {};
  bool ace {false};
  //sorts through each number in hand
  for (int i {0}; i < hand.size(); i++){
    tuple<int, string> card {hand.at(i)};
    if (get<0>(card) > 10){
      cards.push_back(10);
    } else if (get<0>(card) <= 10 && get<0>(card) > 1){
      cards.push_back(get<0>(card));
    } else if (get<0>(card) == 1){
      ace = true;
    }
  }
  //if there is an ace, need to check if value should be 1 or 11
  if (ace == true){
    for (int i {0}; i < cards.size(); i++){
      total += cards.at(i);
    }
    if (11 + total <= 21){
      cards.push_back(11);
    } else {
      cards.push_back(1);
    }
  }
  //sets total back to zero before recalculating
  total = 0;
  for (int i {0}; i < cards.size(); i++){
    total += cards.at(i);
    cout << cards.at(i) << endl;
  }
  cout << total << endl;
  return total;
}
void dealing(vector<tuple<int, string>> deck) {
  vector<tuple<int, string>> userhand{};
  vector<tuple<int, string>> syshand{};
  //picks first 2 cards from the shuffled deck for the user's hand
  for (int i{0}; i < 2; i++) {
    tuple<int, string> usercard{deck.at(i)};
    userhand.push_back(make_tuple(get<0>(usercard), get<1>(usercard)));
    cout << get<0>(usercard) << " " << get<1>(usercard) << endl;
  }
  //next 2 cards for the system's hand
  for (int i{2}; i < 4; i++) {
    tuple<int, string> syscard{deck.at(i)};
    syshand.push_back(make_tuple(get<0>(syscard), get<1>(syscard)));
    cout << get<0>(syscard) << " " << get<1>(syscard) << endl;
  }
  cardnames(userhand, syshand);
  totalhand(userhand);
  totalhand(syshand);
}



int main() {
  vector<tuple<int, string>> deck {randdeck()};
  dealing(deck);
}
