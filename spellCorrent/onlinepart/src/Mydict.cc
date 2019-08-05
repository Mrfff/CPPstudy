#include"../include/Mydict.h"
#include"../include/Myconf.h"

#include<sstream>
#include<algorithm>
using namespace std;
namespace wd
{
Mydict *Mydict::_pInstance=nullptr;
void Mydict::init(const string &filename)
{
    _cndictpath=Myconf::getInstance(filename)->getCndicpath();
    _endictpath=Myconf::getInstance(filename)->getEndicpath();
    _cnindexpath=Myconf::getInstance(filename)->getCnindex();
    _enindexpath=Myconf::getInstance(filename)->getEnindex();
}

vector<pair<string,int>>& Mydict::getDict()
{
    fstream fd1(_cndictpath);
    fstream fd2(_endictpath);
    if(fd1.badbit)
    {
        perror("Mydict get dict");
    }
    if(fd2.badbit)
    {
        perror("Mydict get dict");
    }
    string line;
    while(getline(fd1,line))
    {
        stringstream word(line);
        string dic;
        int num;
        word>>dic;
        word>>num;
        _dict.push_back(make_pair(dic,num));
    } 
    while(getline(fd2,line))
    {
        stringstream word(line);
        string dic;
        int num;
        word>>dic;
        word>>num;
        _dict.push_back(make_pair(dic,num));
    } 
    return _dict;

}

map<string,set<int>>& Mydict::getIndexTable()
{
    fstream fd1(_cnindexpath);
    fstream fd2(_enindexpath);
    if(fd1.badbit)
    {
        perror("Mydict get index");
    }
    if(fd2.badbit)
    {
        perror("Mydict get index");
    }
    string line;
    while(getline(fd1,line))
    {
        stringstream word(line);
        string key;
        int num;
        word>>key;
        while(word>>num)
        {
            _index_table[key].insert(num);
        }
        
    }
    while(getline(fd2,line))
    {
        stringstream word(line);
        string key;
        int num;
        word>>key;
        while(word>>num)
        {
            _index_table[key].insert(num);
        }
        
    }
    return _index_table;


}



}//end of wd

