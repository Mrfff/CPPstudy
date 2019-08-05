#pragma once
#include"warcraft.h"
namespace warcraft{

class City
{
public:
    City(size_t id,size_t elements=0)
    :_flag(Color::NOTSET)
    ,_id(id)
    ,_elements(elements)
    ,_redWinCount(0)
    ,_blueWinCount(0)
    {}
    
    void produceElements();
    void attach(WarriorPtr);
    void detach(WarriorPtr);
    void startBattle();//开始战斗
    void takenBy(WarriorPtr warrior);//生命元被取走

    size_t getId()const {return _id;}
    Color getFlag()const {return _flag;}
    size_t getWarriorAmount()const{return _redWarriors.size()+_blueWarriors.size();}
    vector<WarriorPtr> &getRedWarriors(){return _redWarriors;}
    vector<WarriorPtr> &getBlueWarriors(){return _blueWarriors;}


private:
Color _flag;
size_t _id;
size_t _elements;
size_t _redWinCount;
size_t _blueWinCount;
vector<WarriorPtr> _redWarriors;
vector <WarriorPtr> _blueWarriors;
};




}//end of namespace
