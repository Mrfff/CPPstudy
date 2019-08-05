#pragma once

#include<string>
#include<vector>
#include<map>
#include<unordered_map>
#include<set>

using namespace std;

namespace wd
{
class IndexProducer
{
public:
    IndexProducer(){}
    void getIndexProducer();
    void storeIndex(const string &);
    void getCNIndexProducer();
    size_t nByterCode(const char ch);
    size_t iLength(const string &);
private:
    void readDiren(const string &dirName);
    void readDircn(const string &dirName);

private:
    vector<pair<string,int>> _readDir;
    unordered_map<string,set<int>> _indexDir;

};



}//end of wd
