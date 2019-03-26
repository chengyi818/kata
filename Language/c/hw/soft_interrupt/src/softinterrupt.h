/*
 * File Name: soft_interrupt.h
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Sun 24 Mar 2019 08:55:18 PM CST
 */

#ifndef __SOFT_INTERRUPT_H__
#define __SOFT_INTERRUPT_H__

int SwiCreate(unsigned int swiId, unsigned int prio, void(* proc)( void ));
int SwiActivate(unsigned int swiId);
void Clear(void);

#endif /* __SOFT_INTERRUPT_H__ */
