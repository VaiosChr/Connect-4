#ifndef player_hpp
#define player_hpp

#include <string>

using namespace std;

class Player
{
private:
    int id;
    string name;
    bool is_ai{false};
    
public:
    Player(int id, string name, bool is_ai = false)
    {
        this->id = id;
        this->name = name;
        this->is_ai = is_ai;
    }
    
    int get_id()
    {
        return id;
    }
    
    string get_name()
    {
        return name;
    }
    
    bool get_is_ai()
    {
        return is_ai;
    }
    
    int move()
    {
        int col;

        cin >> col;
        
        return col - 1;
    }
};

#endif /* player_hpp */
