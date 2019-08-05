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
    template<class ... Args>
    void warn(Args... args)
        {
            osLog.setAppender(ostreamAppender);
            osLog.setAppender(fileAppender);
            osLog.setPriority(Priority::DEBUG);
            osLog.warn(args...);
        }
    void warn(const char *msg)
    {
        osLog.setAppender(ostreamAppender);
        osLog.setAppender(fileAppender);
        osLog.setPriority(Priority::DEBUG);
        osLog.warn(msg);
    };
    template<class ... Args>
    void error(Args... args)
        {
            osLog.setAppender(ostreamAppender);
            osLog.setAppender(fileAppender);
            osLog.setPriority(Priority::DEBUG);
            osLog.error(args...);
        }
    void error(const char *msg)
    {

        osLog.setAppender(ostreamAppender);
        osLog.setAppender(fileAppender);
        osLog.setPriority(Priority::DEBUG);
        osLog.error(msg);
    };
    template<class ... Args>
    void debug(Args... args)
        {
            osLog.setAppender(ostreamAppender);
            osLog.setAppender(fileAppender);
            osLog.setPriority(Priority::DEBUG);
            osLog.debug(args...);
        }
    void debug(const char *msg)
    {

        osLog.setAppender(ostreamAppender);
        osLog.setAppender(fileAppender);
        osLog.setPriority(Priority::DEBUG);
        osLog.debug(msg);
    };
    template<class ... Args>
    void info(Args... args)
        {
            osLog.setAppender(ostreamAppender);
            osLog.setAppender(fileAppender);
            osLog.setPriority(Priority::DEBUG);
            osLog.info(args...);
        }
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
         //fileLog(Category::getRoot())
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

#define LogInfo(msg,...) Mylog::pGet()->info(FUNC(msg),##__VA_ARGS__)
#define LogWarn(msg,...) Mylog::pGet()->warn(FUNC(msg),##__VA_ARGS__)
#define LogError(msg,...) Mylog::pGet()->error(FUNC(msg),##__VA_ARGS__)
#define LogDebug(msg,...) Mylog::pGet()->debug(FUNC(msg),##__VA_ARGS__)

int main()
{
    Mylog::pGet()->warn(FUNC("warn massage"));
    Mylog::pGet()->error(FUNC("error massage"));
    Mylog::pGet()->debug(FUNC("debug massage"));

   // Mylog::pGet()->info(FUNC("info massage,number =%d"),number);
    int number = 100; 
    const char * pstr = "hello, log4cpp";
    LogInfo("this is an info message. number = %d, str = %s\n", number, pstr);
    LogError("this is an info message. number = %d, str = %s\n", number, pstr);
    LogWarn("this is an info message. number = %d, str = %s\n", number, pstr);
    LogDebug("this is an info message. number = %d, str = %s\n", number, pstr);
    Mylog::destroy();
    return 0;
}

