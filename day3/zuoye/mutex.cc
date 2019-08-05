#include <iostream>
#include<pthread.h>
#include<unistd.h>
using std::cout;
using std::endl;

class MutexLock
{
public:
    MutexLock()
    {
        pthread_mutex_init(&_mutex,NULL);
    }
    ~MutexLock()
    {
        pthread_mutex_destroy(&_mutex);
    }
    void lock()
    {
        pthread_mutex_lock(&_mutex);
    }
    void unlock()
    {
        pthread_mutex_unlock(&_mutex);
    }
    pthread_mutex_t* getMutexPoint()
    {
        return &_mutex;
    }

private:
    MutexLock(const MutexLock &rhs);
    MutexLock &operator=(const MutexLock &rhs);
private:
    pthread_mutex_t _mutex;
};
class Cond
{
public:
    Cond(MutexLock &mutex)
    :_mutex(mutex)
    {
        pthread_cond_init(&_cond,NULL);
    };
    void wait()
    {
        pthread_cond_wait(&_cond,_mutex.getMutexPoint());

    }
    void notify()
    {
        pthread_cond_signal(&_cond);
    };
    void notifyall()
    {
        pthread_cond_broadcast(&_cond);
    };
private:
    pthread_cond_t _cond;
    MutexLock &_mutex;
};
int main()
{
    MutexLock mutex;
    Cond c(mutex);
    mutex.lock();
    c.wait();
    std::cout << "Hello world" << std::endl;
    mutex.unlock();
    return 0;
}

