/*
 * File Name: 04_Lock_free_map.cpp
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Thu 21 Mar 2019 03:27:21 PM CST
 */

/*
  1. 没有实现内存释放
 */


#define CAS(val, oldval, newval)                            \
    __sync_bool_compare_and_swap((val), (oldval), (newval))


template <typename K, typename V>
class LockFreeMap {
private:
    std::map<K, V> *pMap_;

public:
    V LookUp(K &key) {
        return pMap_[key];
    }

    void Update(K &key, V& val) {
        std::map<K, V> pNewMap = nullptr;
        std::map<K, V> pOldMap = nullptr;
        do {
            pOldMap = pMap_;
            if (pNewMap != nullptr) {
                delete pNewMap;
            }
            pNewMap = new std::map<K, V>(*pOldMap);
            pNewMap[key] = val;
        } while( CAS(&pMap_, pOldMap, pNewMap) );
    }
};
