#include <iostream>
#include<vector>
#include<map>
#include<fstream>
#include<string>
#include<unordered_map>
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::unordered_map;
class WordNum
{
public:
    void readFile(const char *file);
    //void store(const char *file);
    void display();
private:
    unordered_map<string,int> _words;
};

void WordNum::readFile(const char* filename)
{
    std::ifstream fd(filename);
    if(!fd.good())
    {   
        cout<<"open file error"<<endl;
        return;
    }
    string word;
    while(fd>>word)
    {
        _words[word]++;

    }
}
void WordNum::display()
{
    unordered_map<string ,int>::const_iterator it;
    for(it=_words.begin();it!=_words.end();++it)
    {
        cout<<"|"<<it->first<<"        |"<<it->second<<endl;
    }
    
}
int main()
{
    WordNum pf;
    pf.readFile("china_daily.txt");
    pf.display();
    return 0;
}

