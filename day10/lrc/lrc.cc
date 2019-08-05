#include <iostream>
#include<list>
#include<utility>
#include<unordered_map>
using std::unordered_map;
using std::cout;
using std::endl;
using std::list;
using std::pair;
class LruCache
{
public:
    LruCache(int capacity)
    :_size(capacity)
    {}
    int get(int key)
    {
        auto it=_hash.find(key);
        if(it==_hash.end())
        {
            return -1;
        }
        _cache.splice(_cache.begin(),_cache,it->second);//把找到的链表提前
        return it->second->second;
    }
    void put(int key,int value)
    {   
        auto it=_hash.find(key);
        if(it!=_hash.end())
        {
            it->second->second=value;
            return _cache.splice(_cache.begin(),_cache,it->second);//把找到的链表提前
        }
        //_cache.push_front(key,value);
        _cache.insert(_cache.begin(), std::make_pair(key, value));
        _hash[key]=_cache.begin();//放到前项

        if(_cache.size() > _size)
        {
            _hash.erase(_cache.back().first);
            _cache.pop_back();
        }
        
    }
    ~LruCache(){};
private:
    unordered_map<int ,list<pair<int,int>>::iterator> _hash;
    list<pair<int,int>> _cache;
    size_t _size;
};
int main()
{
    LruCache cache(2);
    cache.put(1,1);
    cache.put(2,2);
    cout<<cache.get(2)<<endl;
    cache.put(3,3);
    cache.put(4,4);
    cout<<cache.get(2)<<endl;
    cout<<cache.get(4)<<endl;
    return 0;
}

