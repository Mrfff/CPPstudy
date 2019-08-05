#pragma once
#include<string>
#include<map>
#include<vector>
using std::vector;
using std::string;
using std::map;

namespace wd
{
class Dictproducer
{
public:
    Dictproducer();
    void get_path();
    void build_dict();
    void store_dict(const char *filepath);
    void show_files()const ;
    void show_dict()const;
    void build_cn_dict();
    string getstorePath() 
    {
        return _storeDataPath;
    } 
private:
    void get_files();
    void push_dict(const string&word);
    
private:
    //string _dir;
    vector<string> _englishfiles;//英文语料库
    vector<string> _chinesefiles;//中文语料库
    string _storeDataPath;//词典的存储路径
    map<string,int> _englishdict;
    map<string,int> _cndict;
    //splitTool *_splittool;

};


}//end of wd
