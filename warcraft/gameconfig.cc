#include <iostream>
#include"warcraft.h"

using namespace warcraft;

namespace warcraft
{
class GameConfig
{
public:
    static GameConfig *getInstance()
    {
        if(_pinstance==nullptr)
        {
            _pinstance=new GameConfig();
        }
        return _pinstance;
    }

    static void destroy()
    {
        if(_pinstance)
        delete _pinstance;
    };

    void readFromConsole();//从控制台获取测试数据
    void readFromFile(const string &filename);//从配置文件获取数据
    void nextGoupId(){++_currentGroupId;}//测试下一组数据
    size_t groups()const {return _groups.size();}
    size_t currentGroupId()const{return _currentGroupId;}
    size_t cityCount()const{return _groups[_currentGroupId]._cityCount;}
    size_t headquartersInitialElements()const{return _groups[_currentGroupId]._initElements;}//生命元
    size_t warriorInitalLiffe(WarriorType key)const
    {
        return _groups[_currentGroupId]._initLifes.at(key);
    }
    size_t warriorInitalAttack(WarriorType key)const
    {
        return _groups[_currentGroupId]._initAttacks.at(key);

    }
    void print();

private:
    GameConfig()
    :_currentGroupId(0)
    {
        cout<<"GameConfig"<<endl;
    }
    ~GameConfig()
    {
        cout<<"~GameConfig"<<endl;
    }
    void readFromStream(istream &is);
    struct InitData
    {
        size_t _initElements;
        size_t _cityCount;
        size_t _minutes;
        map<WarriorType,size_t> _initLifes;
        map<WarriorType,size_t> _initAttacks;
    };

private:
        static GameConfig* _pinstance;
        vector<InitData> _groups;
        size_t _currentGroupId;
        vector<WarriorType> _initwarriorOrder;//输入武士的生命值和攻击力顺序
};

void GameConfig::readFromFile(const string &filename)
{
    ifstream fd(filename);
    if(!fd)
    {
        cout<<"open error"<<endl;
    }
    size_t totaltestNum;
    size_t testNum;
    InitData getStructData;
    string line;
    //map<size_t,vector<WarriorType,size_t>> group;
    getline(fd,line);
    cout<<"get sucess"<<endl;
    istringstream word(line);
    word>>totaltestNum;
        for(size_t i=0;i<totaltestNum;++i)
        {
        getline(fd,line);
        istringstream elem(line);//第一行数据
        elem>>testNum;
        getStructData._initElements=testNum;
        elem>>testNum;
        getStructData._cityCount=testNum;
        elem>>testNum;
        getStructData._minutes=testNum;
        
        getline(fd,line);
        istringstream life(line);
       life>>testNum;
        getStructData._initLifes[DRAGON_TYPE]=testNum;
       life>>testNum;
        getStructData._initLifes[NINJA_TYPE]=testNum;
       life>>testNum;
        getStructData._initLifes[ICEMAN_TYPE]=testNum;
       life>>testNum;
        getStructData._initLifes[LION_TYPE]=testNum;
       life>>testNum;
        getStructData._initLifes[WOLF_TYPE]=testNum;
    
        getline(fd,line);
        istringstream act(line);
        act>>testNum;
        getStructData._initAttacks[DRAGON_TYPE]=testNum;
        act>>testNum;
        getStructData._initAttacks[NINJA_TYPE]=testNum;
        act>>testNum;
        getStructData._initAttacks[ICEMAN_TYPE]=testNum;
        act>>testNum;
        getStructData._initAttacks[LION_TYPE]=testNum;
        act>>testNum;
        getStructData._initAttacks[WOLF_TYPE]=testNum;
        
        }
        _groups.push_back(getStructData);


}
GameConfig *GameConfig::_pinstance=nullptr;

size_t GameConfig::warriorInitalAttack(WarriorType key)const
{
    return _groups[_currentGroupId]->_initLifes[key];
}
void GameConfig::print()
{
    cout<<_groups[0]._cityCount<<endl;
    cout<<_groups[0]._minutes<<endl;
    cout<<_groups[0]._initElements<<endl;
    cout<<_groups[0]._initAttacks[DRAGON_TYPE]<<endl;
    cout<<_groups[0]._initAttacks[NINJA_TYPE]<<endl;
    cout<<_groups[0]._initAttacks[ICEMAN_TYPE]<<endl;
    cout<<_groups[0]._initAttacks[LION_TYPE]<<endl;
    cout<<_groups[0]._initAttacks[WOLF_TYPE]<<endl;
    cout<<_groups[0]._initLifes[DRAGON_TYPE]<<endl;
    cout<<_groups[0]._initLifes[WOLF_TYPE]<<endl;
    cout<<_groups[0]._initLifes[ICEMAN_TYPE]<<endl;
    cout<<_groups[0]._initLifes[LION_TYPE]<<endl;
    cout<<_groups[0]._initLifes[WOLF_TYPE]<<endl;
    
}

}//end of name spacewarcraft

#if 0
int main()
{
    GameConfig::getInstance()->readFromFile("warcraft.conf");
    GameConfig::getInstance()->print(); 
    return 0;
}
#endif
