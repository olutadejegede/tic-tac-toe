#include <iostream>
using namespace std;

////////////////////////////////////////////////////////
// Program: Tic-Tac-Toe                                /
// Author: Olutade Jegede                              /
// Class: Data Structures & Algorithms                 /
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
// Structs:                                            /
////////////////////////////////////////////////////////

struct Player
{
string firstName;
string lastName;
char piece;
int wins = 0;
int losses = 0;
};

////////////////////////////////////////////////////////
// Function Prototypes:                                /  
////////////////////////////////////////////////////////

void startGame(Player &player1, Player &player2, Player *&current, Player *&other);
void resetBoard(char board[9]);
void displayBoard(char board[9]);
bool checkLine(int a, int b, int c, char board[9]);
bool checkforWinner(char board[9], Player &current, Player &other, int &gamesPlayed, int &draws);
void displayScoreboard(Player &player1, Player &player2, int &gamesPlayed, int &draws);
int moveIndex(int move);
void makeMove(Player &current, char board[9]);
void determineStart(Player *&current, Player *&other, int gamesPlayed, int draws);
char askToPlayAgain();

////////////////////////////////////////////////////////
// Main function:                                      /
////////////////////////////////////////////////////////

int main() 
{
  Player player1, player2;
  Player *current, *other;
  int gamesPlayed = 0, draws = 0;
  char board[9] = {'1','5','2','8','9','6','4','7','3'};
  player1.piece = 'x';
  player2.piece = 'o';
  
  startGame(player1, player2, current, other);

  char playAgain;
  do
  {
    resetBoard(board);
    displayBoard(board);
    bool endGame = false;
    
  while (!endGame)
  {
    makeMove(*current,board);
    endGame = checkforWinner(board, *current, *other, gamesPlayed,draws);
    if (!endGame)
    {
      swap(current,other);
    }
  }
    
  displayScoreboard(player1, player2, gamesPlayed, draws);
  determineStart(current, other, gamesPlayed, draws);
  playAgain = askToPlayAgain();
  }
    
  while (playAgain == 'y' || playAgain == 'Y');
  
  cout << endl << "Thanks for playing!" << endl;
  
  return 0;
}

////////////////////////////////////////////////////////
// Function Definitions:                               /
////////////////////////////////////////////////////////


////////////////////////////////////////////////////////
// Function that hanldes the start of the game:        /
////////////////////////////////////////////////////////

void startGame(Player &player1, Player &player2, Player *&current, Player *&other)
{
  cout << "Player 1, enter your first and last name: ";
  cin >> player1.firstName >> player1.lastName;
  cout << "Player 2, enter your first and last name: ";
  cin >> player2.firstName >> player2.lastName;

  if (player1.lastName > player2.lastName)
  {
    current = &player1;
    other = &player2;
  }
  else if (player1.lastName < player2.lastName)
  {
    current = &player2;
    other = &player1;
  }
  else
  {
    if (player1.firstName > player2.firstName)
    {
      current = &player1;
      other = &player2;
    }
    else if (player1.firstName < player2.firstName)
    {
      current = &player2;
      other = &player1;
    }
    else 
    {
      current = &player1;
      other = &player2;
    }
  }
  // current->piece = 'x';
  // other->piece = 'o';
}

////////////////////////////////////////////////////////
// Function that resets the board:                     / 
////////////////////////////////////////////////////////

void resetBoard(char board[9])
{
  board[0] = '1';
  board[1] = '5';
  board[2] = '2';
  board[3] = '8';
  board[4] = '9';
  board[5] = '6';
  board[6] = '4';
  board[7] = '7';
  board[8] = '3';
}

////////////////////////////////////////////////////////
// Function that displays the board:                   /
////////////////////////////////////////////////////////

void displayBoard(char board[9])
{
  cout << "+---+---+---+" << endl;
  cout << "| " << board[0] << " | " << board[1] << " | " << board[2] << " |" << endl;
  cout << "+---+---+---+" << endl;
  cout << "| " << board[3] << " | " << board[4] << " | " << board[5] << " |" << endl;
  cout << "+---+---+---+" << endl;
  cout << "| " << board[6] << " | " << board[7] << " | " << board[8] << " |" << endl;
  cout << "+---+---+---+" << endl;
}

////////////////////////////////////////////////////////
// Function to check all alternative winning lines:    /
////////////////////////////////////////////////////////

