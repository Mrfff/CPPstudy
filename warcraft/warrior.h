#include <iostream>
#include"warcraft.h"
#include"warcraftHead.h"
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
void setForce(size_t forces){_forces=forces;}
void setHeapquarers(Headquarters *headquarters)
{
     _headquarters=headquarters;
}
Color getColor()const{return _color;}
string getName(){return _name;}
size_t getId()const{return _id;}
size_t getHp()const{return _hp;}
size_t getCityId()const {return _cityId;}
size_t getElements()const {return _hp;}
size_t getEarnElements()const {return _earnElements;}
size_t getForces()const {return _forces;}
WarriorType getType()const {return _type;}
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

class Dragon
:public Warrior
{
public:Dragon(Color color,size_t id,size_t hp,size_t forces
              ,float morale)
       :Warrior(color,"dragon",id,hp,forces,DRAGON_TYPE)
        ,_morale(morale)
    {}
       virtual
           float getMorale()const {return _morale;}

private:
        float _morale;
};

class Ninja
:public Warrior
{
public:Ninja(Color color,size_t id,size_t hp,size_t forces)
       :Warrior(color,"ninja",id,hp,forces,NINJA_TYPE)
    {}
       virtual void defense(WarriorPtr warrior) override;
};

class Iceman
:public Warrior
{
public:Iceman(Color color,size_t id,size_t hp,size_t forces)
       :Warrior(color,"iceman",id,hp,forces,ICEMAN_TYPE)
        ,_steps(0)
    {}
       virtual void march() override;
private:
    size_t _steps;
};

class Lion
:public Warrior
{
public:Lion(Color color,size_t id,size_t hp,size_t forces
            ,size_t loyalty)
       :Warrior(color,"lion",id,hp,forces,LION_TYPE)
        ,_loyalty(loyalty)
    {}
       virtual
        size_t getLoyalty()const{return _loyalty;}

private:
    size_t _loyalty;
};

class Wolf
:public Warrior
{
public:Wolf(Color color,size_t id,size_t hp,size_t forces)
       :Warrior(color,"wolf",id,hp,forces,WOLF_TYPE)
        ,_killTimes(0)
    {}
    virtual void attack(WarriorPtr warrior) override;
private:
    int _killTimes;

};



}//end of namespace

