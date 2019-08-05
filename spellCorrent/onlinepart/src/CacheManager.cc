#include"../include/CacheManager.h"
#include"../include/MutexLock.h"
#include"../include/timefd.h"
#include"../include/timeThread.h"

#include <iostream>

namespace wd
{
CacheManager::CacheManager(const string &filename)
:_filename(filename)
{
    initCache(20);
}

void CacheManager::initCache(size_t cacheNum)
{
    _cacheNum.reserve(cacheNum);
    Cache tmp(cacheNum);
    tmp.readFromFile(_filename);
    for(size_t i=0;i<cacheNum;++i)
    {
        _cacheNum.push_back(tmp);
    }
    
}

Cache &CacheManager::getCache(size_t i)
{
    return _cacheNum[i];
}

void CacheManager::periodicUpdateCache()
{
    auto it=_cacheNum.begin();
    Cache newCache=*(it++);
    for(;it!=_cacheNum.end();++it)
    {
        newCache.update(*it);
    }
    for(auto it =_cacheNum.begin()+1;it!=_cacheNum.end();++it)
    {
        (*it).update(newCache);
    }
    newCache.writeTofile(_filename);
} 

}//end of wd

