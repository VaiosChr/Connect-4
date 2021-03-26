#ifndef board_hpp
#define board_hpp

#include <iostream>
#include <vector>

#include "player.hpp"

using namespace std;

class Board
{
private:
    int rows{0}, columns{0};
    vector<vector<string>> board;
    
public:
    Board(int rows, int columns);
    
    void print();
    
    bool play(Player player);
    
    bool wins(int id);
    
    string get_char(int i, int j);
        
    bool is_full();
    
    bool ai_play(Player player);
    
    float minmax(Player player, vector<vector<int>> check_board, int depth, bool maximizing_player);
    
    float evaluation(vector<vector<int>> array);
};

#endif /* board_hpp */
