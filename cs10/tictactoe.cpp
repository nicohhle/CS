#include <vector>
#include <iostream>

using namespace std;

const bool CLEAR_SCREEN = true;

/// @brief Utilizes an escape character sequence to clear the screen
void clearScreen() {
    cout << endl;

    if (CLEAR_SCREEN) {
        cout << "\033c";
    }

    cout << endl;

    return;
}


/// @brief Draws the provided tic-tac-toe board to the screen
//  @param board is the tic-tac-toe board that should be drawn
void drawBoard(const vector < char >&gameBoard) {
    clearScreen();
    for (int i = 0; i < 9; i += 3) {
        cout << "  " << gameBoard.at(i) << "  |  " << gameBoard.at(i + 1) << "  |  "
            << gameBoard.at(i + 2) << "  " << endl;
        if (i < 6) {
            cout << "-----|-----|-----" << endl;
        }
    }
    cout << endl;

    return;
}



/// @brief Fills vector with characters starting at lower case a.
///
///     If the vector is size 3 then it will have characters a to c.
///     If the vector is size 5 then it will have characters a to e.
///     If the vector is size 26 then it will have characters a to z.
///
/// @param v the vector to initialize
/// @pre-condition the vector size will never be over 26
void initVector(vector <char> &v) {

    // TODO: implement function
    for (int i = 0; i < v.size(); ++i) {
            v.at(i) = 'a' + i;
    }
    
    return;
}


/// @brief Converts a character representing a cell to associated vector index
/// @param the position to be converted to a vector index
/// @return the integer index in the vector, should be 0 to (vector size - 1)
int convertPosition(char boardPosition) {

    // TODO: implement function
    int pos;
    vector<char> v(9);
    
    for (int i = 0; i < 9; ++i) {
        v.at(i) = 'a' + i;
        if (v.at(i) == boardPosition) {
            pos = i;
        }
    } 
    
    return pos;
}


/// @brief Predicate function to determine if a spot in board is available.
/// @param board the current tic-tac-toe board 
/// @param position is an index into vector to check if available
/// @return true if position's state is available (not marked) AND is in bounds
bool validPlacement(const vector<char>  &gameBoard, int positionIndex) {

    // TODO: implement function
    vector<char> v(9);
    for (int i = 0; i < 9; ++i) {
        v.at(i) = 'a' + i;
    }
    
    for (int i = 0; i < 9; ++i) {
        if (v.at(i) == gameBoard.at(positionIndex)) {
            return true;
        }
    }
    
    return false;
}

/// @brief Acquires a play from the user as to where to put her mark
///
///     Utilizes convertPosition and validPlacement functions to convert the
///     user input and then determine if the converted input is a valid play.
///
/// @param board the current tic-tac-toe board 
/// @return an integer index in board vector of a chosen available board spot
int getPlay(const vector<char> &gameBoard) {

    // TODO: implement function
    int pos;
    bool isValid;
    char boardPosition = ' ';

    cout << "Please choose a position: ";
    cin >> boardPosition;
    cout << endl;
    
    pos = convertPosition(boardPosition);
    isValid = validPlacement(gameBoard, pos);
    
    if (isValid) {
        return pos;
    }
    
    return -1;
}


/// @brief Predicate function to determine if the game has been won
///
///     Winning conditions in tic-tac-toe require three marks from same 
///     player in a single row, column or diagonal.
///
/// @param board the current tic-tac-toe board 
/// @return true if the game has been won, false otherwise
bool gameWon(const vector<char> &gameBoard) {

    // TODO: implement function
    for (int i = 0; i < 8; i = i + 3) {
        if (gameBoard.at(i) == gameBoard.at(i + 1) && gameBoard.at(i) == gameBoard.at(i + 2)) {
            return true;
        }
    }
    
    for (int i = 0; i < 3; ++i) {
        if (gameBoard.at(i) == gameBoard.at(i + 3) && gameBoard.at(i) == gameBoard.at(i + 6)) {
            return true;
        }
    }
    
    if (gameBoard.at(0) == gameBoard.at(4) && gameBoard.at(0) == gameBoard.at(8)) {
        return true;
    }
    
    if (gameBoard.at(2) == gameBoard.at(4) && gameBoard.at(2) == gameBoard.at(6)) {
        return true;
    }
    
    return false;
}


/// @brief Predicate function to determine if the board is full
/// @param board the current tic-tac-toe board 
/// @return true iff the board is full (no cell is available)
bool boardFull(const vector<char> &gameBoard) {

    // TODO: implement function
    
    for (int i = 0; i <  9; ++i) {
        if (gameBoard.at(i) != 'O' && gameBoard.at(i) != 'X') {
            return false;
        }
    }
    
    return true;
}


// Global constants for player representation
const int PLAYER1 = 0;
const int PLAYER2 = 1;

int main() {
    // Variables that you may find useful to utilize
    vector<char> gameBoard(9);
    int curPlay;
    int whosTurn = PLAYER1; // Player 1 always goes first and is 'X'
    bool fullBoard = false;
    bool wonGame = false;

    /// TODO: Initialize board to empty state
    /// TODO: Display empty board
    initVector(gameBoard);
    drawBoard(gameBoard);
        
    while (!fullBoard && !wonGame) {
        
        /// TODO: Play until game is over
        /// TODO: Get a play
        /// TODO: Set the play on the board
        /// TODO: Switch the turn to the other player
        /// TODO: Output the updated board
        /// TODO: Determine winner and output appropriate message
        
        curPlay = getPlay(gameBoard);
        
        if (curPlay != -1) {
            if (whosTurn == 0) {
                gameBoard.at(curPlay) = 'X'; //X at Player1's play
                whosTurn = PLAYER2; //switched turns here
            } else {
                gameBoard.at(curPlay) = 'O';
                whosTurn = PLAYER1;
            } 
        } else {
            curPlay = getPlay(gameBoard);
            if (whosTurn == 0) {
                gameBoard.at(curPlay) = 'X'; //X at Player1's play
                whosTurn = PLAYER2; //switched turns here
            } else {
                gameBoard.at(curPlay) = 'O';
                whosTurn = PLAYER1;
            }
        }
    
    fullBoard = boardFull(gameBoard);
    wonGame = gameWon(gameBoard);
    
    drawBoard(gameBoard);
    
    }
    
    if (fullBoard && !wonGame) {
        cout << "No one wins" << endl;
    }
    
    if (wonGame) {
        if (whosTurn == PLAYER1) {
            cout << "PLAYER 2 WINS!" << endl;
        } else {
            cout << "PLAYER 1 WINS!" << endl;
        }
    }
    
    return 0;
}