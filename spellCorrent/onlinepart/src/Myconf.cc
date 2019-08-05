#include"../include/Myconf.h"

#include<string.h>

#include <iostream>
#include<sstream>
using namespace std;
namespace wd
{
Myconf *Myconf::_pInstance=nullptr;
Myconf::Myconf(const string &filename)
{
    fstream fd(filename);
    if(fd.badbit)
    {
        perror("Myconf openfd");
    }
    
    string line;
    while(getline(fd,line))
    {
        stringstream word(line); 
        string type;
        string data;
        word>>type;
        word>>data;
        _conf.insert(make_pair(type,data));
    }

}
string Myconf::getIp()
{
    string ip;
    for(auto it=_conf.begin();it!=_conf.end();++it)
    {
        if(!strcmp(it->first.c_str(),"ip"))
        {
            ip=it->second;
            return ip;
        }

    }
    return 0;
}

unsigned short Myconf::getPort()
{
    unsigned short port;
    for(auto it=_conf.begin();it!=_conf.end();++it)
    {
        if(!strcmp(it->first.c_str(),"port"))
        {
            port=atoi((char*)it->second.c_str());
            return port;
        }
    }
    return 0;
}

size_t Myconf::getThreadNum()
{
    size_t threadnum;
    for(auto it=_conf.begin();it!=_conf.end();++it)
    {
        if(!strcmp(it->first.c_str(),"threadnum"))
        {
            threadnum=stoul(it->second);
            return threadnum;
        }

    }
    return 0;
}
size_t Myconf::getQuesize()
{
    size_t quesize;
    for(auto it=_conf.begin();it!=_conf.end();++it)
    {
        if(!strcmp(it->first.c_str(),"quesize"))
        {
            quesize=stoul(it->second);
            return quesize;
        }

    }
    return 0;
    
}

string Myconf::getEnindex()
{
    string indexenpath;
    for(auto it=_conf.begin();it!=_conf.end();++it)
    {
        if(!strcmp(it->first.c_str(),"indexEnpath"))
        {
            indexenpath=it->second;
            cout<<"index sucess >>"<<indexenpath<<endl;
            return indexenpath;
        }

    }
    return 0;
}
string Myconf::getEndicpath()
{
    string dictenpath;
    for(auto it=_conf.begin();it!=_conf.end();++it)
    {
        if(!strcmp(it->first.c_str(),"dictEnpath"))
        {
            dictenpath=it->second;
            cout<<"dictenpath>> "<<dictenpath<<endl;
            return dictenpath;
        }

    }
    return 0;

}
string Myconf::getCnindex()
{
    string indexcnpath;
    for(auto it=_conf.begin();it!=_conf.end();++it)
    {
        if(!strcmp(it->first.c_str(),"indexCnpath"))
        {
            indexcnpath=it->second;
            return indexcnpath;
        }

    }
    return 0;

}
string Myconf::getCndicpath()
{
    string dictcnpath;
    for(auto it=_conf.begin();it!=_conf.end();++it)
    {
        if(!strcmp(it->first.c_str(),"dictCnpath"))
        {
            dictcnpath=it->second;
            return dictcnpath;
        }

    }
    return 0;

}


}//end of wd

