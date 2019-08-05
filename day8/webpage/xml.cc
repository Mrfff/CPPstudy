#include <iostream>
#include<string>
#include"tinyxml2.h"
#include<vector>
#include<string.h>
#include<regex.h>
using std::vector;
using std::cout;
using std::endl;
using std::string;
using namespace tinyxml2;
struct RssItem
{
    string title;//标题
    string link;//链接
    string description;//描述
    string content;//内容
};
class RssReader
{
public:
    RssReader(const char *filename)
    :_filename(new char[strlen(filename)+1]())
    {
        strcpy(_filename,filename);
        //XMLDocument doc;
        //doc.LoadFile(filename.c_str());
        //XMLElement *info = doc.RootElement();//获取根节点
        cout<<"RssInit OK"<<endl;
    };
    ~RssReader()
    {
        delete []_filename;
        cout<<"~RssReader() sucess"<<endl;
    }
    void parseRss()
    {
        XMLDocument doc;
        doc.LoadFile(_filename);
        XMLElement *info = doc.RootElement();//获取根节点
        const char *title=info->FirstChildElement("title")->GetText();
        const char *link=info->FirstChildElement("link")->GetText();
        const char *description=info->FirstChildElement("description")->GetText();
        const char *content=info->FirstChildElement("content")->GetText();

        
    };
    void dump (const string & filename);
private:
    vector<RssItem> _rss;
    char *_filename;
};
int main()
{
    std::cout << "Hello world" << std::endl;
    return 0;
}

