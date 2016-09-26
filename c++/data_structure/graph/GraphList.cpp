#include "GraphList.h"

/*
 *创建邻接表(手动输入)
 */
ListDG::ListDG() {
    char c1, c2;
    /*int v, e;*/
    int i, p1, p2;
    ENode *node1;
    /*ENode *node2;*/

    //输入"顶点数"和"边数"
    cout << "input vertex number: ";
    cin >> mVexNum;
    cout << "input edge number: ";
    cin >> mEdgNum;

    //检查输入
    if(mVexNum < 1 || mEdgNum < 1 || (mEdgNum > (mVexNum * (mVexNum-1)))) {
        cout << "input error: invalid parameters!" << endl;
        return;
    }

    //初始化"邻接表"顶点
    for (i = 0; i < mVexNum; ++i) {
        cout << "vertex(" << i << "):";
        mVexs[i].data = readChar();
        mVexs[i].firstEdge = NULL;
    }

    //初始化"邻接表"的边
    for (i = 0; i < mEdgNum; ++i) {
        //读取边的起始顶点和结束顶点
        cout << "edge(" << i << "): ";
        c1 = readChar();
        c2 = readChar();

        p1 = getPosition(c1);
        p2 = getPosition(c2);
        //初始化node1
        node1 = new ENode();
        node1->ivex = p2;
        //将node1链接到"p1所在链表的末尾"
        if(mVexs[p1].firstEdge == NULL)
            mVexs[p1].firstEdge = node1;
        else
            linkLast(mVexs[p1].firstEdge, node1);
       }
}

/*
 *创建邻接表对应的图(矩阵)
 */
ListDG::ListDG(char vexs[], int vlen, char edges[][2], int elen) {
    char c1, c2;
    int i, p1, p2;
    ENode *node1;

    //初始化"顶点数"和"边数"
    mVexNum = vlen;
    mEdgNum = elen;
    //初始化"邻接表"的顶点
    for (i = 0; i < mVexNum; ++i) {
        mVexs[i].data = vexs[i];
        mVexs[i].firstEdge = NULL;
    }
    //初始化"邻接表"的边
    for (i = 0; i < mEdgNum; ++i) {
        //读取边的起始顶点和结束顶点
        c1 = edges[i][0];
        c2 = edges[i][1];

        p1 = getPosition(c1);
        p2 = getPosition(c2);
        //初始化node1
        node1 = new ENode();
        node1->ivex = p2;
        //将node1链接到"p1所在链表的末尾"
        if(mVexs[p1].firstEdge == NULL)
            mVexs[p1].firstEdge = node1;
        else
            linkLast(mVexs[p1].firstEdge, node1);
    }
}

/*
 *析构函数
 */
ListDG::~ListDG() {
}

/*
 *将node节点链接到list的最后
 */
void ListDG::linkLast(ENode *list, ENode *node) {
    ENode *p = list;
    while(p->nextEdge)
        p = p->nextEdge;
    p->nextEdge = node;
}

/*
 *返回ch的位置
 */
int ListDG::getPosition(char ch) {
    int i;
    for (i = 0; i < mVexNum; ++i) {
        if(mVexs[i].data == ch)
            return i;
    }
    return -1;
}

/*
 *读取一个输入字符
 */
char ListDG::readChar() {
    char ch;
    do {
        cin >> ch;
    } while(!((ch>='a' && ch<='z') || (ch>='A' && ch<='Z')));

    return ch;
}

/*
 *打印邻接表
 */
void ListDG::print() {
    int i, j;
    ENode *node;

    cout << "List Graph: " << endl;
    for (i = 0; i < mVexNum; ++i) {
        cout << i << "(" << mVexs[i].data << "): ";
        node = mVexs[i].firstEdge;
        while(node != NULL) {
            cout << node->ivex << "(" << mVexs[node->ivex].data << ") ";
            node = node->nextEdge;
        }
        cout << endl;
    }
}
