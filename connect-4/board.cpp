#include "board.hpp"

Board::Board(int rows, int columns)
{
    this->rows = rows;
    this->columns = columns;
    
    for(int i = 0; i < rows; i++) board.push_back(vector<string>(columns, " "));
}

void Board::print()
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++) cout << " ------- ";
        cout << endl;
        for(int j = 0; j < columns; j++) cout << "|       |";
        cout << endl;
        for(int j = 0; j < columns; j++) cout << "|   " << board[i][j] << "   |";
        cout << endl;
        for(int j = 0; j < columns; j++) cout << "|       |";
        cout << endl;
    }
    for(int i = 0; i < columns; i++) cout << " ------- ";
    cout << endl;
}

bool Board::play(Player player)
{
    int col = 0;
    if(player.get_is_ai()) col = ai_play(player);
    else
    {
        cout << "It's Player " << player.get_id() << "'s turn." << endl;
        cout << "Enter your move: ";
        
        int col = player.move();
        
        while(col < 0 || col > columns || !(this->get_char(0, col) == " "))
        {
            cout << "This is an invalid move. Try again: ";
            col = player.move();
        }
    }
    
    for(int i = rows - 1; i >= 0; i--)
    {
        if(board[i][col] == " ")
        {
            board[i][col] = player.get_name();
            break;
        }
    }
    print();
    
    return wins(player);
}

bool Board::wins(Player player)
{
    int counter;
    
    //vertical
    for(int j = 0; j < columns; j++)
    {
        counter = 0;
        for(int i = 0; i < rows; i++)
        {
            if(board[i][j] == player.get_name())
            {
                counter++;
                if(counter >= 4) return true;
            }
            else counter = 0;
        }
    }
    
    //horizontal
    for(int i = 0; i < rows; i++)
    {
        counter = 0;
        for(int j = 0; j < columns; j++)
        {
            if(board[i][j] == player.get_name())
            {
                counter++;
                if(counter >= 4) return true;
            }
            else counter = 0;
        }
    }
    
    //positive diagonal
    for(int i = rows - 1; i >= 0; i--)
    {
        counter = 0;
        for(int j = 0; j < columns; j++)
        {
            counter = 0;
            for(int k = 0; k < i && k < columns - j; k++)
            {
                if(board[i - k][j + k] == player.get_name())
                {
                    counter++;
                    if(counter >= 4) return true;
                }
                else counter = 0;
            }
        }
    }
    
    //negative diagonal
    for(int i = 0; i < rows; i++)
    {
        counter = 0;
        for(int j = 0; j < columns; j++)
        {
            counter = 0;
            for(int k = 0; k < rows - i && k < columns - j; k++)
            {
                if(board[i + k][j + k] == player.get_name())
                {
                    counter++;
                    if(counter >= 4) return true;
                }
                else counter = 0;
            }
        }
    }
    return false;
}

string Board::get_char(int i, int j)
{
    return board[i][j];
}

bool Board::is_full()
{
    for(int j = 0; j < columns; j++)
    {
        if(board[0][j] == " ") return false;
    }
    
    return true;
}

bool Board::ai_play(Player player)
{
    //TODO: IMPLEMENT THE A.I. PART OF THE ALGORITHM
    
    return wins(player);
}
