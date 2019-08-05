#include <iostream>
#include"warcraft.h"
namespace warcraft
{
class Headquarters
{
public:
    Headquarters(Color color,size_t elements)
        :_color(color)
        ,_elements(elements)
        ,_earnElements(0)
        ,_nextWarriorIndex(0)
    {}

    virtual ~Headquarters(){}

    WarriorPtr create();//创建武士

    void addWinner(WarriorPtr warrior);
    void reward();//奖励胜利者
    void increaseElements(size_t elements)//城市获取的生命元 
    {
        _earnElements+=elements;
    }
    void setElments(size_t elements)//设置剩余生命元
    {
         _elements=elements;
    }

    template<typename Iterator>
    void setWarriorCreatingOrder(Iterator beg,Iterator end)
    {
        for(;beg!=end;++beg)
        {
            _warriorCreatingOrder.push_back(*beg);
        }
    }

private:
    WarriorPtr creatIceman(size_t id,size_t hp,size_t forces);
    WarriorPtr creatLion(size_t id,size_t hp,size_t forces);
    WarriorPtr creatWolf(size_t id,size_t hp,size_t forces);
    WarriorPtr creatNinja(size_t id,size_t hp,size_t forces);
    WarriorPtr creatDragon(size_t id,size_t hp,size_t forces);
    
    void nextWarriorType();

    WarriorType getNextWarriorType()
    {
        return _warriorCreatingOrder[_nextWarriorIndex];
    }

protected:
    Color _color;//红蓝
    size_t _id;//编号，0代表红色司令部，N+1代表蓝色司令部
    size_t _elements;//当前司令部剩余生命元
    size_t _earnElements;//战斗后武士获取的生命元
    size_t _nextWarriorIndex;//下一次生产武士的下标
    vector<WarriorType>_warriorCreatingOrder;//武士产生的顺序

    priority_queue<WarriorPtr,vector<WarriorPtr>,WarriorComparator> _winners;//获胜的队列

    unordered_map<WarriorType,size_t>_warriorTypeAmounts;

};

class RedHeadquarters
:public Headquarters
{
public:RedHeadquarters(size_t elements)
       :Headquarters(RED,elements){}
};

class BluedHeadquarters
:public Headquarters
{
public:BluedHeadquarters(size_t elements)
       :Headquarters(BLUE,elements){}
};


}//end of warcraft


