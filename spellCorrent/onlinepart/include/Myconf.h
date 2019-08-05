#pragma once
#include<string>
#include<map>
#include<fstream>
#include<iostream>


using namespace std;
namespace wd
{

class Myconf
{
public:
    static Myconf *getInstance(const string &filename)
    {
        if(_pInstance==nullptr)
        {
            _pInstance=new Myconf(filename);
        }
        return _pInstance;
    }
    
    string getIp();
    unsigned short getPort();
    size_t getThreadNum();
    size_t getQuesize();
    string getCndicpath();
    string getEndicpath();
    string getCnindex();
    string getEnindex();

private:
    Myconf(const string &);
    ~Myconf()
    {
        if(_pInstance)
        {
            delete _pInstance;
        }
    }
private:
    static Myconf *_pInstance;
    map<string,string> _conf;
};



}//end of wd
