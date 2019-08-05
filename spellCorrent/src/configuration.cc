#include"../include/configuration.h"

#include<fstream>
#include<sstream>
#include <iostream>
using namespace std;
namespace wd
{
Configuration * Configuration::_pInstance = nullptr;
void Configuration::confPath(const string &filepath)
{
    _filepath=filepath;
}

multimap<string,string> &Configuration::getConfigMap()
{
    ifstream fd(_filepath);
    if(fd.failbit)
    {
        perror("fd");
    }
    string line;
    while(getline(fd,line))
    {
    istringstream word(line);
    string dataPath;
    string dataType;
    word>>dataType;
    word>>dataPath;
    _configMap.insert(make_pair(dataType,dataPath));
    }
    for(auto &data:_configMap)
    {
        cout<<data.first<<"---->"<<data.second<<endl;
    }
    return _configMap;
}


}//end of configuration 

