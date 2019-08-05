#include"../include/Thread.h"
#include"../include/Tcpserver.h"
#include"../include/Threadpool.h"
#include"../include/TaskQueue.h"
#include"../include/TcpConnection.h"
#include"../include/WorkTask.h"
#include"../include/Spellserver.h"
#include"../include/Myconf.h"
#include"../include/MutexLock.h"
#include"../include/MyResult.h"
#include"../include/Mydict.h"

#include <iostream>

using namespace wd;
using namespace std;
int main()
{
    Spellserver startServer("../conf/server.conf");
    //Myconf::getInstance("../conf/server.conf");
    Mydict::getInstance()->init("../conf/server.conf");
    startServer.start();
    return 0;
}

