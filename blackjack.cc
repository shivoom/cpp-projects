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
    //cout << cards.at(i) << endl;
  }
  return total;
}
vector<tuple<int, string>> hit (vector<tuple<int, string>> hand, vector<tuple<int, string>> deck, int cardnum) {
  bool bust {false};
  //add new card into the hand from the deck using the cardnum to index through the deck to avoid repeats
  tuple<int, string> card{deck.at(cardnum)};
  hand.push_back(make_tuple(get<0>(card), get<1>(card)));
  //printing the name of the card drawn
  if (get<0>(card) <= 10 && get<0>(card) != 1){
    cout << get<0>(card) << " of " << get<1>(card) << endl;
  } else if (get<0>(card) > 10){
    if (get<0>(card) = 11){
      cout << "Jack of " << get<1>(card) << endl;
    } else if (get<0>(card) = 12){
      cout << "Queen of " << get<1>(card) << endl;
    } else {
      cout << "King of " << get<1>(card) << endl;
    }
  } else {
    cout << "Ace of " << get<1>(card) << endl;
  }
  if (totalhand(hand) > 21){
    bust = true;
    cout << "You busted" << endl;
  }
  cardnum++;
  return hand;
}
bool bust (vector<tuple<int, string>> hand){
  bool bust {false};
  if (totalhand(hand) > 21){
    return bust;
  } else {
    return !bust;
  }
}
char input () {
  char choice {};
  cout << "hit or stand (h,s): ";
  cin >> choice;
  choice = toupper(choice);
  if (choice == 'H' || choice == 'S'){
    return choice;
  } else {
    //if input doesnt match an option
    return 'N';
  }
}
vector<tuple<int, string>> dealerhit (vector<tuple<int, string>> hand, vector<tuple<int, string>> deck, int cardnum){
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dis(1,10);
  int chance {dis(gen)};
  bool stand {false};
  //while loop with the logic behind if the dealer hits or stands
  do {
    cout << "Dealer hits: ";
    if (totalhand(hand) == 21){
      //stand
      stand = true;
      //cout << "21 stand" << endl;
    } else if (totalhand(hand) <= 10){
      //always hitting when the total hand is less than 10
      hand = hit(hand, deck, cardnum);
      //cout << "greater than 10 hit" << endl;
    } else if (totalhand(hand) > 10 && totalhand(hand) < 14){
      if(chance >= 1 && chance <= 7){
        //70% chance to hit if hand is between 11 and 13
        hand = hit(hand, deck, cardnum);
        //cout << "greater than 10 less that 14 hit" << endl;
      } else {
        //stand
        stand = true;
        //cout << "greater than 10 less that 14 stand" << endl;
      }
    } else if (totalhand(hand) > 13 && totalhand(hand) < 17){
      if(chance >= 1 && chance <= 5){
        //50% chance to hit if hand is between 14 and 16
        hand = hit(hand, deck, cardnum);
        //cout << "greater than 13 less than 17 hit" << endl;
      } else {
        //stand
        stand = true;
        //cout << "greater than 13 less than 17 stand" << endl;
      }
    } else if (totalhand(hand) > 16 && totalhand(hand) < 20){
      if(chance >= 1 && chance <= 3){
        //30% chance to hit if hand is between 17 and 19
        hand = hit(hand, deck, cardnum);
        //cout << "greater than 16 less than 20 hit" << endl;
      } else {
        //cout << "greater than 16 less than 20 stand" << endl;
        //stand
        stand = true;
      }
    } else {
      //always stand if hand greater than 19
      cout << "Dealer stands" << endl;
      //stand
      stand = true;
    }
    cardnum++;
  } while (!stand);
  return hand;
}

void stand (vector<tuple<int, string>> userhand, vector<tuple<int, string>> syshand) {
  
}

void dealing(vector<tuple<int, string>> deck) {
  vector<tuple<int, string>> userhand{};
  vector<tuple<int, string>> syshand{};
  //picks first 2 cards from the shuffled deck for the user's hand
  for (int i{0}; i < 2; i++) {
    tuple<int, string> usercard{deck.at(i)};
    userhand.push_back(make_tuple(get<0>(usercard), get<1>(usercard)));
    //cout << get<0>(usercard) << " " << get<1>(usercard) << endl;
  }
  //next 2 cards for the system's hand
  for (int i{2}; i < 4; i++) {
    tuple<int, string> syscard{deck.at(i)};
    syshand.push_back(make_tuple(get<0>(syscard), get<1>(syscard)));
    //cout << get<0>(syscard) << " " << get<1>(syscard) << endl;
  }
  cout << "here are the cards: " << endl;
  cardnames(userhand, syshand);
  cout << "the total amount of your cards: " << totalhand(userhand) << endl;
  //cout << "the total amount of the dealer's cards: " << totalhand(syshand) << endl;  
  int hitnum{4};
  bool stand {false};
  do {
    char choice {input()};
    if (choice == 'H'){
      userhand = hit(userhand, deck, hitnum);
      cout << "Your hand: " << totalhand(userhand) << endl;
      hitnum++;
    } else if (choice == 'S'){
      syshand = dealerhit(syshand, deck, hitnum);
      stand = true;      
    } else if (choice == 'N'){
      cout << "invalid input, ";
    }
  } while((bust(userhand) && bust(syshand)) && !stand);
  
  if (!bust(userhand)){
    cout << "Dealer wins, you busted\nYou had " << 
    totalhand(userhand) << " and the Dealer had " << 
    totalhand(syshand) << endl;
  } else if (!bust(syshand)){
    cout << "You win, Dealer busted\nYou had " << 
    totalhand(userhand) << " and the Dealer had " << 
    totalhand(syshand) << endl;
  } else {
    if (totalhand(userhand) == totalhand(syshand)){
      cout << "Tie!\nYou had " << 
      totalhand(userhand) << " and the Dealer had " << 
      totalhand(syshand) << endl;
    } else if (totalhand(userhand) > totalhand(syshand)){
      cout << "You win!\nYou had " << 
      totalhand(userhand) << " and the Dealer had " << 
      totalhand(syshand) << endl;
    } else {
      cout << "Dealer wins!\nYou had " << 
      totalhand(userhand) << " and the Dealer had " << 
      totalhand(syshand) << endl;
    }
  }
}

int main() {
  vector<tuple<int, string>> deck {randdeck()};
  dealing(deck);
}
