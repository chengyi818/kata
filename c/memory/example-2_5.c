/* @filename: example_2_5.c */

demo()
{
    char *p;

    //分配了100Kbytes线性地址
    if ((p = malloc(1024*100)) != NULL)  // L0
    {
        *p = ‘t’;     // L1
        //过去了很长一段时间，不管系统忙否，长久不用的页框都有可能被回收
        *p = ‘m’;      // L2
        p[4096] = ‘p’;   // L3
        /*…*/
        free(p);  //L4

        if (p == NULL)
        {
            *p = ‘l’; // L5
        }
    }
}
