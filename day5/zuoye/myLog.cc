#include <iostream>
#include<string>
#include<log4cpp/Category.hh>
#include<log4cpp/Priority.hh>
#include<log4cpp/OstreamAppender.hh>
#include<log4cpp/RollingFileAppender.hh>
#include<log4cpp/FileAppender.hh>
#include<log4cpp/PatternLayout.hh>
using namespace log4cpp;
using std::cout;
using std::endl;
using std::string;
class Mylog
{
public:
    void warn(const char *msg)
    {
        osLog.setAppender(ostreamAppender);
        osLog.setAppender(fileAppender);
        osLog.setPriority(Priority::DEBUG);
        osLog.warn(msg);
    };
    void error(const char *msg)
    {

        osLog.setAppender(ostreamAppender);
        osLog.setAppender(fileAppender);
        osLog.setPriority(Priority::DEBUG);
        osLog.error(msg);
    };
    void debug(const char *msg)
    {

        osLog.setAppender(ostreamAppender);
        osLog.setAppender(fileAppender);
        osLog.setPriority(Priority::DEBUG);
        osLog.debug(msg);
    };
    void info(const char *msg)
    {
        osLog.setAppender(ostreamAppender);
        osLog.setAppender(fileAppender);
        osLog.setPriority(Priority::DEBUG);
        osLog.info(msg);

    };
    static Mylog *pGet();
    static void  destroy();
private:
     Mylog()
        :osLog(Category::getRoot())
        //,fileLog(Category::getRoot())
    {
        ostreamLayout=new PatternLayout();
        ostreamLayout->setConversionPattern("%d [%p] %m%n");
        fileLayout=new PatternLayout();
        fileLayout->setConversionPattern("%d [%p] %m%n");
        ostreamAppender=new OstreamAppender("osAppender",&cout);
        fileAppender=new FileAppender("fileAppender","wwf.log");
        cout<<"Mylog()"<<endl;
    };
    ~Mylog()
    {
        Category::shutdown();
        cout<<"~Mylog"<<endl;
    };
private:
    PatternLayout *ostreamLayout;
    PatternLayout *fileLayout;
    OstreamAppender *ostreamAppender;
    FileAppender *fileAppender;
    Category &osLog;
    //Category &fileLog;
    static Mylog *_point;

};
Mylog *Mylog::_point=nullptr;
Mylog *Mylog::pGet()
{
    if(_point==nullptr)
    {
        _point=new Mylog();
    }
    return _point;
}
void Mylog::destroy()
{
    if(_point)
    {
        delete _point;
    }
}
#define FUNC(msg) string("[ ").append(__FILE__" :")\
    .append(std::to_string(__LINE__)).append( __func__)\
    .append(string(" ]")).append(msg).c_str()



int main()
{
    Mylog::pGet()->warn(FUNC("warn massage"));
    Mylog::pGet()->error(FUNC("error massage"));
    Mylog::pGet()->debug(FUNC("debug massage"));
    Mylog::pGet()->info(FUNC("info massage"));
    Mylog::destroy();
    return 0;
}

