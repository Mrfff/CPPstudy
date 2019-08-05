#include <iostream>
#include<vector>
#include<map>
#include<fstream>
#include<string>
#include<set>
#include<algorithm>
#include<ctype.h>
#include<sstream>
using std::set;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::multimap;
using std::pair;
using std::stringstream;
class TextQuery
{
public:
    void readFile(const char *file);
    void wordFind(const string & word);
    void display();
private:
    map<string,set<int>> _words;
    map<int,string> _line;
    multimap<string,int> _tmp;
    int _lineNum=0;
};

void TextQuery::readFile(const char* filename)
{
    std::ifstream fd(filename);
    if(!fd.good())
    {   
        cout<<"open file error"<<endl;
        return;
    }
    string line;
     //map<string,int> tmp;
    //int tmpNum=0;
    while(getline(fd,line))
    {
        _line[++_lineNum]=line;
        //tmp=_line;
        stringstream ltw;//让每一行的单词分别单独存储
        //line.erase(remove_if(line.begin(),line.end(),static_cast<int(*)(int)>(&ispunct)),line.end());
        replace_if(line.begin(),line.end(),static_cast<int(*)(int)>(&ispunct),' ');
        //tmp[++tmpNum]=line;
        ltw<<line;
        string word;
        while(ltw>>word)
        {
            _tmp.insert(make_pair(word,_lineNum));
        }
       // while()
    }
        //tmp=_line;
        for(auto &e:_line)
        {
            cout<<e.first<<" "<<e.second<<endl;
        }
        for(auto &e:_tmp)
        {
            cout<<e.first<<" "<<e.second<<endl;
        }
        //stringstream ltw;//让每一行的单词分别单独存储
        //tmp.erase(remove_if(tmp.begin(),tmp.end(),static_cast<int(*)(int)>(&ispunct)),tmp.end());
        //while()
}
#if 1 
void TextQuery::wordFind(const string &word)
{
    auto tmpIt1=_tmp.lower_bound(word);
    auto tmpIt2=_tmp.upper_bound(word);
    if(tmpIt1!=_tmp.end()){
    while(tmpIt1!=tmpIt2)
    {
        //cout<<"find success"<<tmpIt1->first<<"->"<<tmpIt1->second<<endl;
        //_words.insert(make_pair(word,tmpIt1->second));
        cout<<"line("<<tmpIt1->second<<")"<<_line[tmpIt1->second]<<endl;
        ++tmpIt1;
    }
    }else{cout<<"find error"<<endl;}
    for(auto &e:_words)
    {
        cout<<e.first<<" "<<endl;
    }
}
#endif
#if 0
void TextQuery::display()
{
    map<string ,int>::const_iterator it;
    for(it=_words.begin();it!=_words.end();++it)
    {
        cout<<"|"<<it->first<<"        |"<<it->second<<endl;
    }
    
}
#endif
int main()
{
    TextQuery pf;
    pf.readFile("china_daily.txt");
    pf.wordFind("with");
    //pf.display();
    return 0;
}

