#include <iostream>
#include <vector>
#include <cmath>

namespace st = std;

int main (){
    st::vector<st::vector<float>> board;
    for(auto y = 0; y < 63; y++){ // For loop for every line
        board.emplace_back();
        if(y % 16 < 8){ // Currently starts with a square made of letters
            for(auto x = 0; x < 63; x++){ // For loop for every space in the row
                if(x % 16 < 8){ // Calculate if the next space needs to be blank or a letter. 0.5 = letter, 0 = blank
                    board[y].push_back(0.5);
                }
                else board[y].push_back(0.0);
            }
        }
        else{ // Currently starts with a blank square
            for(auto x = 0; x < 63; x++){// For loop for every space in the row
                if(x % 16 < 8){// Calculate if the next space needs to be blank or a letter. 0.5 = letter, 0 = blank
                    board[y].push_back(0.0);
                }
                else board[y].push_back(0.5);
            }
        }
    }

    for(auto y = 31; y > -32; y--){ // Starts at the highest y coordinate and works down to the lowest
        for(auto x = -32; x < 31; x++){
            if(st::pow(12, 2) < st::pow(x, 2) + st::pow(y, 2) && st::pow(20, 2) > st::pow(x, 2) + st::pow(y, 2)){ 
                // Before && calculate if x,y coordinates are outside of the middle circle that is not being filled in. 
                // After && calculate a bigger circle that will be filled in if it is outside of the smaller circle
                board[31-y][x+31] = board[31-y][x+31] + 0.5; // Up the brightness by 0.5 of the corresponding x,y coordinate
            }
        }
    }

    for(auto y:board){ // Loop through rows
        for(auto x:y){ // Loop through brightnesses in the row
            if(x == 0.0) st::cout << "  "; // If the brightness value is 0 than print a blank space
            else if(x == 0.5) st::cout << "LL"; // If the brightness value is 1 print L
            else st::cout << "NN"; // Else the brightness value = 2 so print N
        } // Im printing 2 of the same characters to compensate for the difference in height compared to the width
        st::cout << '\n'; // End of row so go to the next line
    }

    return 0;
}