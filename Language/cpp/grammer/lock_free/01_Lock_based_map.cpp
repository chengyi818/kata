/*
 * File Name: 01_Lock_based_map.cpp
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Thu 21 Mar 2019 03:16:18 PM CST
 */


#include <map>
#include <mutex>

template <typename K, typename V>
class LockMap {
private:
    std::map<K, V> map_;
    std::mutex mutex_;

public:
    V LookUp(K& key) {
        std::lock_guard<std::mutex> lock(mutex_);
        return map_[key];
    }

    void Update(K& key, V& val) {
        std::lock_guard<std::mutex> lock(mutex_);
        map_[key] = val;
    }
};
