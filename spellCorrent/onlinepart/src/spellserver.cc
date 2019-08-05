#include"../include/Spellserver.h"
#include"../include/WorkTask.h"
namespace wd
{

Spellserver::Spellserver(const string &cfgFileName)
:_tcpserver(Myconf::getInstance(cfgFileName)->getIp(),Myconf::getInstance(cfgFileName)->getPort())
,_threadpool(Myconf::getInstance(cfgFileName)->getThreadNum(),Myconf::getInstance(cfgFileName)->getQuesize())
{
    cout<<"Spellserver init sucess"<<endl;    
}

void Spellserver::start()
{
    _threadpool.start();
    _tcpserver.setConnectionCallback(bind(&Spellserver::onConnection,this,std::placeholders:: _1));
    _tcpserver.setMessaageCallback(bind(&Spellserver::onMessage,this,std::placeholders:: _1));
    _tcpserver.setCloseCallback(bind(&Spellserver::onClose,this,std::placeholders:: _1));
    _tcpserver.start();


}

void Spellserver::onConnection(TcpConnectionPtr conn)
{
    cout<<conn->toSting()<<endl;
    conn->send("welcome to server!");
}

void Spellserver::onMessage(TcpConnectionPtr conn)
{
    string recvMsg=conn->receive();
    cout<<"receive MSG: "<<recvMsg<<endl;
    WorkTask task(recvMsg,conn);
    cout<<"init ok"<<endl;
    _threadpool.addTask(bind(&WorkTask::execute,task));
}

void Spellserver::onClose(TcpConnectionPtr conn)
{
    cout<<">> "<<conn->toSting()<<" has closed "<<endl;
}





}//end of wd

