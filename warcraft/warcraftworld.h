#include <iostream>
#include"warcraft.h"
#include"warcraftHead.h"
namespace warcraft
{
class WarrcraftWorld
{
public:
    explicit
    WarrcraftWorld()
    :_redHeadquarters(nullptr)
    ,_blueHeadquarters(nullptr)
    {init();}
    
    void start()
    {
        while(1)
        {
            createWarrior();
            if(!warriorMarch())
            {
                break;
            }
            cityProduceElements();
            takeCityElements();
            battle();
            headquartersReportElements();
        }
    }
    
template<typename Iterator>
void setRedWarriorCreatingOrder(Iterator beg,Iterator end);

template<typename Iterator>
void setBlueWarriorCreatingOrder(Iterator beg,Iterator end);

~WarrcraftWorld()
{
    if(_redHeadquarters) 
    { delete _redHeadquarters;}
    if(_blueHeadquarters) 
    {delete _blueHeadquarters;}
}

private:
    void init();
    //-------------------begin--------------------
    void createWarrior();//整点创建武士
    bool warriorMarch();//武士行进
    void cityProduceElements();//城市产生生命元
    void takeCityElements();//创建武士的生命源
    void battle();//战斗
    void headquartersReportElements();//50min司令部报告情况
    //-------------------end----------------------
    
    bool createWarrior(Headquarters *);//创建武士
    void warriorMarch(Headquarters *headquarters);
    bool checkRedHeadquartersBeTaken();//红方是否被占领
    bool checkBlueHeadquartersBeTanke();//蓝方是否被占领


private:
    Headquarters *_redHeadquarters;
    Headquarters *_blueHeadquarters;
    vector<City> _cities;

};

template<typename Iterator>
void WarrcraftWorld::setRedWarriorCreatingOrder(Iterator beg,Iterator end)
{
    return _redHeadquarters->setWarriorCreatingOrder(beg,end);
}

template<typename Iterator>
void WarrcraftWorld::setBlueWarriorCreatingOrder(Iterator beg,Iterator end)
{
    return _blueHeadquarters->setWarriorCreatingOrder(beg,end);
}


}//end of warcraft

