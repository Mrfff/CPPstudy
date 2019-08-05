#pragma once
#include"../include/configuration.h"
#include"../include/dictproducer.h" 
#include"../include/IndexProducer.h"

#include <iostream>
using namespace std;
using namespace wd;
int main()
{
    Configuration::getInstance()->confPath("../conf/dict.conf");
    cout<<Configuration::getInstance()->filePath()<<endl; 
    multimap<string,string> tmp;
    tmp=Configuration::getInstance()->getConfigMap();
    Dictproducer dic;
    dic.get_path();
    string s=dic.getstorePath();
    cout<<"get the store test"<<s<<endl;
    dic.build_dict();
    dic.build_cn_dict();
    IndexProducer index; 
    index.getIndexProducer();
    index.getCNIndexProducer();
    cout<<"text end"<<endl;
    return 0;
}

