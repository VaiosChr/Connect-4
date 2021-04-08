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
    
    return wins(player.get_id());
}

bool Board::wins(int id)
{
    int counter;
    string character;
    
    if(id == 2) character = "X";
    else character = "O";
    
    //vertical
    for(int j = 0; j < columns; j++)
    {
        counter = 0;
        for(int i = 0; i < rows; i++)
        {
            if(board[i][j] == character)
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
            if(board[i][j] == character)
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
                if(board[i - k][j + k] == character)
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
                if(board[i + k][j + k] == character)
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
    vector<vector<int>> board_2(rows, vector<int>(columns, 0));
    
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            if(board[i][j] == "X") board_2[i][j] = 1;
            else if(board[i][j] == "O") board_2[i][j] = 2;
        }
    }
    
    minmax(player, board_2, 3, true);
    
    return wins(player.get_id());
}

float Board::minmax(Player player, vector<vector<int>> check_board, int depth, bool is_max)
{
    if(depth == 0 || wins(1)) return evaluation(check_board);
    
    if(is_max)
    {
        float max_eval = - INFINITY;
        
        for(int j = 0; j < columns; j++)
        {
            if(check_board[0][j] != 0) continue;
            for(int i = rows - 1; i >= 0; i--)
            {
                if(check_board[i][j] == 0)
                {
                    check_board[i][j] = 1;
                    
                    float eval = minmax(player, check_board, depth - 1, false);
                    
                    max_eval = max(max_eval, eval);
                }
            }
        }
        
        return max_eval;
    }
    
    else
    {
        float min_eval = INFINITY;
        
        for(int j = 0; j < columns; j++)
        {
            if(check_board[0][j] != 0) continue;
            for(int i = rows - 1; i >= 0; i--)
            {
                if(check_board[i][j] == 0)
                {
                    check_board[i][j] = 2;
                    
                    float eval = minmax(player, check_board, depth - 1, true);
                    
                    min_eval = min(min_eval, eval);
                }
            }
        }
        
        return min_eval;
    }
}

float Board::evaluation(vector<vector<int>> array)
{
    int counter = 0, no_co = 0, rating = 0;
    
    if(wins(2)) return INFINITY;
    else if(wins(1)) return - INFINITY;
    
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            //for ai
            if(array[i][j] == 2)
            {
                //vertical
                for(int k = 1; k < 4; k++)
                {
                    if(i - k >= 0)
                    {
                        if(array[i - k][j] == 1) break;
                        else counter++;
                        if(array[i - k][j] == 2) no_co++;
                    }
                }
                if(counter >= 4)
                {
                    if(no_co > 0) rating += pow(2, no_co + 1);
                }
                //horizontal - right
                counter = 0;
                no_co = 0;
                for(int k = 1; k < 4; k++)
                {
                    if(j + k < columns)
                    {
                        if(array[i][j + k] == 1) break;
                        else counter++;
                        if(array[i][j + k] == 2) no_co++;
                    }
                }
                if(counter >= 4)
                {
                    if(no_co > 0) rating += pow(2, no_co + 1);
                    else rating += 2;
                }
                //horitzontal - left
                counter = 0;
                no_co = 0;
                for(int k = 1; k < 4; k++)
                {
                    if(j - k >= 0)
                    {
                        if(array[i][j - k] == 1) break;
                        else counter++;
                        if(array[i][j - k] == 2) no_co++;
                    }
                    
                }
                if(counter >= 4)
                {
                    if(no_co > 0) rating += pow(2, no_co + 1);
                    else rating += 2;
                }
                //negative diagonal - right
                counter = 0;
                no_co = 0;
                for(int k = 1; k < 4; k++)
                {
                    if(i + k < rows && j + k < columns)
                    {
                        if(array[i + k][j + k] == 1) break;
                        else counter++;
                        if(array[i + k][j + k] == 2) no_co++;
                    }
                }
                if(counter >= 4)
                {
                    if(no_co > 0) rating += pow(2, no_co + 1);
                    else rating += 2;
                }
                //negative diagonal - left
                counter = 0;
                no_co = 0;
                for(int k = 1; k < 4; k++)
                {
                    if(i - k >= 0 && j - k >= 0)
                    {
                    if(array[i - k][j - k] == 1) break;
                    else counter++;
                    if(array[i - k][j - k] == 2) no_co++;
                    }
                }
                if(counter >= 4)
                {
                    if(no_co > 0) rating += pow(2, no_co + 1);
                    else rating += 2;
                }
            }
            //for player
            if(array[i][j] == 1)
            {
                //vertical
                for(int k = 1; k < 4; k++)
                {
                    if(i - k >= 0)
                    {
                        if(array[i - k][j] == 2) break;
                        else counter++;
                        if(array[i - k][j] == 1) no_co++;
                    }
                }
                if(counter >= 4)
                {
                    if(no_co > 0) rating += pow(2, no_co + 1);
                }
                //horizontal - right
                counter = 0;
                no_co = 0;
                for(int k = 1; k < 4; k++)
                {
                    if(j + k < columns)
                    {
                        if(array[i][j + k] == 2) break;
                        else counter++;
                        if(array[i][j + k] == 1) no_co++;
                    }
                }
                if(counter >= 4)
                {
                    if(no_co > 0) rating += pow(2, no_co + 1);
                    else rating += 2;
                }
                //horitzontal - left
                counter = 0;
                no_co = 0;
                for(int k = 1; k < 4; k++)
                {
                    if(j - k >= 0)
                    {
                        if(array[i][j - k] == 2) break;
                        else counter++;
                        if(array[i][j - k] == 1) no_co++;
                    }
                }
                if(counter >= 4)
                {
                    if(no_co > 0) rating += pow(2, no_co + 1);
                    else rating += 2;
                }
                //negative diagonal - right
                counter = 0;
                no_co = 0;
                for(int k = 1; k < 4; k++)
                {
                    if(i + k < rows && j + k < columns)
                    {
                        if(array[i + k][j + k] == 2) break;
                        else counter++;
                        if(array[i + k][j + k] == 1) no_co++;
                    }
                }
                if(counter >= 4)
                {
                    if(no_co > 0) rating += pow(2, no_co + 1);
                    else rating += 2;
                }
                //negative diagonal - left
                counter = 0;
                no_co = 0;
                for(int k = 1; k < 4; k++)
                {
                    if(i - k >= 0 && j - k >= 0)
                    {
                        if(array[i - k][j - k] == 2) break;
                        else counter++;
                        if(array[i - k][j - k] == 1) no_co++;
                    }
                    
                }
                if(counter >= 4)
                {
                    if(no_co > 0) rating += pow(2, no_co + 1);
                    else rating += 2;
                }
            }
            
        }
    }
    
    return rating;
}
