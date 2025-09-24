#include <iostream>
#include <vector>
#include <cmath>

namespace st = std;

st::vector<st::vector<float>> createBoard(int dimensions){
    st::vector<st::vector<float>> board;
    int lenghtTwoBlocks = dimensions/4;
    int lenghtOneBlock = dimensions/8;
    for(auto y = 0; y < dimensions-1; y++){ // For loop for every line
        board.emplace_back(); // Add empty vector to the back of the first vector
        if(y % (lenghtTwoBlocks) < (lenghtOneBlock)){ // Currently starts with a square made of letters
            for(auto x = 0; x < dimensions-1; x++){ // For loop for every space in the row
                if(x % (lenghtTwoBlocks) < (lenghtOneBlock)){ // Calculate if the next space needs to be blank or a letter. 0.5 = letter, 0 = blank
                    board[y].push_back(0.5); // Add 0.5 to the back of the second vector
                }
                else board[y].push_back(0.0); // Add 0.0 to the back of the second vector
            }
        }
        else{ // Currently starts with a blank square
            for(auto x = 0; x < dimensions-1; x++){// For loop for every space in the row
                if(x % (lenghtTwoBlocks) < (lenghtOneBlock)){// Calculate if the next space needs to be blank or a letter. 0.5 = letter, 0 = blank
                    board[y].push_back(0.0); // Add 0.5 to the back of the second vector
                }
                else board[y].push_back(0.5); // Add 0.5 to the back of the second vector
            }
        }
    }
    return board;
}

void addCircle(auto dimensions, auto &board){
    int middleBoard = dimensions/2-1;
    for(auto y = dimensions-1; y > -dimensions; y--){ // Starts at the highest y coordinate and works down to the lowest
        for(auto x = -dimensions; x < dimensions-1; x++){
            if(st::pow(dimensions/4-(dimensions/16), 2) < st::pow(x, 2) + st::pow(y, 2) && st::pow(dimensions/8*3-(dimensions/16), 2) > st::pow(x, 2) + st::pow(y, 2)){ 
                // Before && calculate if x,y coordinates are outside of the middle circle that is not being filled in. 
                // After && calculate a bigger circle that will be filled in if it is outside of the smaller circle
                board[middleBoard-y][x+middleBoard] = board[middleBoard-y][x+middleBoard] + 0.5; // Up the brightness by 0.5 of the corresponding x,y coordinate
            }
        }
    }
    return;
};

void printBoard(auto &board){
    for(auto y:board){ // Loop through rows
        for(auto x:y){ // Loop through brightnesses in the row
            if(x == 0.0) st::cout << "  "; // If the brightness value is 0 than print a blank space
            else if(x == 0.5) st::cout << "LL"; // If the brightness value is 1 print L
            else st::cout << "NN"; // Else the brightness value = 2 so print N
        } // Im printing 2 of the same characters to compensate for the difference in height compared to the width
        st::cout << '\n'; // End of row so go to the next line
    }
    return;
}

int main (){
    auto dimensions = 64; // Needs to be dividable by 8 for best results!
    auto board = createBoard(dimensions); 
    addCircle(dimensions, board);
    printBoard(board);
    
}
