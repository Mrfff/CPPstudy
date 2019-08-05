#pragma once
#include"Cache.h"

#include<vector>

using namespace std;

namespace wd
{
class Cache;
class CacheManager
{
public:
    CacheManager(const string &);
    ~CacheManager();
    void initCache(size_t);
    Cache &getCache(size_t);
    void periodicUpdateCache();
private:
    vector<Cache> _cacheNum;
    string _filename;
};



}//end of wd
