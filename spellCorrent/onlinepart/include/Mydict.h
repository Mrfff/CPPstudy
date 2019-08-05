#pragma once
#include<map>
#include<string>
#include<vector>
#include<set>


using namespace std;

namespace wd
{
class Mydict
{
public:
    static Mydict *getInstance()
    {
        if(_pInstance==nullptr)
        {
            _pInstance=new Mydict();
        }
        return _pInstance;
    }
    void init(const string &);
    vector<pair<string,int>>&getDict();
    map<string ,set<int>>&getIndexTable();


private:
    Mydict() {}
    ~Mydict() {}

private:
    vector<pair<string,int>> _dict;
    map<string ,set<int>> _index_table;
    string _cndictpath;
    string _endictpath;
    string _cnindexpath;
    string _enindexpath;
    static Mydict * _pInstance;
};


}//end of wd
