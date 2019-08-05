#include"../include/dictproducer.h"
#include"../include/IndexProducer.h"

#include<fstream>
#include<sstream>
#include<unordered_map>
#include<algorithm>
#include <iostream>
#include<string>
using namespace std;
namespace wd
{

void IndexProducer::readDircn(const string &dirName)
{
   string readPath="../data/storedir/";
   cout<<readPath<<endl;
   fstream fd;
   fd.open(readPath+dirName);
   if(fd.badbit){perror("fdread");}
   int num=1;
   string line;
   while(getline(fd,line))
   {
        replace_if(line.begin(),line.end(),static_cast<int(*)(int)>(&isdigit),' ');
        stringstream words(line);  
        string word;
        words>>word;
        _readDir.push_back(make_pair(word,num));
        ++num;
   }
}
void IndexProducer::readDiren(const string &dirName)
{
   string readPath="../data/storedir/";
   cout<<readPath<<endl;
   fstream fd;
   fd.open(readPath+dirName);
   if(fd.badbit){perror("fdread");}
   int num=1;
   string line;
   while(getline(fd,line))
   {
        replace_if(line.begin(),line.end(),static_cast<int(*)(int)>(&isdigit),' ');
        stringstream words(line);  
        string word;
        words>>word;
        _readDir.push_back(make_pair(word,num));
        ++num;
   }
}

void IndexProducer::getCNIndexProducer()
{
    readDircn("cndict.txt");
    auto itreaddir=_readDir.begin();
    for(;itreaddir!=_readDir.end();++itreaddir)
    {
        //auto itchbeg=itreaddir->first.begin();//每一个词语的第一个字
        string substring=itreaddir->first;
        //size_t sublen=iLength(substring);
        for(size_t i=0;i!=substring.size();)//获得字符
        {
            char itWord=substring[i];
            size_t nbytes=nByterCode(itWord);
            _indexDir[substring.substr(i,i+nbytes)].insert(itreaddir->second);
            i+=nbytes;
        }
        
    }
    storeIndex("cnIndexdic.txt");
}


void IndexProducer::getIndexProducer()
{
    readDiren("englishdict.txt");
    
    auto itreaddir=_readDir.begin();
    for(;itreaddir!=_readDir.end();++itreaddir)
    {
        auto itchbeg=itreaddir->first.begin();//每一个单词的字母
        auto itchend=itreaddir->first.end();
        for(;itchbeg!=itchend;++itchbeg)
        {
            _indexDir[string(1,*itchbeg)].insert(itreaddir->second);
        }
        
    }
    storeIndex("eIndexdic.txt");
}

void IndexProducer::storeIndex(const string&filename)
{
    string storepath="../data/storedir/";
    cout<<storepath<<endl;
    fstream fd;
    fd.open(storepath+filename,ofstream::out);
    if(fd.badbit){perror("fdopen");}
    for(auto &elem:_indexDir)
    {
        fd<<elem.first<<" ";
        for(auto &elemNum:elem.second)
        {
            fd<<elemNum<<" ";
        }
        fd<<endl;
    }
}

size_t IndexProducer::nByterCode(char ch)
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

size_t IndexProducer::iLength(const string&istr)
{
    size_t ilen=0;
    for(size_t i=0;i!=istr.size();++i)
    {
        int nBytes=nByterCode(istr[i]);
        i+=(nBytes-1);
        ++ilen;
    }
    return ilen;
}


}//end of wd

