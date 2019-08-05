#include"../include/dictproducer.h"
#include"../include/configuration.h"
#include"../include/cppjieba/include/cppjieba/Jieba.hpp"

#include<cstring>
#include<algorithm>
#include<fstream>
#include<sstream>
#include<memory>
#include <iostream>
using namespace std;

const char* const DICT_PATH = "../include/cppjieba/dict/jieba.dict.utf8";
const char* const HMM_PATH = "../include/cppjieba/dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "../include/cppjieba/dict/user.dict.utf8";
const char* const IDF_PATH = "../include/cppjieba/dict/idf.utf8";
const char* const STOP_WORD_PATH = "../include/cppjieba/dict/stop_words.utf8";

namespace wd
{
Dictproducer::Dictproducer(){cout<<"Dictproducer"<<endl;}

void Dictproducer::get_path()
{
    multimap<string,string> tmp;
    tmp=Configuration::getInstance()->getConfigMap();
    auto it=tmp.begin();
    for(;it!=tmp.end();++it)
    {
        if(!strcmp(it->first.c_str(),"e_original_data"))
        {
            _englishfiles.push_back(it->second);
        }
        else if(!strcmp(it->first.c_str(),"cn_original_data"))
        {
            _chinesefiles.push_back(it->second);
        }
        else if(!strcmp(it->first.c_str(),"store_path"))
        {
            _storeDataPath=it->second;
        }
    }
    for(auto &elem:_englishfiles)
    {
        cout<<"_englishfiles "<<elem<<endl;
    }
    for(auto &elem:_chinesefiles)
    {
        cout<<"_chinesefiles "<<elem<<endl;
    }
}

void Dictproducer::build_cn_dict()
{
    auto it=_chinesefiles.begin();
    for(;it!=_chinesefiles.end();++it)
    {
        fstream fd(*it);
        fstream storepath(_storeDataPath+"cndict.txt",ofstream::out);
        string line;
        vector<string> cutWord;//剪切单词
        cppjieba::Jieba jieba(DICT_PATH,HMM_PATH,USER_DICT_PATH,IDF_PATH,STOP_WORD_PATH);
        while(getline(fd,line))
        {
            
            replace_if(line.begin(),line.end(),static_cast<int(*)(int)>(&ispunct),' ');
            replace_if(line.begin(),line.end(),static_cast<int(*)(int)>(&isdigit),' ');
            jieba.Cut(line,cutWord,true);
            for(auto &word:cutWord)
            {
                if(word.size()==1){continue;}
                _cndict[word]++;
            }
        }

        for(auto &elem:_cndict)
        {
            storepath<<elem.first<<" "<< elem.second<<endl;
        }
        
    }
}

void Dictproducer::build_dict()//创建英文词典
{
    auto it=_englishfiles.begin();
    for(;it!=_englishfiles.end();++it)
    {
    fstream fd(*it);
    fstream storePath(_storeDataPath+"englishdict.txt",ofstream::out);
    string line;
    string word;
    while(getline(fd,line))
    {
        stringstream os;
        replace_if(line.begin(),line.end(),static_cast<int(*)(int)>(&ispunct),' ');
        transform(line.begin(),line.end(),line.begin(),::tolower);
        replace_if(line.begin(),line.end(),static_cast<int(*)(int)>(&isdigit),' ');
        os<<line;
        while(os>>word)
        {
            _englishdict[word]++;
            
        }
    
    
    }
    for(auto &elem:_englishdict)
    {
        storePath<<elem.first<<"  "<<elem.second<<endl;
    }
    }
    

}


}//end of wd


