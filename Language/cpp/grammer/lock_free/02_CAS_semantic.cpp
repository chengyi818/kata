/*
 * File Name: 02_CAS_semantic.cpp
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Thu 21 Mar 2019 03:23:40 PM CST
 */
/*
  1. CAS原语为原子操作
  2. 语言库通常有封装好的CAS函数
 */


template <typename T>
bool CompareAndSwap(T *p, T old_val, T new_val) {
    if(*p == old_val) {
        *p = new_val;
        return true;
    }
    return false;
}
