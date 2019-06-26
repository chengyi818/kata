/*
 * File Name: main.c
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Wed 26 Jun 2019 02:24:30 PM CST
 */

#define _GNU_SOURCE
#include <link.h>
#include <stdlib.h>
#include <stdio.h>

static int
callback(struct dl_phdr_info *info, size_t size, void *data)
{
    int j;

    printf("name=%s (%d segments)\n", info->dlpi_name,
           info->dlpi_phnum);

    for (j = 0; j < info->dlpi_phnum; j++)
        printf("\t\t header %2d: address=%10p\n", j,
               (void *) (info->dlpi_addr + info->dlpi_phdr[j].p_vaddr));
    return 0;
}

int
main(int argc, char *argv[])
{
    dl_iterate_phdr(callback, NULL);

    exit(EXIT_SUCCESS);
}
