#include "GraphList.h"

int main(void) {
    char vexs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    char edges[][2] = {
        {'A', 'B'},
        {'B', 'C'},
        {'B', 'E'},
        {'B', 'F'},
        {'C', 'E'},
        {'D', 'C'},
        {'E', 'B'},
        {'E', 'D'},
        {'F', 'G'},
    };
    int vlen = sizeof(vexs)/sizeof(vexs[0]);
    int elen = sizeof(edges)/sizeof(edges[0]);
    ListDG *pDG;

    //手动输入
    //pDG = new ListDG();
    //采用已有的图
    pDG = new ListDG(vexs, vlen, edges, elen);
    pDG->print();

    return 0;
}
