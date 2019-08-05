#pragma once
#include<unordered_map>
#include<list>

using namespace std;
namespace wd
{
class Cache
{
public:
    struct CacheNode
    {
        CacheNode(const string &key,const string&value)
        :_key(key)
        ,_value(value){}
        
        string _key;
        string _value;

    };

    Cache(int );
    ~Cache() {} 
    void addElement(const string &key,const string& value);
    void readFromFile(const string &);
    void writeTofile(const string &);
    void update(const Cache&);
    bool isHashMap(const string &);
    

private:
    unordered_map<string,list<CacheNode>::iterator> _hashMap;
    size_t _capicity;
    list<CacheNode> _cachelist;
};




}//end of wd