bool possibleWins(char a, char b) 
{
  return (a == 'o' && b == 'O') || (a == 'O' && b == 'o') ||
         (a == 'x' && b == 'X') || (a == 'X' && b == 'x') ||
         (a == 'o' && b == 'o') || (a == 'x' && b == 'x');
}

////////////////////////////////////////////////////////
// Function that capitalizies winning line(s):         /
////////////////////////////////////////////////////////

bool checkLine(int a, int b, int c, char board[9])
{
  if (possibleWins(board[a],board[b]) && possibleWins(board[b],board[c]))
  {
    board[a] = toupper(board[a]);
    board[b] = toupper(board[b]);
    board[c] = toupper(board[c]);
    return true;
  }
  return false;
}

////////////////////////////////////////////////////////
// Function that checks for a winner or tie:           /
////////////////////////////////////////////////////////

bool checkforWinner(char board[9], Player &current, Player &other, int &gamesPlayed, int &draws)
{
    bool win = false;
  
    for (int i = 0; i < 3; i ++)
    {
      if(checkLine(i, i+3, i+6, board))
      {
        win = true;
      }
    }
  
    for (int i = 0; i < 7; i+=3)
    {
      if (checkLine(i, i+1, i+2, board))
      {
        win = true;
      }
    }
  
    if (checkLine(0, 4, 8, board)) win = true;
    if (checkLine(2, 4, 6, board)) win = true;

    if (win)
    {
        displayBoard(board);
        cout << "\n" << current.firstName << " has won the game!" << endl;

        current.wins++;
        other.losses++;
        gamesPlayed++;
        return true;
    }

    bool draw = true;
    for (int i = 0; i < 9; ++i)
    {
        if (board[i] != 'x' && board[i] != 'o')
        {
            draw = false;
            break;
        }
    }

    if (draw)
    {
      displayBoard(board);
      cout << "\nThe game is a draw!" << endl;
      draws++;
      gamesPlayed++;
      return true;
    }

    displayBoard(board);
    return false;
}

////////////////////////////////////////////////////////
// Function that displays the scoreboard:              / 
//////////////////////////////////////////////////////// 

void displayScoreboard(Player &player1, Player &player2, int &gamesPlayed, int &draws)
{
  cout << "Number of games played: " << gamesPlayed << endl;
  cout << "Number of draws: " << draws << endl;
  cout << player1.firstName << " " << player1.lastName << " win: " << player1.wins << endl;
  cout << player1.firstName << " " << player1.lastName << " losses: " << player1.losses << endl;
  cout << player2.firstName << " " << player2.lastName << " win: " << player2.wins << endl;
  cout << player2.firstName << " " << player2.lastName << " losses: " << player2.losses << endl;
}

////////////////////////////////////////////////////////
// Function that match the move to proper position:    /
////////////////////////////////////////////////////////

int moveIndex(int move)
{
  switch (move)
  {
    case 1: return 0;
    case 5: return 1;
    case 2: return 2;
    case 8: return 3;
    case 9: return 4;
    case 6: return 5;
    case 4: return 6;
    case 7: return 7;
    case 3: return 8;
    default: return -1;
  }
}

////////////////////////////////////////////////////////
// Function to prompt the user to make a move:         /
////////////////////////////////////////////////////////

void makeMove(Player &current, char board[9])
{
  int move;
  cout << current.firstName << ", make your move (1-9): ";
  cin >> move;
  int index = moveIndex(move);

  if (index != -1 && board[index] != 'x' && board[index] != 'o')
  {
    board[index] = current.piece;
  }
  else
  {
    cout << "Invalid move (must be between 1-9) Try again." << endl;
    makeMove(current,board);
  }
}

////////////////////////////////////////////////////////
// Function that determines who starts the next game:  /
////////////////////////////////////////////////////////

void determineStart(Player *&current, Player *&other, int gamesPlayed, int draws)
{
    if (draws > 0 && gamesPlayed == draws) {
        swap(current, other);
    } else {
        swap(current, other);
    }
}

/////////////////////////////////////////////////////////////
// Function that asks the user if they want to play again:  /
/////////////////////////////////////////////////////////////
char askToPlayAgain()
{
    char playAgain;
    cout << "Do you want to play again? (y/n): ";
    cin >> playAgain;
    return playAgain;
}