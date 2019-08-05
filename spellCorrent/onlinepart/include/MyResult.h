#pragma once
#include<string>

using namespace std;

class MyResult
{
public:
    string _word;//候选词
    int _iFreq;//词频
    int _iDist;//查询的最小距离
    
};

class Mycompare
{
public:
    bool operator()(const MyResult &a ,const MyResult &b) 
    {
        if(a._iDist==b._iDist)
        {
            return a._iFreq<b._iFreq;
        }
        else 
        {
            return a._iDist>b._iDist;
        }


    }

};

