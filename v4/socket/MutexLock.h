#pragma once
#include"Noncopyable.h"

#include<stdio.h>
#include<errno.h>
#include<pthread.h>

#include<iostream>
using std::cout;
using std::endl;

namespace wd{
class MutexLock
: public Noncopyable
{
public:
    MutexLock()
    :_isLocking(false)
    {
        if(pthread_mutex_init(&_mutex,nullptr))
        {
            perror("pthread_mutex_init");
        }
    }

    void lock()
    {
        if(pthread_mutex_lock(&_mutex))
        {
            perror("pthread_mutex_lock");
        }
        _isLocking=true;
    }

    void unlock()
    {
        if(pthread_mutex_unlock(&_mutex))
        {
            perror("pthread_mutex_unlock");
        }
        _isLocking=false;
    }

    bool isLocking()const
    {
        return _isLocking;
    }

    pthread_mutex_t *getMutexLock()
    {
        return &_mutex; 
    }
    

    ~MutexLock() 
    {
        if(pthread_mutex_destroy(&_mutex))
        {
            perror(">> pthread_mutex_destroy sucess");
        }
    }

private:
    pthread_mutex_t _mutex;
    bool _isLocking;
};

class AutoMutexLock
{
public:
    AutoMutexLock(MutexLock &mutex)
    :_mutex(mutex)
    {
        _mutex.lock();
    }

    ~AutoMutexLock()
    {
        _mutex.unlock();
    }

private:
    MutexLock &_mutex;

};



}//end of namespace
