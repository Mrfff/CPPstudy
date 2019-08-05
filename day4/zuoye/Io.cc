#include <iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<vector>
#include<fstream>
#include<sstream>
using std::cout;
using std::endl;
using std::string;
using std::fstream;
using std::vector;
using std::ofstream;
using std::istream;
using std::cin;
using std::istringstream;
using std::ostringstream;
using std::stringstream;
struct Store
{
    string word;
    int num;
};
class Dicitonary
{
public:
   // Dicitonary(const char *file)
    //{
     //   strcpy(_filename,file);
    //}

    void read(const string&filename);
    void store (const string &filename);
private:
    char _filename[128]={0};
    vector<Store> _store; 
};
void Dicitonary::read(const string&filename)
{
    fstream fd(filename);
    string line;
    cout<<"waiting open"<<endl;
    if(!fd.good())
    {
        cout<<" open "<<filename<<"error"<<endl;
        return ;
    }
    cout<<"open ok"<<endl;
    while(getline(fd,line))
    {
        stringstream isw;
        isw<<line;
        string word;
        while(isw>>word)
        {
            vector<Store>::iterator file;
            for(file=_store.begin();file!=_store.end();file++)
            {
                if(word==file->word)
                {
                    file->num++;
                    break;
                }

            }
                if(file==_store.end())
                {
                    Store record;
                    record.word=word;
                    record.num=1;
                    _store.push_back(record);
                }

        }
    }
    fd.close();
}
void Dicitonary::store (const string&filename)
{
    ofstream ofd(filename);
    string line;
    if(!ofd.good())
    {
        cout<<"open error"<<endl;
    }
    vector<Store>::iterator record;
    for(record=_store.begin();record!=_store.end();record++)
    {
        ofd<<"| "<<record->word<<" "<<record->num<<" |"<<endl;
        
    }
    ofd.close();

}
int main()
{
    string filePath;
    //char path[128]={0};
    cout<<"请输入统计文件的路径"<<endl;
    cin>>filePath;
    Dicitonary dic;
    dic.read(filePath);
    dic.store("theWordNum.txt");
    cout<<"success"<<endl;
    return 0;
}

