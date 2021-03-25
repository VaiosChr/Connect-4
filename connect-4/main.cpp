#include <iostream>

#include "board.hpp"
#include "helpers.hpp"
#include "player.hpp"

#define rows 6
#define columns 7

using namespace std;

int move(Board board, Player player);

int main()
{
    bool winner = false;
    Player player1(1, "O"), player2(2, "X");
//    Player player2(2, "X");
    Board board(rows, columns);
    board.print();
    
    int turn = 1;
    
    while(!board.is_full())
    {
        cout << "TURN: " << turn << endl;
        //player 1
        if(board.play(player1, move(board, player1)))
        {
            cout << "Player 1 is the winner!" << endl;
            winner = true;
            break;
        }
        //player 2
        if(board.play(player2, move(board, player2)))
        {
            cout << "Player 2 is the winner!" << endl;
            winner = true;
            break;
        }
    }
    if(!winner) cout << "It's a tie!" << endl;
    cout << "Game over!" << endl;
    
    return 0;
}

int move(Board board, Player player)
{
    int col;
    
    cout << "It's player " << player.get_id() << "'s turn." << ")" << endl;
    cout << "Enter your move: ";
    cin >> col;
    while(col < 1 || col > columns + 1 || !(board.get_char(0, col - 1) == " "))
    {
        cout << "This is an invalid move. Try again: ";
        cin >> col;
    }
    
    return --col;
}
