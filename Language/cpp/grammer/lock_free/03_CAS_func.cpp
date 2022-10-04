/*
 * File Name: 03_CAS_func.cpp
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Thu 21 Mar 2019 03:26:04 PM CST
 */

// x86 assemble
CMPXCHG

// for gcc
bool __sync_bool_compare_and_swap(type *ptr, type oldval, type newval, ...);
type __sync_val_compare_and_swap(type *ptr, type oldval, type newval, ...);

// for Microsoft
long InterlockedCompareExchange(long* pointer, long desired, long expected);

// for C++11
template <typename T>
bool atomic_compare_exchange(T* pointer, T* expected, T desired);
