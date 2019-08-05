#include<iostream>
#include "warcraft.h"
using namespace warcraft;

namespace warcraft
{
class GameTime
{
public:
    static GameTime*getInstance()
    {
        if(_pinstance==nullptr)
        {
            _pinstance=new GameTime();
        }
        return _pinstance;
    }
    static void destroy()
    {
        if(_pinstance)
        {
            delete _pinstance;
            
        }
    };

    void showTime()const; //打印时间
    void updataTime();//更新时间
    void reset(){_hour=0;_minute=0;}
private:
    GameTime(size_t hour=0,size_t minute=0)
    :_hour(hour)
    ,_minute(minute){cout<<"GameTime()"<<endl;}
private:
    static GameTime* _pinstance;
    size_t _hour;
    size_t _minute;

};

void GameTime::updataTime()
{

    _minute+=10;
    if(_minute==60)
    {
        _hour++;
        _minute=0;
    }

}
void GameTime::showTime()const
{
    cout<<_hour<<":"<<_minute<<endl;
}
GameTime *GameTime::_pinstance=nullptr;



}//end of namespace

int main()
{
    for(int i=0;i!=100;++i)
    {
        GameTime::getInstance()->showTime();
        GameTime::getInstance()->updataTime();
    }
}

