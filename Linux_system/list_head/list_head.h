/*
 * File Name: list_head.h
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Thu 13 Apr 2017 08:12:24 PM CST
 */

#ifndef __LIST_HEAD_H__
#define __LIST_HEAD_H__

struct list_head {
    struct list_head *next, *prev;
};

#define list_entry(ptr, type, member) container_of(ptr, type, member)
#define offsetof(TYPE, MEMBER) ((size_t)&((TYPE *)0)->MEMBER)
#define container_of(ptr, type, member) ({ \
    const typeof( ((type *)0)->member) *__mptr = (ptr); \
    (type *)((char *)__mptr - offsetof(type, member)); \
        })

#define list_for_each(pos, head) \
    for(pos=(head)->next; pos!=(head); pos=pos->next)

#define LIST_HEAD(name) \
    struct list_head name = LIST_HEAD_INIT(name)


#endif /* __LIST_HEAD_H__ */
