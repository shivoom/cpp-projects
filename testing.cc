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
   vector<int> cardnums {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
   vector<string> suits {"Clubs", "Spades", "Diamonds", "Hearts"};
   vector<tuple<int, string>> deck {};
   //creating the deck
   for (int i {0}; i < suits.size(); i++){
      for (int j {0}; j < cardnums.size(); j++){ 
         deck.push_back(make_tuple(cardnums.at(j), suits.at(i)));
      }
   }
   cout << deck.size();
   for (int i {0}; i < deck.size(); i++){
      tuple<int, string> card {deck.at(i)};
      cout << get<0>(card) << ", " << get<1>(card) << endl;
   }


   //shuffle deck
   //shuffle(deck.begin(), deck.end(), gen);
   return deck;
}
int main () {
   randdeck();
}