#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

#define MAX 100
//邻接表
class ListDG {
    private: //内部类
        //邻接表中表对应的链表的顶点
        class ENode {
            public:
                int ivex;
                ENode *nextEdge;
        };
        //邻接表中表的顶点
        class VNode {
            public:
                char data; //顶点信息
                ENode *firstEdge; //指向第一条依附该顶点的弧
        };

    private: //私有成员
        int mVexNum; //图的顶点的数目
        int mEdgNum; //图的边的数目
        VNode mVexs[MAX];

    public:
        ListDG(); //创建邻接表(手动输入)
        ListDG(char vexs[], int vlen, char edges[][2], int elen); //创建邻接表(矩阵)
        ~ListDG();
        void print(); //打印邻接表图

    private:
        char readChar(); //读取一个输入字符
        int getPosition(char ch); //返回ch的位置
        void linkLast(ENode *list, ENode *node); //将node节点链接到list的最后
};
