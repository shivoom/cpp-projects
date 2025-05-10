#include <iostream>
using namespace std;

int main(){
    //length for loop
    int length {};
    int current_length {0};
    
    //starting number is 0 and begins on 1
    int starting_number {1};
    int previous_number {0};

    cout << "How many numbers in Fibonacci's Sequence do you want? ";
    cin >> length;
    
    //creating loop
    while (length > current_length){
        ++current_length;
        //the operation
        cout << starting_number << ", ";
        starting_number += previous_number;
        previous_number = starting_number - previous_number;
    }

    cout << endl;
    return 0;
}