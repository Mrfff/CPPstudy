#pragma once
#include"Spellserver.h"
#include"MyResult.h"

#include<queue>
#include<set>

using namespace std;
namespace wd
{

class WorkTask
{
public:
    WorkTask(const string &,TcpConnectionPtr&);
    ~WorkTask() {}
    void execute();
    
private:
    size_t nByterCode(char);
    size_t length(const string &);
    int triple_min(const int&,const int&,const int&);
    void queryIndexTable();
    void statistic(set<int> &iset);
    int distance(const string &rhs);
    void response();
    string resulttoJson();
private:
    string _queryWord;
    int _peerfd;
    TcpConnectionPtr _conn;
    priority_queue<MyResult,vector<MyResult>,Mycompare> _resultQue;
};




}//end of wd
