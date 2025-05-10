#include <iostream>
#include <random>
#include <vector>
using namespace std;

int main(){
    // creating random device and defining range
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0,2);
    
    // defining variables
    int user_choice {};
    int computer_choice {dis(gen)};
    vector <string> options {"Rock", "Paper", "Scissors"};
    
    // intro and input
    cout << "Welcome to Rock Paper Scissors!\n0 is Rock, 1 is Paper, and 2 is Scissors.\n";
    cout << "Make your selection: ";
    cin >> user_choice;
    cout << "===========================================" << endl;
    // checking for illegal user choice
    if (user_choice == 0 || user_choice == 1 || user_choice == 2){
        cout << "You chose " << options[user_choice] << "." << endl;
        cout << "The computer chose " << options[computer_choice] << "." << endl;
        
        // output decision-maker
        if (user_choice==computer_choice) {
            cout << "It's a Tie!" << endl;
        } else if ((user_choice == computer_choice-1) || (user_choice == 3 && computer_choice == 1)) {
            cout <<"You Lose!" << endl;
        } else {
            cout << "You Win!" << endl;
        }
    } else {
        cout << "Invalid option. Try again.";
        return 1;
    }
    return 0;
}