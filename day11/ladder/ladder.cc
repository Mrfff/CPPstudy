#include <iostream>
#include<vector>
#include<string>
#include<unordered_set>
#include<queue>
#include<algorithm>
using namespace std;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) 
    {
        int cnt=count(wordList.begin(),wordList.end(),endWord);
        if(cnt==0){return 0;}
        unordered_set<string> words(wordList.begin(),wordList.end());
        unordered_set<string> visited;
        queue<string> curQue;
        queue<string> nextQue;
        int len =1;
        curQue.push(beginWord);
        visited.insert(beginWord);
        while(!curQue.empty())
        {
        while(!curQue.empty())
        {
            string word=curQue.front();
            curQue.pop();
            vector<string> nextStat;
            getNext(word,words,visited,nextStat);
            for(auto &stat:nextStat)
            {
                nextQue.push(stat);
                if(stat==endWord)
                {
                    return len+1;
                }
                visited.insert(stat);
            }
            
        }
        ++len;
        swap(curQue,nextQue);
        }
    return 0;
    }
    void getNext(const string &word,const unordered_set<string> &words,
                 const unordered_set<string> &visited,vector<string> &result)
    {
        for(auto &condition:words)
        if(isValue(word,condition))
        {
            int cnt=visited.count(condition);
            if(0==cnt)
            {
                result.push_back(condition);
            }

        }

    }
    bool isValue(const string &word,const string &condition)
    {
        int cnt=0;
        for(size_t i=0;i!=word.end();++i)
        {
            if(word[i]!=condition[i])
            ++i;
        }
    }
    
};
int main()
{
    std::cout << "Hello world" << std::endl;
    return 0;
}

