/*
 * File Name: soft_interrupt.c
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Sun 24 Mar 2019 08:48:01 PM CST
 */

#include "softinterrupt.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef void(*Func)(void);

typedef struct interrupt {
    unsigned int prio;
    Func proc;
    struct interrupt* next;
} Interrupt;

static Interrupt soft_interrupt_table[100];
static Interrupt task_queue;
static unsigned int current_prio = 32;


int SwiCreate(unsigned int swiId, unsigned int prio, void(* proc)( void )) {
    if(swiId > 99 || prio > 31 || !proc) {
        return -1;
    }
    if(soft_interrupt_table[swiId].proc) {
        return -1;
    }
    soft_interrupt_table[swiId].prio = prio;
    soft_interrupt_table[swiId].proc = proc;

    return 0;
}

int SwiActivate(unsigned int swiId) {
    Func proc = soft_interrupt_table[swiId].proc;
    unsigned int prio = soft_interrupt_table[swiId].prio;
    unsigned int restore = current_prio;
    Interrupt *tmp, *new_node;

    // check
    if(!proc) {
        return -1;
    }

    if(prio >= current_prio) {
        // create Interrupt task and insert to task_queue
        printf("insert %u\n", prio);
        new_node = (Interrupt*)malloc(sizeof(Interrupt));
        new_node->prio = prio;
        new_node->proc = proc;
        new_node->next = NULL;

        tmp = &task_queue;
        while(tmp->next && tmp->next->prio <= prio) {
            tmp = tmp->next;
        }
        new_node->next = tmp->next;
        tmp->next = new_node;
        return 0;
    }

    // high prio preempt
    current_prio = prio;
    proc();
    current_prio = restore;

scheduler:
    tmp = &task_queue;
    if(tmp->next && tmp->next->prio < current_prio) {
        new_node = tmp->next;
        tmp->next = tmp->next->next;

        current_prio = new_node->prio;
        new_node->proc();
        current_prio = restore;

        free(new_node);
        goto scheduler;
    }

    return 0;
}

void Clear(void) {
    Interrupt *tmp;

    if(current_prio != 32) {
        return;
    }

    memset(soft_interrupt_table, 0, sizeof(soft_interrupt_table));
    tmp = &task_queue;
    while(tmp->next) {
        Interrupt* new_node = tmp->next;
        tmp->next = tmp->next->next;
        printf("free %u\n", new_node->prio);
        free(new_node);
    }
}
