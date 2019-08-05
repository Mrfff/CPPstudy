#include"../include/Cache.h"
#include <iostream>
#include<fstream>
#include<sstream>

using namespace std;

namespace wd
{

Cache::Cache(int num)
:_capicity(num)
{}
void Cache::addElement(const string &key,const string &value)
{
    if(isHashMap(key))
    {
        if(_hashMap.size()==_capicity)
        {
            auto itEndElem=_cachelist.back()._key;
            _hashMap.erase(itEndElem);
            _cachelist.pop_back();
        }
        _cachelist.push_front(CacheNode(key,value));
        _hashMap.insert(make_pair(key,_cachelist.begin()));

    }

    else
    {
        auto it=_hashMap.find(key);
        it->second->_value=value;//哈希表中的Cachelist的value更新
        _cachelist.splice(_cachelist.begin(),_cachelist,it->second);//把找到的链表位置放到首部
        _hashMap[key]=_cachelist.begin();//更新hashMap中的节点位置
    }

}


bool Cache::isHashMap(const string &key)
{
    auto it=_hashMap.find(key);
    if(it==_hashMap.end())
    {
        return false;
    }
    return true;
}

void Cache::readFromFile(const string &filename)
{
    fstream fd(filename);
    if(fd.badbit)
    {
        perror("fd read from file ");
    }
    string line;
    while(getline(fd,line))
    {
        stringstream words(line);
        string key,value;
        words>>key;
        words>>value;
        CacheNode Node(key,value);
        _cachelist.push_back(Node);
        _hashMap.insert(make_pair(key,_cachelist.begin()));
    }

}

void Cache::writeTofile(const string &filename)
{
    fstream fd;
    fd.open(filename,fstream::out);
    if(fd.badbit)
    {
        perror("fd writetofile");
    }
    
    auto it=_cachelist.begin();
    for(;it!=_cachelist.end();++it)
    {
        fd<<it->_key<<" "<<it->_value<<endl;
    }
    fd.close();
}

void Cache::update(const Cache& cache)//访问到就改变其顺序
{
    for(auto &elem:cache._hashMap)
    {
        if(_hashMap.find(elem.first)==_hashMap.end())
        {
            _hashMap.insert(move(elem));            
        }
    }
    
}


}//end of wd

