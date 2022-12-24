#include "ESMGame.h"
Board::Board(){}
// copy constructor
Board::Board(Board &B)
{
    n=B.Getsize();
    board=new char*[n];
    for(int i=0;i<n;i++){
        board[i]=new char[n];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            board[i][j]=B.board[i][j];
        }
    }
}
// assignment operator
Board Board::operator=(const Board B)
{
    for(int i=0;i<n;i++){
        delete []board[i];
    }
    delete []board;

    board=new char*[n];
    for(int i=0;i<n;i++){
        board[i]=new char[n];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            board[i][j]=B.board[i][j];
        }
    }
    return *this;
}
// move assignment
Board Board::operator=(Board &&B)
{
    int allsize=B.Getsize();Setsize(allsize);
    board=new char*[allsize];
    for(int i=0;i<allsize;i++){
        board[i]=new char[allsize];
    }
    for(int i=0;i<allsize;i++){
        for(int j=0;j<allsize;j++){
            board[i][j]=B.board[i][j];
        }
    }
    for(int i=0;i<n;i++){
        delete []B.board[i];
    }
    delete []B.board;
    return *this;
}
// move constructor
Board::Board(Board &&B)
{
    int allsize=B.Getsize();Setsize(allsize);
    board=new char*[allsize];
    for(int i=0;i<allsize;i++){
        board[i]=new char[allsize];
    }
    for(int i=0;i<allsize;i++){
        for(int j=0;j<allsize;j++){
            board[i][j]=B.board[i][j];
        }
    }
    for(int i=0;i<n;i++){
        delete []B.board[i];
    }
    delete []B.board;
}
void Board::modifyboard(int i,int j,char character)
{
    board[i][j]=character;
}
// this function to fill board(array) of the Board
void Board::fill_board(int n,char up,char left){
    this->n=n;
    board=new char*[n];
    for(int i=0;i<n;i++){
        board[i]=new char[n];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==0 && j!=0 && j!=n-1){
                board[i][j]=up;
            }
            else if(j==0 && i!=0 && i!=n-1){
                board[i][j]=left;
            }
            else{
                board[i][j]='-';
            }
        }
    }
}
// to check if there any moves to this player that has this symbol and direct
bool Board::avalailablemove(char symbol,char direct)
{
    int counter=0;
    for(int i=0;i<(n-(direct=='Y'));i++){
        for(int j=0;j<(n-(direct=='X'));j++){
            if(board[i][j]==symbol){
                if(direct=='X'){
                    if(board[i][j+1]=='-'){
                        counter++;
                    }
                    else if(j!=n-2){
                        if(board[i][j+2]=='-'){
                            counter++;
                        }
                    }
                }
                else{
                    if(board[i+1][j]=='-'){
                        counter++;
                    }
                    else if(i!=n-2){
                        if(board[i+2][j]=='-'){
                            counter++;
                        }
                    }
                }
            }
        }
    }
    return (counter);
}
// Return true  if move is valid and put it on board
// within board boundaries in empty cell
// Return false otherwise
bool Board::update_board (int x, int y,char direct, char symbol){
    // Only update if move is valid
    if (!(x < 1 || x > n-1 || y < 1 || y > n-1) && (board[x][y] == '-')){
        if(direct=='X'){
            if((board[x][y-1]==symbol)){
                board[x][y] = toupper(symbol);
                board[x][y-1]='-';
                return true;
            }
            else if(board[x][y-1]!='-' && board[x][y-2]==symbol){
                board[x][y] = toupper(symbol);
                board[x][y-2]='-';
                return true;
            }
            return false;
        }
        else if(direct=='Y'){
            if((board[x-1][y]==symbol)){
                board[x][y] = toupper(symbol);
                board[x-1][y]='-';
                return true;
            }
            else if(board[x-1][y]!='-' && board[x-2][y]==symbol){
                board[x][y] = toupper(symbol);
                board[x-2][y]='-';
                return true;
            }
            return false;
        }
        return false;
    }
    else
        return false;
}
// Display the board and the pieces on it
void Board::display_board() {
    for (int i=0;i<n;i++) {
        cout << "\n| ";
        for (int j=0;j<n;j++) {
            cout << setw(2) << board [i][j] << " |";
        }
    }
    cout << endl;
}
// Returns true if there is any winner
// either G or R
// Written in a complex way. DO NOT DO LIKE THIS.
bool Board::is_winner(){
    int countF=0,countS=0;
    for(int i=1;i<n-1;i++){
        if(board[i][n-1]=='R' || board[i][n-1]=='G'){
            countF++;
        }
        if(board[n-1][i]=='G' || board[n-1][i]=='R'){
            countS++;
        }
    }
    return ((countF==n-2) || (countS==n-2));
}
// to return the array size
int Board::Getsize()
{
    return n;
}
// to put the board array size
void Board::Setsize(int size)
{
    n=size;
}
// this destructor to remove two dimensional dynamic array that called board of size n*n
Board::~Board(){
    for(int i=0;i<n;i++){
        delete []board[i];
    }
    delete []board;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Give player a symbol to use in playing
// It can be X or O or others
// This is needed for computer players
// as it does not ask for a name
Player::Player(char direct,char symbol) {
    this->symbol = symbol;
    this->direction=direct;
}
// Optionally, you can give him ID or order
// Like Player 1 and Player 2
Player::Player (int order,char direction, char symbol) {
    cout << "Welcome player " << order << endl;
    cout << "Please enter your name: ";
    cin >> name;
    this->symbol = symbol;
    this->direction=direction;
}
// Get desired move: x y (each between 0 and 2)
// Virtual (can change for other player types)
void Player::get_move (int& x, int& y,Board &b){
    cout << "\nPlease "<<name<<" that has symbol ( "<<symbol<<" ) enter your move x and y separated by spaces: ";
    cin >> x >> y;
}
// Give player info as a string
string Player::to_string(){
    return "Player: " + name ;
}
// Get symbol used by player
char Player::get_symbol() {
    return symbol;
}
// Get direction of the player
char Player::Getdirect()
{
    return direction;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// this class to start the game
// and allows the players to play
// and determines if any player of them is winner or draw in the game end
void GameManager::run() {
    Board R_G;
    int x, y, choice1,n=0;
    Player* players[2];
    players[0] = new Player (1,'Y', 'G');
    cout << "Press 1 if you want to play with computer: ";
    cin >> choice1;
    if (choice1 != 1)
        players[1] = new Player (2,'X', 'R');
    else
        //Player pointer points to child
        players[1] = new ComputerPlayer ('X','R');
    while(n<3){
        cout<<"please enter the size of board that must be greater than 2 ----> ";
        cin>>n;
    }
    R_G.fill_board(n,players[0]->get_symbol(),players[1]->get_symbol());
    R_G.display_board();
    while (true) {
        for (int i:{0,1}) {
            if(R_G.avalailablemove(players[i]->get_symbol(),players[i]->Getdirect())){
                players[i]->get_move(x, y,R_G);
                while (!R_G.update_board (x, y,players[i]->Getdirect(), players[i]->get_symbol())){
                    players[i]->get_move(x, y,R_G);
                }
                R_G.display_board();
                // to check if any of two players is winner
                if (R_G.is_winner()){
                    cout  << players[i]->to_string() << " wins\n";
                    return;
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// this constructor to give the player name
ComputerPlayer::ComputerPlayer (char direct,char symbol):Player(direct,symbol)
{
    this->name="Computer Player";
    cout<<"My name is "<<name<< endl;
}
// this function to determine the winning, losing of player or drawing or two players
// this struct to store two indecies with state of win or draw or lose
struct indexstate
{
    int index1,index2,state;
};
// this function to check if there is win move or not
int currentresult(Board a,bool mystate,char symbol,char direct)
{
    bool winning=a.is_winner(),
    prevent=a.avalailablemove(symbol,direct);
    if(winning && (mystate==1)){
        return 2;
    }
    else if((!prevent) && (mystate==1)){
        return 1;
    }
    else if((!prevent) && (mystate==0)){
        return -1;
    }
    else if(winning && (mystate==0)){
        return -2;
    }
    else{
        return 0;
    }
}
// Generate a specific valid move
indexstate specvalxy(Board b,char symbol,char direct,bool mystate)
{
    // we must take copy from the board because we will change it and after that take the same copy to check another x and y
    Board a=b;int result=0,sizeborard=a.Getsize();
    indexstate myresult={1,1,(mystate==0?3:-3)},myreplacedresult=myresult;
    for(int i=1;i<sizeborard;i++){
        for(int j=1;j<sizeborard;j++){
            if(a.update_board(i,j,direct,symbol)){
                result=currentresult(a,mystate,(symbol=='G'?'R':'G'),(direct=='X'?'Y':'X'));
                if(result==1 || result==-1){
                    myreplacedresult=specvalxy(a,symbol,direct,mystate);
                    if(mystate==1){
                        //max
                        if(myreplacedresult.state>myresult.state){
                            myresult={i,j,myreplacedresult.state};
                        }
                    }
                    else{
                        //min
                        if(myreplacedresult.state<myresult.state){
                            myresult={i,j,myreplacedresult.state};
                        }
                    }
                }
                else if(result!=0){
                    if(mystate==1){
                        //max
                        if(result>myresult.state){
                            myresult={i,j,result};
                        }
                    }
                    else{
                        //min
                        if(result<myresult.state){
                            myresult={i,j,result};
                        }
                    }
                }
                else{
                    myreplacedresult=specvalxy(a,(symbol=='R'?'G':'R'),(direct=='X'?'Y':'X'),(mystate==1?0:1));
                    if(mystate==1){
                        //max
                        if(myreplacedresult.state>myresult.state){
                            myresult={i,j,myreplacedresult.state};
                        }
                    }
                    else{
                        //min
                        if(myreplacedresult.state<myresult.state){
                            myresult={i,j,myreplacedresult.state};
                        }
                    }
                }
                a.modifyboard(i,j,'-');
            }
        }
    }
    return myresult;
}
void ComputerPlayer::get_move (int& x, int& y,Board &b){
    indexstate myresult;
    myresult=specvalxy(b,symbol,direction,1);
    cout<<myresult.state<<" "<<myresult.index1<<" "<<myresult.index2<<endl;
    x=myresult.index1;y=myresult.index2;
}