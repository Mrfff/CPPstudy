#include <iostream>
#include"warcraft.h"
using namespace warcraft;
namespace warcraft
{

class Warrior
:public enable_shared_from_this<Warrior>
{
public:
    Warrior(Color color,
            const string &name,
            size_t id,
            size_t hp,
            size_t forces,
            WarriorType type)
        :_color(color)
        ,_name(name)
        ,_id(id)
        ,_hp(hp)
        ,_forces(forces)
        ,_type(type){}
virtual ~Warrior(){}
virtual void march();//行军
virtual void attack(WarriorPtr warrior);//攻击其他武士
virtual void defense(WarriorPtr warrior);//反击其他武士

void beWinner();//成为赢家
void beRewarded();//被奖励
void sentElementsToheadquarters(size_t elements);//为基地获取生命元

void setHp(size_t hp){_hp=hp;}
void setCity(size_t id){_id=id;}
void setHeapquarers(Head);
protected:
    Color _color;
    string _name;
    size_t _id;//编号
    size_t _hp;//生命值
    size_t _forces;//攻击力
    size_t _cityId;//城市ID
    size_t _earnElements;//在城市中获取的生命元
    WarriorType _type;
    Headquarters *_headquarters;

};

}//end of namespace

