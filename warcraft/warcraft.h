#pragma once
#include<string>
#include<ostream>
#include<vector>
#include<map>
#include<algorithm>
#include<fstream>
#include<sstream>
#include<memory>
#include<unordered_map>
#include<queue>
#include<unordered_set>
//#include"warcity.h"
//#include"warrior.h"
//#include"warcraftworld.h"
//#include"warcraftHead.h"
class warrior;
class Headquarters;
class City;
using namespace std;
using WarriorPtr=shared_ptr<warrior>;

namespace warcraft{
enum Color
{
    RED,
    BLUE,
    NOTSET
};

enum WarriorType
{
    DRAGON_TYPE,
    NINJA_TYPE,
    ICEMAN_TYPE,
    LION_TYPE,
    WOLF_TYPE

};

inline string toString(Color color)
{
    return (color==RED)?string ("red"):string ("blue");

}

inline string toString(WarriorType warrior)//通过类型得到字符串
{
    switch(warrior)
    {
case DRAGON_TYPE: return "dragon";
case NINJA_TYPE: return "ninja";
case ICEMAN_TYPE: return "iceman";
case LION_TYPE: return "lion";
case WOLF_TYPE: return "wolf";
default:
    string();
    }
}
}//end of namespace
