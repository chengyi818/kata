/*
 * File Name: main.c
 * Author: ChengYi
 * Mail: chengyi818@foxmail.cn
 * Created Time: Fri 21 Jun 2019 04:35:54 PM CST
 */


int sum(int a, int b, int c, int d, int e, int f, int* g) {
    return a+b+c+d+e+f+*g;
}

int main() {
    int a = 7;
    sum(1, 2, 3, 4, 5, 6, &a);
    /* sum(2, 2, 3, 4, 5, 6, 7); */
}
