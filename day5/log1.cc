#include<log4cpp/Category.hh>
#include<log4cpp/Priority.hh>
#include<log4cpp/OstreamAppender.hh>
#include<log4cpp/RollingFileAppender.hh>
#include<log4cpp/FileAppender.hh>
#include<log4cpp/PatternLayout.hh>
#include <iostream>
using namespace log4cpp;
using std::cout;
using std::endl;
int main()
{
    PatternLayout *ptnLayout1 =new PatternLayout();
    //设置输出格式
    ptnLayout1->setConversionPattern("%d [%p] %m%n");
    PatternLayout *ptnLayout2 =new PatternLayout();
    ptnLayout2->setConversionPattern("%d [%p] %m%n");
    PatternLayout *ptnLayout3 =new PatternLayout();
    ptnLayout3->setConversionPattern("%d [%p] %m%n");
    //创建新的输出流
    OstreamAppender *ostreamAppender=new OstreamAppender("osAppender",&cout);
    ostreamAppender->setLayout(ptnLayout1);
     
    FileAppender * fileAppender=new FileAppender("FileAppenderfileAppender","myLog.1");
    fileAppender->setLayout(ptnLayout2);
    RollingFileAppender * rollingFileAppender=new RollingFileAppender("RollingfileAppender"
                                            ,"rolingMyLog"
                                            ,256,2);
    rollingFileAppender->setLayout(ptnLayout3);
    //设置日志记录器
    Category &root = Category::getRoot();
    root.setAppender(ostreamAppender);
    root.setAppender(fileAppender);
    root.setAppender(rollingFileAppender);
    //可以让不同用户查看不同的日志
    root.setPriority(Priority::DEBUG);

    root.alert("alter masage");
    root.crit("crit message");
    root.debug("error massage");
    root.emerg("emerg massage");
    root.info("info massage");
    root.fatal("fatal massage");
    root.warn("warn massage");
    
    Category::shutdown();
    return 0;
}

