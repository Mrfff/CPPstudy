#pragma once
#include<map>
#include<string>
using std::string;
using std::multimap;

namespace wd
{
class Configuration
{
public:

    static Configuration *getInstance()
    {
        if(_pInstance==nullptr)
        {
            _pInstance=new Configuration();
        }
        return _pInstance;
    }
    void confPath(const string &filepath);
    multimap<string,string> &getConfigMap();
    string filePath()const{return _filepath;}
private:
    Configuration(){}
    ~Configuration(){}

private:
    static Configuration * _pInstance;
    string _filepath;
    multimap<string,string> _configMap;
};

}//end of namespace
