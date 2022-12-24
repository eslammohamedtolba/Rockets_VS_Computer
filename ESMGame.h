#ifndef INC_5_6_ESMGAME_H
#define INC_5_6_ESMGAME_H
#include "bits/stdc++.h"
using namespace std;
// This class represents a n x n board
// used in ESMGAME game

class Board {
protected:
    char **board;
    int  n=0;
public:
    // empty constructor 
    Board();
    // copy constructor
    Board(Board & B);
    // assignment operator
    Board operator=(Board B);
    // move assignment
    Board operator=(Board &&B);
    // move constructor
    Board(Board &&B);
    // to fill board of size n*n
    void fill_board(int n,char up,char left);
    // to check if there any moves to this player that has this symbol and direct
    bool avalailablemove(char symbol,char direct);
    // Return true  if move is valid and put it on board
    // within board boundaries in empty cell
    // Return false otherwise
    bool update_board (int x, int y,char direct, char symbol);
    // Returns true if there is any winner
    // either R or G
    // Written in a complex way. DO NOT DO LIKE THIS.
    bool is_winner();
    // Display the board and the pieces on it
    void display_board();
    void modifyboard(int i,int j,char character);
    // to return the size of the Board
    void Setsize(int size);
    int Getsize();
    // this destructor to delete the two dimensional dynamic array
    ~Board();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This class represents a player who has
// a name and a symbol to put on board
class Player {
protected:
    string name;
    char symbol,direction;
public:
    // Two constructors to initiate player
    // Give player a symbol to use in playing
    // It can be R or G or others
    // Optionally, you can give him ID or order
    // Like Player 1 and Player 2
    Player (char direction,char symbol); // Needed for computer players
    Player (int order,char direction, char symbol);
    // Get desired move: x y (each between 0 and n-1)
    // Virtual (can change for other player types)
    virtual void get_move(int& x, int& y,Board &b);
    // Give player info as a string
    string to_string();
    // Get symbol used by player
    char get_symbol();
    // Get direction of player
    char Getdirect();
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class GameManager {
public:
    void run();
    // This method creates board and players
    // It displays board
    // While True
    //   For each player
    //      It takes a valid move as x, y pair (between 0 - n-1)
    //      It updates board and displays otit
    //      If winner, declare so and end
    //      If draw, declare so and end

};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This class represents a computer player
// that generates positions x y (0 to n-1)
// If invalid, game manager asks to regenerate
class ComputerPlayer: public Player {
public:
    // Take a symbol and pass it to parent
    ComputerPlayer (char directoin,char symbol);
    // Generate a specific valid move
    void get_move(int& x, int& y,Board &b);
};

#endif //INC_5_6_ESMGAME_H