#include"warcraft.h"
#include<iostream>

namespace warcraft
{
class City
{
public:
    City();

private:
    Color _flag;//旗子颜色
    size_t _id;//城市编号
    size_t _elements;//城市的生命元
    size_t _readWinCount;
    size_t _blueWinCount;
    vector<WarriorPtr> _readWarriors;
    vector<WarriorPtr> _blueWarriors;

};




}//end of warcraft
