#include"../include/WorkTask.h"
#include"../include/Mydict.h"
#include"../include/json/json.h"
namespace  wd
{
WorkTask::WorkTask(const string &queryWord,TcpConnectionPtr &conn)
:_queryWord(queryWord)
,_conn(conn)
{cout<<"WorkTask"<<endl;}

void WorkTask::execute()
{
    cout<<_queryWord<<endl;
    queryIndexTable();//调用就运行
    cout<<"2"<<endl;
    string resultJson=resulttoJson();
    _conn->sendInloop(resultJson);
}


void WorkTask::queryIndexTable()
{
    auto indextable=Mydict::getInstance()->getIndexTable();
    set<int> iset;//存储候选词
#if 0
    auto  it=_queryWord.begin();
    for(;it!=_queryWord.end();++it)
    {
        auto p=indextable.find(string(1,*it));
        cout<<p->first<<endl;
        for(auto it2=p->second.begin();it2!=p->second.end();++it2)
        {
            iset.insert(*it2);
        }
    }
#endif

#if 1 
    for(size_t i=0;i!=_queryWord.size();)
    {
        char itword=_queryWord[i];
        size_t nbytes=nByterCode(itword);
        std::string strword = _queryWord.substr(i,nbytes);
        //cout<< strword <<endl;
        //cout<< _queryWord.size() <<endl;
        auto psearch=indextable.find(_queryWord.substr(i,nbytes));
        //cout << "single world"<< endl;
        if(psearch != indextable.end())
        {
        cout<<_queryWord.substr(i,nbytes)<<endl;
        for(auto it=psearch->second.begin();it!=psearch->second.end();++it)
        {
            iset.insert(*it);
            //cout<<*it<<endl;
        } 
        }
        i+=nbytes;
    }
#endif

#if 0 
    for(auto &elem:iset)
    {
        cout<<elem<<" ";
    }
    cout<<endl;
#endif
    statistic(iset);

}

void WorkTask::statistic(set<int> &iset)//从索引获取单词
{
    //cout << "123"<<endl;
    MyResult result;
    cout<<"static beging"<<endl;
    auto dictable=Mydict::getInstance()->getDict();
    auto it=iset.begin();//单词的行号
    for(;it!=iset.end();++it)
    {
        int num = *it-1;
        //cout<<*it<<endl;
        
        result._word=dictable[num].first;
        //cout << *it << endl;
        //cout<<result._word<<endl;
        result._iFreq=dictable[num].second;
        cout<<result._iFreq<<endl;
        //result._iDist=distance(dictable[*it].first);
        result._iDist=distance(result._word);
        cout<<result._iDist<<endl;
        //if(distance(result._word)<3)
        //{
        _resultQue.push(result);//放入优先级队列

        //}
    } 

}

int WorkTask::distance(const string&rhs)
{
    size_t lhs_len=length(_queryWord);
    size_t rhs_len=length(rhs);
    int editDist[lhs_len+1][rhs_len+1];
    for(size_t i=0;i<=lhs_len;++i)
    {
        editDist[i][0]=i;
    }
    for(size_t i=0;i<=rhs_len;++i)
    {
        editDist[0][i]=i;
    }
    string sublhs,subrhs;
    for(size_t dist_i=1,lhs_i=0;dist_i<=lhs_len;++dist_i,++lhs_i)
    {
        size_t nBytes=nByterCode(_queryWord[lhs_i]);
        sublhs =_queryWord.substr(lhs_i,nBytes);
        lhs_i+=(nBytes-1);
        for(size_t dist_j=1,rhs_i=0;dist_j<=rhs_len;++dist_j,++rhs_i)
        {
            nBytes=nByterCode(rhs[rhs_i]);
            subrhs=rhs.substr(rhs_i,nBytes);
            rhs_i+=(nBytes-1);
            if(sublhs ==subrhs)
            {
                editDist[dist_i][dist_j]=editDist[dist_i-1][dist_j-1];
            }
            else
            {
                editDist[dist_i][dist_j]=triple_min(editDist[dist_i][dist_j-1]+1,
                                                    editDist[dist_i-1][dist_j]+1,
                                                    editDist[dist_i-1][dist_j-1]+1);
            }
        }
    }
    //cout<<"the distance::::::"<<editDist[lhs_len][rhs_len]<<endl;
    return editDist[lhs_len][rhs_len];
}

int WorkTask::triple_min(const int &a,const int &b,const int&c)
{
    return a<b?(a<c?a:c):(b<c?b:c);
}

size_t WorkTask::length(const string &str)
{
    size_t ilen=0;
    for(size_t i=0;i!=str.size();++i)
    {
        int nBytes=nByterCode(str[i]);
        i+=(nBytes-1);
        ++ilen;
    }
    return ilen;

}

size_t WorkTask::nByterCode(char ch)
{
    if(ch&(1<<7))
    {
        int nBytes=1;
        for(int i=0;i!=6;++i)
        {
            if(ch&(1<<(6-i)))
            {
                ++nBytes;
            }else 
            {
                break;
            }
        }
        return nBytes;
    }
    return 1;

}

string WorkTask::resulttoJson()
{
    Json::FastWriter dog;
    Json::Value root;   
    Json::FastWriter fawrite;
    int retNum=0;
    while(retNum<5)
    {
        MyResult temp=_resultQue.top();
        cout<<temp._word<<" "<<temp._iFreq<<"  "<<temp._iDist<<endl;
        _resultQue.pop();
        Json::Value sendValue;
        sendValue["_word"]=temp._word;
        sendValue["_frequent"]=temp._iFreq;
        root["sendValue"].append(sendValue);
        ++retNum;
    }
    return dog.write(root);
}

}//end of wd


