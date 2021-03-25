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
    
    bool wins(Player player);
    
    string get_char(int i, int j);
    
    bool is_full();
    
    bool ai_play(Player player);
};

#endif /* board_hpp */
