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
    //Change this to false if there is going to be a player 2
    bool player_2_is_ai = true;
    bool winner = false;
    Player player1(1, "O"), player2(2, "X", player_2_is_ai);
    Board board(rows, columns);
    board.print();
    
    int turn = 1;
    
    while(!board.is_full())
    {
        cout << "TURN: " << turn << endl;
        //player 1
        if(board.play(player1))
        {
            cout << "Player 1 is the winner!" << endl;
            winner = true;
            break;
        }
        //player 2
        if(board.play(player2))
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

