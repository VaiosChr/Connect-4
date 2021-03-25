#ifndef player_hpp
#define player_hpp

#include <string>

using namespace std;

class Player
{
private:
    int id;
    string name;
    
public:
    Player(int id, string name)
    {
        this->id = id;
        this->name = name;
    }
    
    int get_id()
    {
        return id;
    }
    
    string get_name()
    {
        return name;
    }
};

#endif /* player_hpp */
